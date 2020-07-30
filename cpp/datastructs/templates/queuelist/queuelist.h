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
    template<typename TY>
    struct Node {
      TY data;
      Node *next;
      Node(): data(), next(NULL) {};
      Node(TY val): data(val), next(NULL) {};
    };
    Node<T> *head, *tail;
    bool enqueue(T val, Node<T> *&head);
    T dequeue(Node<T> *&tail);
    void print(Node<T> *start) const;
    void makeEmpty(Node<T> *&head);
    
};

#endif
