#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>

// Singly Linked List
class SingleList{
  public:
    SingleList() : head(NULL) {};
    SingleList(const SingleList& rhs);
    SingleList& operator=(const SingleList& rhs);
    ~SingleList();
    bool insert(int val);
    bool insert(int val, int key);
    void makeEmpty();
    bool isEmpty() const;
    int peek() const;
    void print() const;
    bool find(int val) const;

  private:
    struct Node {
      int data;
      Node *next;
      Node(): data(00), next(NULL) {};
      Node(int val): data(val), next(NULL) {};
    };
    Node *head;
    Node* find(int val, Node *start) const;
    Node* findPrevious(int val, Node *start) const;
    void print(Node *start) const;
};

#endif
