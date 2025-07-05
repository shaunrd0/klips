/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved               ##
## About: An example of a red black tree implementation                      ##
##        The algorithms in this example are seen in MIT Intro to Algorithms ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
*/

#ifndef REDBLACK_H
#define REDBLACK_H

#include <iostream>
#include <cstdint>

enum Color {Black, Red};

class RedBlackTree {

public:
  // RedBlackNode Structure
  struct RedBlackNode{
    int element;
    Color color = Black;
    RedBlackNode *left{}, *right{}, *parent{};

    RedBlackNode() : element(INT32_MIN), color(Black) {}
    // Ctor for specific element, lhs, rhs
    RedBlackNode(const int &el, Color c,
                 RedBlackNode *lt, RedBlackNode *rt, RedBlackNode *p)
        :element(el), color(c), left(lt), right(rt), parent(p) {};
    // Ctor for copying a node and any downstream nodes
    RedBlackNode(const RedBlackNode &toCopy);
  };
  static RedBlackNode *nil;

  RedBlackTree() : root(nil) {};
  RedBlackTree(const RedBlackTree &rhs);;
  RedBlackTree& operator=(RedBlackTree rhs);
  ~RedBlackTree() { makeEmpty(root);};
  // Inlined functions provide less verbose interface for using the RBT
  inline RedBlackNode * getRoot() const { return root;}

  void rotateLeft(RedBlackNode *pivotNode);
  void rotateRight(RedBlackNode *pivotNode);
  void insertFixup(RedBlackNode * start);
  void deleteFixup(RedBlackNode * start);

  // Check if value is within the tree or subtree
  inline bool contains(const int &value) const { return contains(value, root);}
  bool contains(const int &value, RedBlackNode *start) const;

  // Empties a given tree or subtree
  inline void makeEmpty() { makeEmpty(root);}
  void makeEmpty(RedBlackNode *&tree);
  // Checks if this RBT is empty
  bool isEmpty() const;

  // Insert and remove values from a tree or subtree
  inline void insert(const int &x) { insert(x, root, nil);}
  void insert(const int &newValue, RedBlackNode *&start, RedBlackNode *prevNode);
  inline void remove(const int &x) { remove(search(x, root));}
  void remove(RedBlackNode *removeNode);

  // Traversal functions
  inline void printInOrder() const { printInOrder(root);}
  inline void printPostOrder() const { printPostOrder(root);}
  inline void printPreOrder() const { printPreOrder(root);}
  // Overloaded to specify traversal of a subtree
  void printInOrder(RedBlackNode *start) const;
  void printPostOrder(RedBlackNode *start) const;
  void printPreOrder(RedBlackNode *start) const;

  // Find a BinaryNode containing value starting at a given tree / subtree node
  inline RedBlackNode * search(const int &value) const
      { return search(value, root);}
  RedBlackNode * search(const int &value, RedBlackNode *start) const;

  inline RedBlackNode * findMin() const { return findMin(root);}
  inline RedBlackNode * findMax() const { return findMax(root);}
  // Find nodes with min / max values starting at a given tree / subtree node
  RedBlackNode * findMin(RedBlackNode *start) const;
  RedBlackNode * findMax(RedBlackNode *start) const;

  inline RedBlackNode * predecessor(const int &value) const
      { return predecessor(search(value));}
  RedBlackNode * predecessor(RedBlackNode *startNode) const;
  inline RedBlackNode * successor(const int &value) const
      { return successor(search(value));}
  RedBlackNode * successor(RedBlackNode *startNode) const;

private:
  RedBlackNode * clone(RedBlackNode *start);
  void transplant(RedBlackNode *oldNode, RedBlackNode *newNode);

  // The root node for the RBT
  RedBlackNode *root;
};

#endif // REDBLACK_H
