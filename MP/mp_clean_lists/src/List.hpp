/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() : head_(nullptr), tail_(nullptr), length_(0) {  }

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  if (tail_ -> next != nullptr) {
    tail_ -> next -> prev = tail_;
  } else {
    ListNode* one_past_tail = new ListNode();
    one_past_tail -> prev = tail_;
    tail_ -> next = one_past_tail;    
  }
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  if (tail_ -> next != nullptr) { 
    tail_ -> next -> prev = tail_;
    return List<T>::ListIterator(tail_->next);
  }
  ListNode* one_past_tail = new ListNode();
  one_past_tail -> prev = tail_;
  tail_ -> next = one_past_tail;
  return List<T>::ListIterator(one_past_tail);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  ListNode* curr = head_;
  ListNode* curr_next = curr;
  while (curr_next != nullptr) {
    curr_next = curr->next;
    delete curr;
    curr = curr_next;
  }
  head_ = nullptr;
  tail_ = nullptr;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = nullptr;
  if (head_ != nullptr) { head_ -> prev = newNode; }
  if (tail_ == nullptr) { tail_ = newNode; }
  head_ = newNode;
  ++length_;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  ListNode* newNode = new ListNode(ndata);
  newNode->next = nullptr;
  newNode->prev = tail_;
  if (tail_ != nullptr) { tail_->next = newNode; }
  if (head_ == nullptr) { head_ = newNode; }
  tail_ = newNode;
  ++length_;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  ListNode * curr = start;
  if (splitPoint == 0) { return curr; }
  for (int i = 0; i < splitPoint; ++i) { curr = curr->next; }
  if (curr != nullptr) {
    if (curr->prev != nullptr) curr->prev->next = nullptr;
    curr->prev = nullptr;
  }
  return curr;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  if (size() == 0 || size() == 1 || size() == 2) { return; }
  ListNode* head = head_->next;
  ListNode* curr_trip_first = head_;
  for (int i = 0; i < size() / 3; ++i) {
    curr_trip_first -> next -> prev       = curr_trip_first -> prev;
    if (curr_trip_first -> prev != nullptr)
      curr_trip_first -> prev -> next     = curr_trip_first -> next;
    curr_trip_first -> prev               = curr_trip_first->next->next;
    curr_trip_first -> next               = curr_trip_first->next->next->next;
    if (curr_trip_first -> next != nullptr ) 
      curr_trip_first -> next -> prev     = curr_trip_first;
    curr_trip_first -> prev -> next       = curr_trip_first;
    curr_trip_first                       = curr_trip_first -> next;
  }
  head_ = tail_ = head;
  while (tail_ -> next != nullptr) { tail_ = tail_ -> next; }
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
  head_->prev = nullptr;
  tail_->next = nullptr;
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  if (size() == 0 || size() == 1) { return; }
  ListNode * left = startPoint -> prev, * right = endPoint -> next;
  ListNode* dummy_node = new ListNode();
  ListNode* curr       = dummy_node;
  while (endPoint != startPoint) {
    endPoint                 = endPoint -> prev;
    curr -> next             = endPoint -> next;
    endPoint -> next -> prev = curr;
    curr                     = curr -> next;
  }
  curr -> next       = startPoint;
  startPoint -> prev = curr;
  startPoint         = dummy_node -> next;
  startPoint -> prev = left;  if (left != nullptr)  left  -> next = startPoint;
  endPoint   -> next = right; if (right != nullptr) right -> prev = endPoint;
  delete dummy_node;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  if (n <= 1) { return; }
  if (n >= length_) { reverse(); return; }
  ListNode * start = head_, * end = head_; 
  while (start != nullptr && end != nullptr) {
    for (int i = 0; i < n-1 && end != tail_; ++i) end = end -> next;
    if (start == head_) { reverse(head_, end); }
    else if (end == tail_) { reverse(start, tail_); break; }
    else { reverse(start, end); }
    start = end -> next;
    end = start;
  }
  head_ -> prev = nullptr; tail_ -> next = nullptr;
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != nullptr) {
        while (tail_->next != nullptr)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = nullptr;
    otherList.tail_ = nullptr;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode * second) {
  if (first == nullptr) { return second; }
  if (second == nullptr) { return first; }
  ListNode * dummy_head = new ListNode();
  dummy_head -> next = first; first -> prev = dummy_head;
  ListNode * first_prev = first -> prev, * curr_second = second;
  while (first != nullptr) {
    if (second == nullptr) { first_prev = first; first = nullptr; break; }
    if (first -> data < curr_second -> data) { first_prev = first; first = first -> next; } 
    else {
      second             = second -> next;
      first_prev -> next = curr_second;     curr_second -> prev = first_prev;
      first      -> prev = curr_second;     curr_second -> next = first;
      first_prev         = first -> prev;
      curr_second        = second;
    }
  }
  if (second != nullptr) { first_prev -> next = second; second -> prev = first_prev; }
  ListNode* head = dummy_head -> next; head -> prev = nullptr;
  delete dummy_head; dummy_head = nullptr;
  return head;
}

/*
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  if (chainLength == 1 || chainLength == 0) { return start; }
  return merge(mergesort(split(start, chainLength / 2), chainLength - (chainLength / 2)),
               mergesort(start, chainLength / 2));
}
