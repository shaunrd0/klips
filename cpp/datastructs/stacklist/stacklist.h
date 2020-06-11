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

class StackList {
  public:
    StackList() : head(NULL) {};
    StackList(const StackList& rhs);
    StackList operator=(StackList rhs);
    ~StackList();
    bool push(int val);
    int pop();
    int top() const;
    bool isEmpty() const;
    void print() const;
    void makeEmpty();

  private:
    struct Node {
      int data;
      Node *next;
      Node(): data(), next(NULL) {};
      Node(int val): data(val), next(NULL) {};
    };
    Node *head;
    bool push(int val, Node *&head);
    int pop(Node *&head);
    void print(Node *start) const;
    void makeEmpty(Node *&head);
    
};

#endif
