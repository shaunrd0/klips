#ifndef LDS_H
#define LDS_H

#include <iostream>

class StackArray {
  public:
    StackArray() : top(EMPTY) {};
    void Push(char val);
    char Pop();
    char Top() const;
    void Display() const;
    bool isEmpty() const;

  private:
    enum { EMPTY=-1, MAX=10 };
    class ListNode {
      public:
        ListNode() : next(NULL) {};
        ListNode(char val) : data(val), next(NULL) {};
        char data;
        ListNode* next;
    };
    ListNode list[MAX];
    int top;
};

#endif
