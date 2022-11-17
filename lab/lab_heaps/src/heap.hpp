
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <cstddef>

template <class T, class Compare>
class heap;

template <class T, class Compare>
size_t heap<T, Compare>::root() const { return 1; }

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const { return currentIdx * 2; }

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const { return currentIdx * 2 + 1; }

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const { return currentIdx / 2; }

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    return currentIdx * 2 + 1 <= _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    if (currentIdx * 2 + 1 >= _elems.size()) return currentIdx * 2;
    return higherPriority(_elems.at(currentIdx*2), _elems.at(currentIdx*2+1))
        ? currentIdx * 2
        : currentIdx * 2 + 1;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    if (!hasAChild(currentIdx)) return;
    size_t childIdx = maxPriorityChild(currentIdx);
    if (higherPriority(_elems.at(childIdx), _elems.at(currentIdx))) {
        std::swap(_elems.at(childIdx), _elems.at(currentIdx));
        heapifyDown(childIdx);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root()) return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap() { _elems.push_back(T()); }

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems) 
{
    _elems = elems;
    _elems.insert(_elems.begin(), T());
    for (size_t i = _elems.size() / 2; i >= 1; --i) heapifyDown(i);
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    T to_pop = peek();
    std::swap(_elems.at(1), _elems.back());
    _elems.pop_back();
    heapifyDown(1);
    return to_pop;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const { return _elems.at(1); }

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    _elems.push_back(elem);
    heapifyUp(_elems.size() - 1);
}

template <class T, class Compare>
void heap<T, Compare>::updateElem(const size_t & idx, const T& elem)
{
    _elems.at(idx) = elem;
    heapifyUp(idx);
    heapifyDown(idx);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const { return _elems.size() == 1; }

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) 
        heaped.push_back(_elems[i]);
}
