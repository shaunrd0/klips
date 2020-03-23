#ifndef LDS_H
#define LDS_H

#include <iostream>

enum CONST {
  MAX=10
};

template <typename T>
class ListNode {
  public:
    ListNode() : next(NULL) {};
    ListNode(T val) : data(val), next(NULL) {};
    // Sneak more of Push() through node concstr?
    // ListNode(T val, LinkedList& l) data(val), next(l.Top());
  private:
    T data;
    ListNode* next;

};

template <typename T>
class LinkedList {

  public:
    LinkedList() {};
    void Push(T val) {};
    T Pop();
    T Top();
    void Display() const;

  private:
    // ListNode data[MAX];

};

#endif
