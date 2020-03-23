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
    class Node {
      public:
        Node() : next(NULL) {};
        Node(char val) : data(val), next(NULL) {};
        char data;
        Node* next;
    };
    Node stack[MAX];
    int top;
};

#endif
