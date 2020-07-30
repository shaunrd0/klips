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
    template <typename TY>
    struct Node {
      TY data;
      Node *next, *prev;
      Node(): data(), next(NULL), prev(NULL) {};
      Node(T val): data(val), next(NULL), prev(NULL) {};
    };
    Node<T> *head;
    bool insert(T val, Node<T> *&head);
    bool insert(T val, T key, Node<T> *&head);
    bool remove(T val, Node<T> *&head);
    bool replace(T val, T key, Node<T> *&head);
    Node<T>* find(T val, Node<T> *start) const;
    void print(Node<T> *start) const;
};

#endif
