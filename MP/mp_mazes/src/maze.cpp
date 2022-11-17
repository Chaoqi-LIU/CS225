#include "maze.h"

SquareMaze::SquareMaze(): maze_(), width_(), height_() {}

void SquareMaze::makeMaze(int width, int height) {
    width_ = width;
    height_ = height;
    maze_ = std::vector<std::vector<std::pair<bool,bool>>>(
        height_, std::vector<std::pair<bool,bool>>(width_, {false, false})
    );
    dset_.init();
    dset_.addelements(width_ * height_);

    int option = rand() & 1;
    if (option == 0) {
        for (int y = 0; y < height_; ++y) {
            for (int x = 0; x < width_; ++x) {
                int dir = rand() & 1;
                if (!canTravel(x, y, dir) && InBound(x + dx_[dir], y + dy_[dir])) {
                    if (dset_.find(y * width_ + x) != dset_.find((y+dy_[dir]) * width_ + (x+dx_[dir]))) {
                        setWall(x, y, dir, false);
                        dset_.setunion(y*width_+x, (y+dy_[dir])*width_+(x+dx_[dir]));
                    }
                } 
                if (!canTravel(x, y, 1 - dir) && InBound(x + dx_[1 - dir], y + dy_[1 - dir])) {
                    if (dset_.find(y * width_ + x) != dset_.find((y+dy_[1 - dir]) * width_ + (x+dx_[1-dir]))) {
                        setWall(x, y, 1 - dir, false);
                        dset_.setunion(y*width_+x, (y+dy_[1-dir])*width_+(x+dx_[1-dir]));
                    }
                }
            }
        }
    } else {
        for (int y = height_ - 1; y >= 0; --y) {
            for (int x = width_ - 1; x >= 0; --x) {
                int dir = rand() & 1;
                if (!canTravel(x, y, dir) && InBound(x + dx_[dir], y + dy_[dir])) {
                    if (dset_.find(y * width_ + x) != dset_.find((y+dy_[dir]) * width_ + (x+dx_[dir]))) {
                        setWall(x, y, dir, false);
                        dset_.setunion(y*width_+x, (y+dy_[dir])*width_+(x+dx_[dir]));
                    }
                } 
                if (!canTravel(x, y, 1 - dir) && InBound(x + dx_[1 - dir], y + dy_[1 - dir])) {
                    if (dset_.find(y * width_ + x) != dset_.find((y+dy_[1 - dir]) * width_ + (x+dx_[1-dir]))) {
                        setWall(x, y, 1 - dir, false);
                        dset_.setunion(y*width_+x, (y+dy_[1-dir])*width_+(x+dx_[1-dir]));
                    }
                }
            }
        }
    }

    // std::vector<std::vector<bool>> visited(height_, std::vector<bool>(width_, false));
    // int x = 0, y = 0, di = 0;
    // for (int i = 0; i < width_ * height_; ++i) {
    //     visited.at(y).at(x) = true;

    //     int dir = rand() & 1;
    //     if (!canTravel(x, y, dir) && InBound(x + dx_[dir], y + dy_[dir])) {
    //         if (dset_.find(y * width_ + x) != dset_.find((y+dy_[dir]) * width_ + (x+dx_[dir])))
    //             setWall(x, y, dir, false);
    //     } 
    //     else if (!canTravel(x, y, 1 - dir) && InBound(x + dx_[1 - dir], y + dy_[1 - dir])) {
    //         if (dset_.find(y * width_ + x) != dset_.find((y+dy_[1 - dir]) * width_ + (x+dx_[1-dir])))
    //                 setWall(x, y, 1 - dir, false);
    //     }

    //     int new_x = x + dx_[di], new_y = y + dy_[di];
    //     if (InBound(new_x, new_y) && !visited.at(new_y).at(new_x)) {
    //         x = new_x;
    //         y = new_y;
    //     } else {
    //         di = (di + 1) % 4;
    //         x += dx_[di];
    //         y += dy_[di];
    //     }
    // }

    // dset_.print();
}

bool SquareMaze::canTravel(int x, int y, int dir) const {
    if (!InBound(x,y)) throw std::runtime_error("x y not in bound");
    if (dir == 0)
        return InBound(x + 1, y) && maze_.at(y).at(x).first;
    else if (dir == 1)
        return InBound(x, y + 1) && maze_.at(y).at(x).second;
    else if (dir == 2) 
        return InBound(x - 1, y) && maze_.at(y).at(x - 1).first;
    else 
        return InBound(x, y - 1) && maze_.at(y - 1).at(x).second;
}

void SquareMaze::setWall(int x, int y, int dir, bool exists) {
    if (!InBound(x, y)) throw std::runtime_error("x y not in bound");
    if (dir == 0 && InBound(x + 1, y))
        maze_.at(y).at(x).first = !exists;
    else if (dir == 1 && InBound(x, y + 1))
        maze_.at(y).at(x).second = !exists;
}

std::vector<int> SquareMaze::solveMaze() {
    std::vector<std::vector<int>> dist(height_, std::vector<int>(width_, -1));
    dist.at(0).at(0) = 0;
    std::vector<std::vector<int>> pre(height_, std::vector<int>(width_, -1));
    std::queue<std::pair<int,int>> q;
    q.push({0, 0});
    while (!q.empty()) {
        std::pair<int,int> coord = q.front(); q.pop();
        int x = coord.first, y = coord.second;
        int cnt = 0;
        for (int i = 0; i < 4; ++i) {
            if (canTravel(x, y, i) && dist.at(y + dy_[i]).at(x + dx_[i]) == -1) {
                q.push({x + dx_[i], y + dy_[i]});
                dist.at(y + dy_[i]).at(x + dx_[i]) = dist.at(y).at(x) + 1;
                pre.at(y + dy_[i]).at(x + dx_[i]) = i;
                ++cnt;
            }
        }
    }
    int x = 0, dis = dist.at(height_ - 1).at(x);
    for (int i = 0; i < width_; ++i) 
        if (dist.at(height_ - 1).at(i) > dis) 
            dis = dist.at(height_ - 1).at(i), x = i;
    std::vector<int> path;
    std::pair<int,int> coord = {x, height_ - 1};
    destination = coord;
    while (coord.first != 0 || coord.second != 0) {
        path.push_back(pre.at(coord.second).at(coord.first));
        if (pre.at(coord.second).at(coord.first) == 0)
            coord = {coord.first - dx_[0], coord.second - dy_[0]};
        else if (pre.at(coord.second).at(coord.first) == 1)
            coord = {coord.first - dx_[1], coord.second - dy_[1]};
        else if (pre.at(coord.second).at(coord.first) == 2)
            coord = {coord.first - dx_[2], coord.second - dy_[2]};
        else if (pre.at(coord.second).at(coord.first) == 3)
            coord = {coord.first - dx_[3], coord.second - dy_[3]};
    }
    std::reverse(path.begin(), path.end());
    return path;
}

PNG * SquareMaze::drawMaze() const {
    PNG * png = new PNG(width_ * 10 + 1, height_ * 10 + 1);
    for (int x = 10; x < width_ * 10 + 1; ++x)
        png->getPixel(x, 0) = {0,0,0};
    for (int y = 0; y < height_ * 10 + 1; ++y)
        png->getPixel(0, y) = {0,0,0};
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            if (!maze_.at(y).at(x).first)
                for (int k = 0; k <= 10; ++k)
                    png->getPixel((x+1)*10, y*10+k) = {0,0,0};
            if (!maze_.at(y).at(x).second)
                for (int k = 0; k <= 10; ++k)
                    png->getPixel(x*10+k, (y+1)*10) = {0,0,0};
        }
    }       
    return png;
}

PNG * SquareMaze::drawMazeWithSolution() {
    PNG * png = drawMaze();
    std::vector<int> path = solveMaze();
    int x = 5, y = 5;
    png->getPixel(x, y) = {0, 1, 0.5};
    for (auto & dir : path) {
        for (int k = 0; k < 10; ++k) {
            x += dx_[dir];
            y += dy_[dir];
            png->getPixel(x, y) = {0, 1, 0.5};
        }
    }
    x = destination.first, y = destination.second;
    for (int k = 1; k <= 9; ++k) 
        png->getPixel(x*10+k, (y+1)*10) = {0, 0, 1};
    return png;
}