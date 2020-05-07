/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: An example of a doubly linked list                                 ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## doublelist.h
*/

#ifndef DOUBLELIST_H
#define DOUBLELIST_H

#include <iostream>

class DoubleList {
  public:
    DoubleList() : head(NULL) {};
    DoubleList(const DoubleList& rhs);
    DoubleList operator=(DoubleList rhs);
    ~DoubleList();
    bool insert(int val);
    bool insert(int val, int key);
    bool remove(int val);
    bool replace(int val, int key);
    void makeEmpty();
    bool isEmpty() const;
    int peek() const;
    void print() const;
    bool find(int val) const;

  private:
    struct Node {
      int data;
      Node *next, *prev;
      Node(): data(), next(NULL), prev(NULL) {};
      Node(int val): data(val), next(NULL), prev(NULL) {};
    };
    Node *head;
    bool insert(int val, Node *&head);
    bool insert(int val, int key, Node *&head);
    bool remove(int val, Node *&head);
    bool replace(int val, int key, Node *&head);
    Node* find(int val, Node *start) const;
    void print(Node *start) const;
};

#endif
