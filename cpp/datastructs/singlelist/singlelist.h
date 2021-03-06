/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: An example of a singly linked list                                 ##
##                                                                           ##
## Structure:   Remove:         Insert:      Insert at:   Replace:           ##
## o-o-o-o-o-o  o-o--x-->o-o-o  o                o            o              ##
##                              |               /|           / \             ##
##                              o-o-o-o-o-o  o-o~o-o-o-o  o-o~x~o-o-o        ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## singlelist.h
*/

#ifndef SINGLELIST_H
#define SINGLELIST_H

#include <iostream>

class SingleList{
  public:
    SingleList() : head(NULL) {};
    SingleList(const SingleList& rhs);
    SingleList operator=(SingleList rhs);
    ~SingleList();
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
      Node *next;
      Node(): data(), next(NULL) {};
      Node(int val): data(val), next(NULL) {};
    };
    Node *head;
    bool insert(int val, Node *&head);
    bool insert(int val, int key, Node *&head);
    bool remove(int val, Node *&head);
    bool replace(int val, int key, Node *&head);
    Node* find(int val, Node *start) const;
    Node* findPrevious(int val, Node *start) const;
    void print(Node *start) const;
};

#endif
