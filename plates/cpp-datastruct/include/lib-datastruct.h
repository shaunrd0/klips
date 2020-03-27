#ifndef LDS_H
#define LDS_H

#include <iostream>

class Node {
  public:
    Node() : next(NULL) {};
    Node(char val) : data(val), next(NULL) {};
    char data;
    Node *next;
};

// Linked list

class LinkedList {

  public:
    LinkedList() : head(NULL), tail(NULL) {};
    void Append(char val);
    void Push(char val);
    void Remove(char val);
    void Replace(char remove, char replace);
    void Display() const;
    bool isEmpty() const;
    Node* Find(char val) const;
  private:
    Node *head, *tail;
};

// Array based stack

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
    Node stack[MAX];
    int top;
};

#endif
