/**
 * @file schedule.h
 * Exam scheduling using graph coloring
 */

#pragma once

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <set>
#include <unordered_set>
#include <algorithm>
#include <list>
#include <iostream>

typedef std::vector<std::vector<std::string>> V2D; 


/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. You must preserve the order from the input file.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 * @return The vector of vectors of strings imported from filename
 */
V2D file_to_V2D(const std::string & filename);

/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param course A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 * @return A 2D vector of strings where each row is a course followed by all the students in the course
 */
V2D clean(const V2D & cv, const V2D & sv);

/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * If a valid solution cannot be formed after <XXX: How many iterations?> iterations of graph coloring, return a V2D with one row
 * with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 * @return A 2D vector which each row is a timeslot with all the courses scheduled for that time
 */
V2D schedule(const V2D &courses, const std::vector<std::string> &timeslots);

class Graph {
    public:
        Graph() = default;

        void AddVertex(const std::string v) {
            if (VertexInGraph(v)) throw std::runtime_error("v already in graph");
            graph_.insert({v, std::list<std::string>()});
            colors_.insert({v, -1});
        }
        void AddVertex(const std::string v, int color) {
            if (VertexInGraph(v)) throw std::runtime_error("v already in graph");
            graph_.insert({v, std::list<std::string>()});
            colors_.insert({v, color});
        }
        void AddEdge(const std::string v1, const std::string v2) {
            if (!VertexInGraph(v1) || !VertexInGraph(v2)) throw std::runtime_error("v1 / v2 not in graph");
            auto & v1_adj = graph_.at(v1); auto & v2_adj = graph_.at(v2);
            if (std::find(v1_adj.begin(), v1_adj.end(), v2) == v1_adj.end()) v1_adj.push_back(v2);
            if (std::find(v2_adj.begin(), v2_adj.end(), v1) == v2_adj.end()) v2_adj.push_back(v1);
        }
        bool AreAdj(const std::string v1, const std::string v2) {
            return (std::find(graph_.at(v1).begin(), graph_.at(v1).end(), v2) != graph_.at(v1).end()) &&
                   (std::find(graph_.at(v2).begin(), graph_.at(v2).end(), v1) != graph_.at(v2).end());
        }
        void Print() const {
            std::cout << "==============================\nGraph: \n";
            for (const auto & pair : graph_) {
                std::cout << " | {" << pair.first << "," << colors_.at(pair.first) << "} | ";
                for (auto & adj : pair.second)
                    std::cout << " -> {" << adj << "," << colors_.at(adj) << "}";
                std::cout << '\n';
            }
            std::cout << "==============================\n";
        }
        bool VertexInGraph(const std::string v) { return graph_.count(v) != 0; }
        std::list<std::string>& GetAdjList(const std::string v) { return graph_.at(v); }
        int GetColor(const std::string v) const { return colors_.at(v); }
        void SetColor(const std::string v, const int color) { colors_[v] = color; }
        void BuildGraph(const V2D& courses) {
            V2D nc_cv = courses;
            std::unordered_map<std::string, std::unordered_set<std::string>> map_student_to_courses;
            for (auto & course : nc_cv) {
                AddVertex(course.at(0));
                for (unsigned int i = 1; i < course.size(); ++i)
                    map_student_to_courses[course.at(i)].insert(course.at(0));
            }
            for (auto & entry : map_student_to_courses) {
                std::vector<std::string> course_list;
                for (auto & c : entry.second) course_list.push_back(c);
                for (unsigned int i = 0; i < course_list.size(); ++i) 
                    for (unsigned int j = i + 1; j < course_list.size(); ++j) 
                        AddEdge(course_list.at(i), course_list.at(j));
            }
        }
        void DFS(std::string v) {
            std::unordered_set<int> adj_colors;
            for (auto & adj : GetAdjList(v))
                adj_colors.insert(colors_.at(adj));
            int color = 0;
            while (adj_colors.count(color)) ++color;
            color_used = color > color_used ? color : color_used;
            SetColor(v, color);
            for (auto & adj : GetAdjList(v))
                if (GetColor(adj) == -1) DFS(adj);
        }
        void GraphColoring(const std::string& start) { DFS(start); }
        int GetColorUsed() const { return color_used; }
        std::map<std::string, int>& GetColors() { return colors_; }

    private:
        int color_used = 0;
        std::map<std::string, std::list<std::string>> graph_;
        std::map<std::string, int> colors_;
};