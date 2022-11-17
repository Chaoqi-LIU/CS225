#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stack>
#include "cs225/PNG.h"
#include "dsets.h"
#include "maze.h"

using namespace cs225;
using namespace std;

void assert_maze_acyclic(SquareMaze & maze, int width, int height);
void assert_maze_connected(SquareMaze & maze, int width, int height);
void assert_maze_tree(SquareMaze & maze, int width, int height);
void advancePosition(int * x, int * y, int dir);
PNG read_solution(const string & filename, int width, int height);
PNG read_unsolved(const string & filename, int width, int height);
#define READ_SOLUTION_PNG(func, width, height)  \
    read_solution(string("../tests/soln_") + func + string(".png"), width, height)
#define READ_UNSOLVED_PNG(func, width, height)  \
    read_unsolved(string("../tests/soln_") + func + string(".png"), width, height)
#define READ_SOLUTION_MAZE(func, width, height)  \
    MazeReader(READ_SOLUTION_PNG(func, width, height))
#define READ_UNSOLVED_MAZE(func, widht, height)  \
    MazeReader(READ_UNSOLVED_PNG(func, width, height))

void recDFS(SquareMaze & maze, vector<vector<uint8_t> > * visited, int x, int y, int width, int height, int * calls)
{
    stack< pair<int, int> > s;
    s.push(make_pair(x, y));

    while (!s.empty()) {
        x = s.top().first;
        y = s.top().second;
        s.pop();
        (*calls)++;
        if ((*visited)[x][y] != 0)
            continue;
        (*visited)[x][y] = 1;

        if (x < width-1 && maze.canTravel(x, y, 0))
            s.push(make_pair(x+1, y));
        if (y < height-1 && maze.canTravel(x, y, 1))
            s.push(make_pair(x, y+1));
        if (x > 0 && maze.canTravel(x, y, 2))
            s.push(make_pair(x-1, y));
        if (y > 0 && maze.canTravel(x, y, 3))
            s.push(make_pair(x, y-1));
    }
}

pair<int, int> assert_maze_helper(SquareMaze & maze, int width, int height)
{
    vector<vector<uint8_t> > visited;
    for (int i = 0; i < width; i++)
        visited.push_back(vector<uint8_t>(height));

    int components = 0;
    int calls = 0;

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            if (visited[i][j] == 0) {
                recDFS(maze, &visited, i, j, width, height, &calls);
                components++;
            }
        }
    }

    return make_pair(components, calls);
}

void assert_maze_acyclic(SquareMaze & maze, int width, int height)
{
    pair<int, int> checks = assert_maze_helper(maze, width, height);
    int components = checks.first;
    int calls = checks.second;
    if (calls + components != width * height * 2)
        cout << "Maze has a cycle" << endl;
}


void assert_maze_connected(SquareMaze & maze, int width, int height)
{
    pair<int, int> checks = assert_maze_helper(maze, width, height);
    int components = checks.first;
    int calls = checks.second;
    if (components != 1)
        cout << "Maze is not connected" << endl;
}

void assert_maze_tree(SquareMaze & maze, int width, int height)
{
    pair<int, int> checks = assert_maze_helper(maze, width, height);
    int components = checks.first;
    int calls = checks.second;
    if (calls + components != width * height * 2)
        cout << "Maze has a cycle" << endl;
    if (components != 1)
        cout << "Maze is not connected" << endl;
}

PNG read_solution(const string & filename, int width, int height)
{
      PNG output;
      output.readFromFile(filename);
      return output;
}

PNG read_unsolved(const string & filename, int width, int height)
{
      PNG output;
      output.readFromFile(filename);
      return output;
}



int main()
{
    // SquareMaze maze;
    // int w = 50, h = 50;
    // maze.makeMaze(w, h);
    // assert_maze_connected(maze, w, h);
    // assert_maze_acyclic(maze, w, h);
    // assert_maze_tree(maze, w, h);
    // cout << "after assertion" << endl;

    // vector<int> path = maze.solveMaze();
    // for (auto & dir : path) cout << dir << " ";
    // cout << endl;

    // PNG * image = maze.drawMazeWithSolution();
    // image->writeToFile("main.png");

    // PNG * image = maze.drawMaze();
    // image->writeToFile("main.png");



    SquareMaze maze1;
    maze1.makeMaze(50, 50);
    
    SquareMaze maze2;
    maze2.makeMaze(50, 50);
    bool same = true;

    for (int y = 0; y < 50; y++) {
        for (int x = 0; x < 50; x++) {
            if (maze1.canTravel(x, y, 0) != maze2.canTravel(x, y, 0)){
                same = false;
                break;
            }
            if (maze1.canTravel(x, y, 1) != maze2.canTravel(x, y, 1)){
                same = false;
                break;
            }
        }
    }
    if(same == false) {
        cout << "success" << endl;
    } else
        cout << "Generated the same 50x50 maze twice" << endl;


    return 0;
}
