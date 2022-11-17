/**
 * @file binarytree.hpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */
#include "InorderTraversal.h"
#include <iostream>

/**
 * @return The height of the binary tree. Recall that the height of a binary
 *  tree is just the length of the longest path from the root to a leaf, and
 *  that the height of an empty tree is -1.
 */
template <typename T>
int BinaryTree<T>::height() const
{
    // Call recursive helper function on root
    return height(root);
}

/**
 * Private helper function for the public height function.
 * @param subRoot
 * @return The height of the subtree
 */
template <typename T>
int BinaryTree<T>::height(const Node* subRoot) const
{
    // Base case
    if (subRoot == NULL)
        return -1;

    // Recursive definition
    return 1 + std::max(height(subRoot->left), height(subRoot->right));
}

/**
 * Prints out the values of the nodes of a binary tree in order.
 * That is, everything to the left of a node will be printed out before that
 * node itself, and everything to the right of a node will be printed out after
 * that node.
 */
template <typename T>
void BinaryTree<T>::printLeftToRight() const
{
    // Call recursive helper function on the root
    printLeftToRight(root);

    // Finish the line
    std::cout << std::endl;
}

/**
 * Private helper function for the public printLeftToRight function.
 * @param subRoot
 */
template <typename T>
void BinaryTree<T>::printLeftToRight(const Node* subRoot) const
{
    // Base case - null node
    if (subRoot == NULL)
        return;

    // Print left subtree
    printLeftToRight(subRoot->left);

    // Print this node
    std::cout << subRoot->elem << ' ';

    // Print right subtree
    printLeftToRight(subRoot->right);
}

/**
 * Flips the tree over a vertical axis, modifying the tree itself
 *  (not creating a flipped copy).
 */
template <typename T>
void BinaryTree<T>::mirror() {
    mirror(root);
}

template <typename T>
void BinaryTree<T>::mirror(Node* node) {
    if (node == nullptr) { return; }
    Node* tmp = node->left;
    node->left = node->right;
    node->right = tmp;
    mirror(node->left);
    mirror(node->right);
}


/**
 * isOrdered() function iterative version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedIterative() const
{
    InorderTraversal<T> tt(root);
    auto prev = tt.begin();
    for (auto iter = tt.begin(); iter != tt.end(); ++iter) {
        if ((*prev)->elem > (*iter)->elem) return false;
        prev = iter;
    }
    return true;
}

/**
 * isOrdered() function recursive version
 * @return True if an in-order traversal of the tree would produce a
 *  nondecreasing list output values, and false otherwise. This is also the
 *  criterion for a binary tree to be a binary search tree.
 */
template <typename T>
bool BinaryTree<T>::isOrderedRecursive() const
{
    return isOrderedRecursive(root);
}

template <typename T>
bool BinaryTree<T>::isOrderedRecursive(Node* node) const {
    if (node == nullptr || (node->left == nullptr && node->right == nullptr)) return true;
    return node->elem >= max(node->left, node->left->elem)
        && node->elem <= min(node->right, node->right->elem);
}

template <typename T>
T BinaryTree<T>::min(Node* node, T min_val) const {
    if (node == nullptr) return min_val;
    if (node->left == nullptr && node->right == nullptr) return node->elem;
    min_val = min_val < node->elem ? min_val : node->elem;
    T left_min = min(node->left, min_val);
    T right_min = min(node->right, min_val);
    return left_min < right_min ? left_min : right_min;
}

template <typename T>
T BinaryTree<T>::max(Node* node, T max_val) const {
    if (node == nullptr) return max_val;
    if (node->left == nullptr && node->right == nullptr) return node->elem;
    max_val = max_val > node->elem ? max_val : node->elem;
    // T left_max = max(node->left, max_val);
    // T right_max = max(node->right, max_val);
    // return left_max > right_max ? left_max : right_max;
    return std::max( max(node->left, max_val), max(node->right, max_val) );
}
