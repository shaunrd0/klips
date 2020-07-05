/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: An example of a binary search tree implementation                  ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## bst.cpp
*/

#include "bst.h"


/********************************************************************************
* Constructors, Destructors, Operators
*********************************************************************************/

/** Default Destructor
 * @brief Destroy the Binary Search Tree:: Binary Search Tree object
 */
BinarySearchTree::~BinarySearchTree()
{
  makeEmpty(root);
}

/** Copy Assignment Operator
 * @brief Empty the calling object's root BinaryNode, and copy the rhs data
 *
 * @param rhs The BST to copy, beginning from its root BinaryNode
 * @return const BinarySearchTree& The copied BinarySearchTree object
 */
const BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& rhs)
{
  // If the objects are already equal, do nothing
  if (this == &rhs) return *this;

  // Empty this->root
  makeEmpty();
  // Copy rhs to this->root
  root = clone(rhs.root);
  return *this;
}


/********************************************************************************
* Public Member Functions
*********************************************************************************/

/** findMin
 * @brief Find and return the minimum value of the calling BST object
 *        Calls to the private member findMin(BinaryNode* t)
 *
 * @return const int& The element of the BinaryNode that holds the lowest value in our tree
 */
const int & BinarySearchTree::findMin() const
{
  return findMin(root)->element;
}

/** findMax
 * @brief Find and return the maximum value of the calling BST object
 *        Calls to the private member findMax(BinaryNode* t)
 *
 * @return const int& The element of the BinaryNode that holds the highest value in our tree
 */
const int & BinarySearchTree::findMax() const
{
  return findMax(root)->element;
}

/** contains
 * @brief Determine whether or not a value exists within the calling BST object
 *        Calls to the private member contains(const int &x, BinaryNode* t)
 *
 * @param x The value to search for within our tree
 * @return true If the value is found within any BinaryNode->element
 * @return false If the value is not found within any BinaryNode->element
 */
bool BinarySearchTree::contains(const int &x) const
{
  return contains(x, root);
}

/** isEmpty
 * @brief Determine wheter or not the calling BST object is empty
 *
 * @return true If this->root node points to an empty tree (NULL)
 * @return false If this->root node points to a constructed BinaryNode
 */
bool BinarySearchTree::isEmpty() // const?
{
  return root == NULL;
}

/** insert
 * @brief Inserts a new value into the calling BST object
 *        Calls to the private member insert(const int &x, BinaryNode* t)
 *
 * @param x The new value to insert into our BinarySearchTree
 */
void BinarySearchTree::insert(const int & x)
{
  insert(x, root);
}

/** remove
 * @brief Remove a value from the calling BST object
 *        Calls to the private member remove(const int &x, BinaryNode* t)
 *
 * @param x The value to remove from our BST
 */
void BinarySearchTree::remove(const int &x)
{
  remove(x, root);
}

/** makeEmpty
 * @brief Delete the root BinaryNode and all of its children from the calling BST object
 *        Calls to the private member makeEmpty(BinaryNode* t)
 */
void BinarySearchTree::makeEmpty()
{
  makeEmpty(root);
}

/** printInOrder
 * @brief Output the element of each BinaryNode between their left and right subtrees
 *        Calls to the private member printInOrder(BinaryNode* t)
 */
void BinarySearchTree::printInOrder() const
{
  printInOrder(root);
}

/** printPostOrder
 * @brief Output the element of each BinaryNode after their left and right subtrees
 *        Calls to the private member printPostOrder(BinaryNode* t)
 */
void BinarySearchTree::printPostOrder() const
{
  printPostOrder(root);
}

/** printPreOrder
 * @brief Output the element of each BinaryNode before their left and right subtrees
 *        Calls to the private member printPreOrder(BinaryNode* t)
 */
void BinarySearchTree::printPreOrder() const
{
  printPreOrder(root);
}


/********************************************************************************
* Private Member Functions
*********************************************************************************/

/** clone
 * @brief Clone a BST node and all its children
 *
 * @param t The node to begin cloning from
 * @return BinarySearchTree::BinaryNode* The root node of the copied tree
 */
BinarySearchTree::BinaryNode * BinarySearchTree::clone(BinaryNode *t) const
{
  // If there is nothing to copy
  if (t == NULL) return NULL;

  // Construct all child nodes through recursion, return root node
  return new BinaryNode(t->element, clone(t->left), clone(t->right));
}

/** insert
 * @brief Insert a value into the BST of the given BinaryNode
 *
 * @param x The value to be inserted
 * @param t The BinaryNode to beign insertion
 */
void BinarySearchTree::insert(const int &x, BinarySearchTree::BinaryNode *&t) const
{
  if (t == NULL)
    t = new BinaryNode(x, NULL, NULL);
  else if (x < t->element)
    insert (x, t->left);
  else if (x > t->element)
    insert (x, t->right);
  else
    return;
}

/** remove
 * @brief Removes a value from the BST of the given BinaryNode
 *
 * @param x The value to be removed
 * @param t The BinaryNode to begin search and removal from
 */
void BinarySearchTree::remove(const int &x, BinarySearchTree::BinaryNode *&t) const
{
  if (t == NULL)
    return;

  if (x < t->element)
    remove(x, t->left);
  else if (x > t->element)
    remove(x, t->right);
  else if (t->left != NULL && t->right != NULL) {
    // If we found the node and there are two branches
    t->element = findMin(t->right)->element;
    std::cout << "Removing [" << t->element << "]...\n";
    remove(t->element, t->right);
  }
  else {
    // If we found the value and there is only one branch
    BinaryNode *oldNode = t;
    t = (t->left != NULL) ? t->left : t->right;
    std::cout << "Removing [" << oldNode->element << "]...\n";
    delete oldNode;
  }
}

/** findMin
 * @brief Find the minimum value within the BST of the given BinaryNode
 *
 * @param t The root BinaryNode to begin checking values
 * @return BinarySearchTree::BinaryNode* The BinaryNode which contains the smallest value (returns NULL if BST is empty)
 */
BinarySearchTree::BinaryNode * BinarySearchTree::findMin(BinarySearchTree::BinaryNode *t) const
{
  while (t != NULL)
    t = t->left;

  // If our tree is empty
  if (t == NULL)
    return NULL;

  // If current node has no smaller children, it is min
  if (t->left == NULL)
    return t;

  // Move down the left side of our tree and check again
  return findMin(t->left);
}

/** findMax
 * @brief Find the maximum value within the BST of the given BinaryNode
 *
 * @param t Te root BinaryNode to begin checking values
 * @return BinarySearchTree::BinaryNode* The BinaryNode which contains the largest value (returns NULL if BST is empty)
 */
BinarySearchTree::BinaryNode * BinarySearchTree::findMax(BinarySearchTree::BinaryNode *t) const
{
  // If our tree is empty
  if (t == NULL)
    return NULL;

  // If current node has no larger children, it is max
  if (t->right == NULL)
    return t;

  // Move down the right side of our tree and check again
  return findMax(t->right);
}

/** contains
 * @brief Determines if the value exists within the given BinaryNode and its children
 *
 * @param x The value to search for within the BST
 * @param t The root BinaryNode to beign the search
 * @return true If the value is found within the root node or any of its children
 * @return false If the value is not found within the root node or any of its children
 */
bool BinarySearchTree::contains(const int &x, BinarySearchTree::BinaryNode *t) const
{
  if (t == NULL) // If tree is empty
    return false;
  else if (x < t->element) // If x is smaller than our current value
    return contains(x, t->left);// Check left node
  else if (x > t->element) // If x is larger than our current value
    return contains(x, t->right); // Check right node
  else
    return true;
}

/** makeEmpty
 * @brief Recursively delete the given root BinaryNode and all of its children
 *
 * @param t The root BinaryNode to delete, along with all child nodes
 */
void BinarySearchTree::makeEmpty(BinarySearchTree::BinaryNode * & t)
{
  if (t != NULL) {
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
  }
  t = NULL;
}

/** printInOrder
 * @brief Output the element of the root nodes between printing their left and right subtrees
 *
 * @param t The root BinaryNode to begin the 'In Order' output
 */
void BinarySearchTree::printInOrder(BinaryNode *t) const
{
  if(t != NULL) {
    printInOrder(t->left);
    std::cout << t->element << " ";
    printInOrder(t->right);
  }
}

/** printPostOrder
 * @brief Output the value of the root nodes only after their subtrees
 *
 * @param t The root BinaryNode to begin the 'Post Order' output
 */
void BinarySearchTree::printPostOrder(BinaryNode *t) const
{
  if (t != NULL) {
    printPostOrder(t->left);
    printPostOrder(t->right);
    std::cout << t->element << " ";
  }
}

/** printPreOrder
 * @brief Output the value of the noot nodes before their subtrees
 *
 * @param t The root BinaryNode to begin the 'Pre Order' output
 */
void BinarySearchTree::printPreOrder(BinaryNode *t) const
{
  if (t != NULL) {
    std::cout << t->element << " ";
    printPreOrder(t->left);
    printPreOrder(t->right);
  }
}