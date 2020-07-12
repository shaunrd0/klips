/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: An example of a binary search tree implementation                  ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## bst.h
*/

#ifndef BST_H
#define BST_H

#include <iostream>

// TODO: Add balance() method to balance overweight branches
class BinarySearchTree {

  public:
    BinarySearchTree() : root(NULL) {};
    BinarySearchTree(const BinarySearchTree &rhs) : root(rhs.clone(rhs.root)) {};
    const BinarySearchTree& operator=(const BinarySearchTree& rhs);
    ~BinarySearchTree();
    const int & findMin() const;
    const int & findMax() const;
    bool contains(const int &x) const;
    bool isEmpty() const;
    void insert(const int &x);
    void remove(const int &x);
    void makeEmpty();
    void printInOrder() const;
    void printPostOrder() const;
    void printPreOrder() const;

  private:
    struct BinaryNode{
      int element;
      BinaryNode *left;
      BinaryNode *right;
      BinaryNode(const int &el, BinaryNode *lt, BinaryNode *rt)
          :element(el), left(lt), right(rt) {};
    };
    BinaryNode *root;
    BinaryNode * clone(BinaryNode *t) const;
    void insert(const int &x, BinaryNode *&t) const;
    void remove(const int &x, BinaryNode *&t) const;
    BinaryNode * findMin(BinaryNode *t) const;
    BinaryNode * findMax(BinaryNode *t) const;
    bool contains(const int &x, BinaryNode *t) const;
    void makeEmpty(BinaryNode * & t);
    void printInOrder(BinaryNode *t) const;
    void printPostOrder(BinaryNode *t) const;
    void printPreOrder(BinaryNode *t) const;
};

#endif //BST_H
