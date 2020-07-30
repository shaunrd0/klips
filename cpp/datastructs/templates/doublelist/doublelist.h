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


#define TYPE std::string

template <typename T>
class DoubleList {
  public:
    DoubleList() : head(NULL) {};
    DoubleList(const DoubleList& rhs);
    DoubleList operator=(DoubleList rhs);
    ~DoubleList();
    bool insert(T val);
    bool insert(T val, T key);
    bool remove(T val);
    bool replace(T val, T key);
    void makeEmpty();
    bool isEmpty() const;
    T peek() const;
    void print() const;
    bool find(T val) const;

  private:
    struct Node {
      TYPE data;
      Node *next, *prev;
      Node(): data(), next(NULL), prev(NULL) {};
      Node(TYPE val): data(val), next(NULL), prev(NULL) {};
    };
    Node *head;
    bool insert(T val, Node *&head);
    bool insert(T val, T key, Node *&head);
    bool remove(T val, Node *&head);
    bool replace(T val, T key, Node *&head);
    Node* find(T val, Node *start) const;
    void print(Node *start) const;
};

#endif
