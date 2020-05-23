/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: An example of a circular doubly linked list                        ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## circledoublelist.h
*/

#ifndef CIRCLEDOUBLELIST_H
#define CIRCLEDOUBLELIST_H

#include <iostream>

class CircleDoubleList {
  public:
    CircleDoubleList() : tail(NULL) {};
    CircleDoubleList(const CircleDoubleList& rhs);
    CircleDoubleList operator=(CircleDoubleList rhs);
    ~CircleDoubleList();
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
      Node(int val): data(val), next(this), prev(this) {};
    };
    Node *tail;
    bool insert(int val, Node *&tail);
    bool insert(int val, int key, Node *&tail);
    bool remove(int val, Node *&tail);
    bool replace(int val, int key, Node *&tail);
    Node* find(int val, Node *start) const;
    void print(Node *start) const;
};

#endif
