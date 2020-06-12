/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: An example of a queue implementation using linked lists            ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## queuelist.h
*/

#ifndef QUEUELIST_H
#define QUEUELIST_H

#include <iostream>

class QueueList {
  public:
    QueueList() : head(NULL), tail(NULL){};
    QueueList(const QueueList& rhs);
    QueueList operator=(QueueList rhs);
    ~QueueList();
    bool enqueue(int val);
    int dequeue();
    int next() const;
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
    Node *head, *tail;
    bool enqueue(int val, Node *&head);
    int dequeue(Node *&tail);
    void print(Node *start) const;
    void makeEmpty(Node *&head);
    
};

#endif
