/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node * subtree = t->right->left;
    t->right->left = t;
    t = t->right;
    t->left->right = subtree;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node * subtree = t->left->right;
    t->left->right = t;
    t = t->left;
    t->right->left = subtree;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if (subtree == nullptr) return;
    int b1 = height(subtree->right) - height(subtree->left);
    if (b1 == -2) {
        int b2 = height(subtree->left->right) - height(subtree->left->left);
        if (b2 == -1) rotateRight(subtree);
        else if (b2 == 1) rotateLeftRight(subtree);
    } else if (b1 == 2) {
        int b2 = height(subtree->right->right) - height(subtree->right->left);
        if (b2 == 1) rotateLeft(subtree);
        else if (b2 == -1) rotateRightLeft(subtree);
    } else return;
    _UpdateHeight(subtree);
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == nullptr) subtree = new Node(key, value);
    else if (subtree->key == key) subtree->value = value;
    else if (subtree->key > key) insert(subtree->left, key, value);
    else insert(subtree->right, key, value);
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree; subtree = nullptr;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node * iop = subtree->left;
            while (iop->right != nullptr) iop = iop->right;
            Node *& IOP = Find(subtree, iop->key);
            if (subtree->left == IOP) {
                IOP->right = subtree->right;
                Node * to_remove = subtree;
                subtree = IOP;
                delete to_remove; to_remove = nullptr;
            } else {
                Node * subtree_left = subtree->left,
                     * subtree_right = subtree->right,
                     * IOP_left = IOP->left;
                Swap(IOP, subtree);
                subtree->left = subtree_left; 
                subtree->right = subtree_right;
                if (IOP_left == nullptr) { delete IOP; IOP = nullptr; }
                else { delete IOP; IOP = IOP_left; }
            }
        } else {
            /* one-child remove */
            // your code here
            Node * to_remove = subtree;
            if (subtree->left != nullptr) subtree = subtree->left;
            else subtree = subtree->right;
            delete to_remove; to_remove = nullptr;
        }
        // your code here
    }
    rebalance(subtree);
}
