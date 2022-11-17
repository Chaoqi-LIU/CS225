#include "dsets.h"

void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; ++i) disjoint_set_.push_back(-1);
}

int DisjointSets::find(int elem) {
    if (disjoint_set_.at(elem) >= 0)
        return disjoint_set_.at(elem) = find(disjoint_set_.at(elem));
    return elem;
}

void DisjointSets::setunion(int a, int b) {
    int root1 = find(a), root2 = find(b);
    int new_size = disjoint_set_.at(root1) + disjoint_set_.at(root2);
    if (disjoint_set_.at(root1) <= disjoint_set_.at(root2)) {
        disjoint_set_.at(root2) = root1;
        disjoint_set_.at(root1) = new_size;
    } else {
        disjoint_set_.at(root1) = root2;
        disjoint_set_.at(root2) = new_size;
    }
}

int DisjointSets::size(int elem) {
    return  -disjoint_set_.at(find(elem));
}

void DisjointSets::init() {
    disjoint_set_.clear();
}

void DisjointSets::print() const {
    for (auto & elem : disjoint_set_) std::cout << elem << " ";
    std::cout << std::endl;
}