/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: An example of a circular singly linked list                        ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## circlesinglelist.h
*/

#ifndef CIRCLESINGLELIST_H
#define CIRCLESINGLELIST_H

#include <iostream>

class CircleSingleList{
  public:
    CircleSingleList() : tail(NULL) {};
    CircleSingleList(const CircleSingleList& rhs);
    CircleSingleList operator=(CircleSingleList rhs);
    ~CircleSingleList();
    bool insert(int val);
    bool insert(int val, int key);
    bool remove(int val);
    bool replace(int val, int key);
    void makeEmpty();
    bool isEmpty() const;
    void peek() const;
    void print() const;
    bool find(int val) const;

  private:
    struct Node {
      int data;
      Node *next;
      Node(): data(), next(NULL) {};
      Node(int val): data(val), next(this) {};
    };
    Node *tail;
    bool insert(int val, Node *&tail);
    bool insert(int val, int key, Node *&tail);
    bool remove(int val, Node *&tail);
    bool replace(int val, int key, Node *&tail);
    Node* find(int val, Node *start) const;
    Node* findPrevious(int val) const;
    void print(Node *start) const;
};

#endif
