/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: An example of a stack implementation using linked lists            ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## stacklist.h
*/

#ifndef STACKLIST_H
#define STACKLIST_H

#include <iostream>


#define TYPE std::string

template <typename T>
class StackList {
  public:
    StackList() : head(NULL) {};
    StackList(const StackList<T>& rhs);
    StackList operator=(StackList<T> rhs);
    ~StackList();
    bool push(T val);
    T pop();
    T top() const;
    bool isEmpty() const;
    void print() const;
    void makeEmpty();

  private:
    struct Node {
      TYPE data;
      Node *next;
      Node(): data(), next(NULL) {};
      Node(TYPE val): data(val), next(NULL) {};
    };
    Node *head;
    bool push(T val, Node *&head);
    T pop(Node *&head);
    void print(Node *start) const;
    void makeEmpty(Node *&head);
    
};

#endif
