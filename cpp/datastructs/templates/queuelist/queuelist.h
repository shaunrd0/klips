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


#define TYPE std::string

template <typename T>
class QueueList {
  public:
    QueueList() : head(NULL), tail(NULL){};
    QueueList(const QueueList<T>& rhs);
    QueueList operator=(QueueList<T> rhs);
    ~QueueList();
    bool enqueue(T val);
    T dequeue();
    T next() const;
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
    Node *head, *tail;
    bool enqueue(T val, Node *&head);
    T dequeue(Node *&tail);
    void print(Node *start) const;
    void makeEmpty(Node *&head);
    
};

#endif
