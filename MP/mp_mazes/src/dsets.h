#pragma once

#include <vector>
#include <iostream>

class DisjointSets {
    public:
        void addelements(int num);
        int find(int elem);
        void setunion(int a, int b);
        int size(int elem);
        void init();
        void print() const;

    private:
        std::vector<int> disjoint_set_;
};