#pragma once

#include "../lib/cs225/PNG.h"
#include "dsets.h"

#include <vector>
#include <queue>
#include <iostream>
#include <algorithm>
#include <set>

using namespace cs225;

class SquareMaze {
    public:
        SquareMaze();
        void makeMaze(int width, int height);
        bool canTravel(int x, int y, int dir) const;
        void setWall(int x, int y, int dir, bool exists);
        std::vector<int> solveMaze();
        PNG * drawMaze() const;
        PNG * drawMazeWithSolution();

    private:
        bool InBound(int x, int y) const { return x >= 0 && x < width_ && y >= 0 && y < height_; }

        DisjointSets dset_;
        std::vector<std::vector<std::pair<bool,bool>>> maze_;
        int width_;
        int height_;
        int dx_[4] = {1, 0, -1, 0};
        int dy_[4] = {0, 1, 0, -1};
        std::pair<int,int> destination;
};