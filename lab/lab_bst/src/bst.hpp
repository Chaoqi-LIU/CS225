/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    return find(root, key)->value;
}

template <class K, class V>
struct BST<K, V>::Node *& BST<K, V>::find(Node *& subtree, const K& key)
{
    if (subtree == nullptr) return subtree;
    if (subtree->key == key) return subtree;
    if (subtree->key > key) {
        return find(subtree->left, key);
    } else {
        return find(subtree->right, key);
    }
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    Node *& place =  find(root, key);
    if (place == nullptr) place = new Node(key, value);
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
}

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    Node * tmp = first;
    first = second;
    second = tmp;
}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    Node *& ptr = find(root, key);
    if (ptr == nullptr) return;
    // 0 child
    if (ptr->left == nullptr && ptr->right == nullptr) { delete ptr; ptr = nullptr; return; }
    if (ptr->left == nullptr) {  // 1 right child
        Node * to_remove = ptr;
        ptr = ptr->right;
        delete to_remove; to_remove = nullptr;
        return;
    }
    if (ptr->right == nullptr) {  // 1 left child
        Node * to_remove = ptr;
        ptr = ptr->left;
        delete to_remove; to_remove = nullptr;
        return;
    }
    // 2 children
    Node * iop = ptr->left;
    while (iop->right != nullptr) iop = iop->right;
    Node *& IOP = find(ptr, iop->key);
    if (ptr->left == IOP) {  // special case
        IOP->right = ptr->right;
        Node * to_remove = ptr;
        ptr = IOP;
        delete to_remove; to_remove = nullptr;
        return;
    }
    Node * ptr_l = ptr->left, * ptr_r = ptr->right;  // mem ptr 's left and right children
    if (IOP->left == nullptr) {  // IOP has no left child
        Node * ptr_l = ptr->left, * ptr_r = ptr->right;
        swap(ptr, IOP);
        ptr->left = ptr_l; ptr->right = ptr_r;
        delete IOP; IOP = nullptr;
        return;
    }
    // IOP has left child
    Node * IOP_l = IOP->left;
    swap(ptr, IOP);
    ptr->left = ptr_l; ptr->right = ptr_r;
    delete IOP;
    IOP = IOP_l;
}


template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{

}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    BST<K, V> tree;
    for (auto p : inList) tree.insert(p.first, p.second);
    return tree;
}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    std::vector<int> heights(inList.size(), 0);
    std::sort(inList.begin(), inList.end());
    do { ++heights.at(listBuild(inList).height());
    } while (std::next_permutation(inList.begin(), inList.end()));
    return heights;
}