/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved               ##
## About: An example of a binary search tree implementation                  ##
##        The algorithms in this example are seen in MIT Intro to Algorithms ##
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
  // BinaryNode Structure
  struct BinaryNode{
    int element;
    BinaryNode *left, *right, *parent;

    // Ctor for specific element, lhs, rhs
    BinaryNode(const int &el, BinaryNode *lt, BinaryNode *rt, BinaryNode *p)
        :element(el), left(lt), right(rt), parent(p) {};
    // Ctor for a node and any downstream nodes
    BinaryNode(const BinaryNode &rhs);
  };

  BinarySearchTree() : root(nullptr) {};
  BinarySearchTree(const BinarySearchTree &rhs) :
      root(BinarySearchTree::clone(rhs.root)) {};
  BinarySearchTree& operator=(BinarySearchTree rhs);
  ~BinarySearchTree() { makeEmpty(root);};
  inline BinaryNode * getRoot() const { return root;}

  // Check if value is within the tree or subtree
  inline bool contains(const int &value) const { return contains(value, root);}
  bool contains(const int &value, BinaryNode *start) const;

  // Empties a given tree or subtree
  inline void makeEmpty() { makeEmpty(root);}
  void makeEmpty(BinaryNode *&tree);
  // Checks if this BST is empty
  inline bool isEmpty() const { return isEmpty(root);}
  static inline bool isEmpty(const BinaryNode *rhs) { return rhs == nullptr;}

  // Insert and remove values from a tree or subtree
  inline void insert(const int &x) { insert(x, root, nullptr);}
  void insert(const int &newValue, BinaryNode *&start, BinaryNode *prevNode);
  inline void remove(const int &x) { remove(search(x, root));}
  void remove(BinaryNode *removeNode);

  // Traversal functions
  inline void printInOrder() const { printInOrder(root);}
  inline void printPostOrder() const { printPostOrder(root);}
  inline void printPreOrder() const { printPreOrder(root);}
  // Overloaded to specify traversal of a subtree
  void printInOrder(BinaryNode *start) const;
  void printPostOrder(BinaryNode *start) const;
  void printPreOrder(BinaryNode *start) const;

  // Find a BinaryNode containing value starting at a given tree / subtree node
  inline BinaryNode * search(const int &value) const { return search(value, root);}
  BinaryNode * search(const int &value, BinaryNode *start) const;
  inline BinaryNode * findMin() const { return findMin(root);}
  inline BinaryNode * findMax() const { return findMax(root);}
  // Find nodes with min / max values starting at a given tree / subtree node
  BinaryNode * findMin(BinaryNode *start) const;
  BinaryNode * findMax(BinaryNode *start) const;

  inline BinaryNode * predecessor(const int &value) const
  { return predecessor(search(value));}
  BinaryNode * predecessor(BinaryNode *startNode) const;
  inline BinaryNode * successor(const int &value) const
  { return successor(search(value));}
  BinaryNode * successor(BinaryNode *startNode) const;

private:
  // BST Private Member Functions
  static BinaryNode * clone(BinaryNode *start);
  void transplant(BinaryNode *oldNode, BinaryNode *newNode);

  BinaryNode *root;
};

#endif // BST_H
