/**
 * @file schedule.cpp
 * Exam scheduling using graph coloring
 */

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <map>
#include <unordered_map>

#include "schedule.h"
#include "utils.h"
#include <algorithm>

/**
 * Given a filename to a CSV-formatted text file, create a 2D vector of strings where each row
 * in the text file is a row in the V2D and each comma-separated value is stripped of whitespace
 * and stored as its own string. 
 * 
 * Your V2D should match the exact structure of the input file -- so the first row, first column
 * in the original file should be the first row, first column of the V2D.
 *  
 * @param filename The filename of a CSV-formatted text file. 
 */
V2D file_to_V2D(const std::string & filename){
    // Your code here!
    std::string content = file_to_string(filename);
    V2D res;
    std::vector<std::string> row;

    std::vector<std::string> fields;
    SplitString(content, '\n', fields);
    for (auto & field : fields) {
        std::vector<std::string> tmp;
        SplitString(field, ',', tmp);
        for (auto & entry : tmp)
            row.push_back(Trim(entry));
        res.push_back(row);
        row.clear();
    }
    return res;
}

/**
 * Given a course roster and a list of students and their courses, 
 * perform data correction and return a course roster of valid students (and only non-empty courses).
 * 
 * A 'valid student' is a student who is both in the course roster and the student's own listing contains the course
 * A course which has no students (or all students have been removed for not being valid) should be removed
 * 
 * @param cv A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param student A 2D vector of strings where each row is a student ID followed by the courses they are taking
 */
V2D clean(const V2D & cv, const V2D & students) {
    std::unordered_map<std::string, std::unordered_set<std::string>> map_student_to_courses;
    V2D res_cv = cv;
    V2D non_const_students = students;

    for (auto & student : non_const_students)
        for (unsigned int i = 1; i < student.size(); ++i) 
            map_student_to_courses[student.at(0)].insert(student.at(i));

    for (auto & course : res_cv)
        for (unsigned int i = 1; i < course.size(); )
            if (map_student_to_courses[course.at(i)].count(course.at(0))) ++i;
            else course.erase(course.begin() + i);

    for (unsigned int i = 0; i < res_cv.size(); )
        if (res_cv.at(i).size() != 1) ++i;
        else res_cv.erase(res_cv.begin() + i);

    return res_cv;
}

/**
 * Given a collection of courses and a list of available times, create a valid scheduling (if possible).
 * 
 * A 'valid schedule' should assign each course to a timeslot in such a way that there are no conflicts for exams
 * In other words, two courses who share a student should not share an exam time.
 * Your solution should try to minimize the total number of timeslots but should not exceed the timeslots given.
 * 
 * The output V2D should have one row for each timeslot, even if that timeslot is not used.
 * 
 * As the problem is NP-complete, your first scheduling might not result in a valid match. Your solution should 
 * continue to attempt different schedulings until 1) a valid scheduling is found or 2) you have exhausted all possible
 * starting positions. If no match is possible, return a V2D with one row with the string '-1' as the only value. 
 * 
 * @param courses A 2D vector of strings where each row is a course ID followed by the students in the course
 * @param timeslots A vector of strings giving the total number of unique timeslots
 */
V2D schedule(const V2D &courses, const std::vector<std::string> &timeslots){
    for (auto & course : courses) {
        Graph graph;
        graph.BuildGraph(courses);
        graph.GraphColoring(course.at(0));
        int no_colors = graph.GetColorUsed() + 1;
        if (static_cast<unsigned int>(no_colors) > timeslots.size()) continue;
        V2D res(timeslots.size());
        for (unsigned int i = 0; i < res.size(); ++i)
            res.at(i).push_back(timeslots.at(i));
        for (auto & pair : graph.GetColors()) 
            res.at(pair.second).push_back(pair.first);
        return res;
    }
    return {{"-1"}};
}