/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved               ##
## About: An example of a binary search tree implementation                  ##
##        The algorithms in this example are seen in MIT Intro to Algorithms ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## bst.cpp
*/

#include "bst.h"


/*******************************************************************************
* Constructors, Destructors, Operators
*******************************************************************************/

/** BinarySearchTree Copy Assignment Operator
 * @brief Empty the calling object's root BinaryNode, and swap the rhs data
 * + Utilizes the copy-swap-idiom
 *
 * Runs in O( n ) time, since we call makeEmpty() which runs is O( n )
 *
 * @param rhs The BST to copy, beginning from its root BinaryNode
 * @return BinarySearchTree The copied BinarySearchTree object
 */
BinarySearchTree& BinarySearchTree::operator=(BinarySearchTree rhs)
{
  // If the objects are already equal, do nothing
  if (this == &rhs) return *this;
  // Empty this->root
  makeEmpty(root);
  // Copy rhs to this->root
  std::swap(root, rhs.root);
  return *this;
}

/*  BinaryNode Copy Constructor
 * @brief Recursively copy rhs node and all child nodes
 *
 * Runs in O( n ) time, since we visit each node in the BST once
 * + Where n is the total number of nodes within the BST
 *
 * @param rhs An existing BST to initialize this node (and children) with
 */
BinarySearchTree::BinaryNode::BinaryNode(const BinaryNode &rhs)
{
  // Base case, breaks recursion when we hit a null node
  // + Returns to the previous call in the stack
  if (isEmpty(this)) return;
  // Set the element of this BinaryNode to the value in toCopy->element
  element = rhs.element;
  // If there is a left / right node, copy it using recursion
  //  + If there is no left / right node, set them to nullptr
  if (rhs.left != nullptr) {
    left = new BinaryNode(*rhs.left);
    left->parent = this;
  }
  if (rhs.right != nullptr) {
    right = new BinaryNode(*rhs.right);
    right->parent = this;
  }
}


/*******************************************************************************
* Public Member Functions
*******************************************************************************/

/** contains
 * @brief Determines if value exists within a BinaryNode and its children
 *
 * Runs in O( height ) time, given the height of the current BST
 * + In the worst case, we search for a node at the bottom of the BST
 *
 * @param value The value to search for within the BST
 * @param start The root BinaryNode to begin the search
 * @return true If the value is found within the root node or its children
 * @return false If the value is not found within the root node or its children
 */
bool BinarySearchTree::contains(const int &value, BinaryNode *start) const
{
  // If tree is empty
  if (start == nullptr) return false;
    // If x is smaller than our current value
  else if (value < start->element) return contains(value, start->left);
    // If x is larger than our current value, check the right node
  else if (value > start->element) return contains(value, start->right);
  else return true;
}

/** makeEmpty
 * @brief Recursively delete the given root BinaryNode and all of its children
 *
 * Runs in O( n ) time, since we need to visit each node in the tree once
 * + Where n is the total number of nodes in the tree
 *
 * @param tree The root BinaryNode to delete, along with all child nodes
 */
void BinarySearchTree::makeEmpty(BinarySearchTree::BinaryNode * & tree)
{
  // Base case: When all nodes have been deleted, tree is a nullptr
  // + Breaks from recursion
  if (tree != nullptr) {
    makeEmpty(tree->left);
    makeEmpty(tree->right);
    delete tree;
    tree = nullptr;
  }
}

/** insert
 * @brief Insert a value into the tree starting at a given BinaryNode
 * + Uses recursion
 *
 * Runs in O( height ) time, since in the worst case we insert the node at the
 * + bottom of the BST.
 *
 * @param newValue The value to be inserted
 * @param start The BinaryNode to begin insertion
 * @param prevNode The last checked BinaryNode
 * + prevNode is used to initialize new node's parent
 */
void BinarySearchTree::insert(const int &newValue,
                              BinaryNode *&start, BinaryNode *prevNode)
{
  // Base case: We found a valid position which is empty for the newValue
  if (start == nullptr) {
    // Build a new node, place it at the current position
    // + Breaks out of recursion
    start = new BinaryNode(newValue, nullptr, nullptr, prevNode);
  }
  else if (newValue < start->element) insert(newValue, start->left, start);
  else if (newValue > start->element) insert(newValue, start->right, start);
  else return;
}

/** remove
 * @brief Removes a value from the BST of the given BinaryNode
 *
 * Runs in O( height ) time, where findMin() is the limiting function
 * + remove() and transplant() otherwise run in constant time, without findMin()
 *
 * @param removeNode The BinaryNode to remove from the BST
 */
void BinarySearchTree::remove(BinaryNode *removeNode)
{
  if (removeNode->left == nullptr) {
    // removeNode has no left node; Replace removeNode with removeNode->right
    // + It doesn't matter if removeNode->right is nullptr or a valid node
    // + Since there is no left node, this is the only possible valid transplant

    // Transplant the right node and its subtree over this node
    transplant(removeNode, removeNode->right);
  }
  else if (removeNode->right == nullptr) {
    // removeNode has no right node; Replace removeNode with removeNode->right
    // + removeNode->left exists, in this case
    transplant(removeNode, removeNode->left);
  }
  else {
    // removeNode has a right and left node, find the next value in-order
    // + findMin(removeNode->right) returns the next largest value in the BST
    BinaryNode *minNode = findMin(removeNode->right);

    // If the next value in-order is not removeNode->right
    if (minNode->parent != removeNode) {
      // replace minNode with the next largest attached value, minNode->right
      transplant(minNode, minNode->right);
      // Set minNode->right to the node at removeNode->right
      // + Update the parent of removeNode->right accordingly in the next line
      minNode->right = removeNode->right;
      minNode->right->parent = minNode;
    }

    // Replace removeNode with the next node in-order
    // + Update the minNode's left and parent nodes in the following lines
    transplant(removeNode, minNode);
    minNode->left = removeNode->left;
    minNode->left->parent = minNode;
  }
}

/** printInOrder
 * @brief Uses recursion to output left subtree, root node, then right subtrees
 *
 * Runs in O( n ) time, since we need to visit each node in the tree once
 * + Where n is the total number of nodes within the BST
 *
 * @param start The root BinaryNode to begin the 'In Order' output
 */
void BinarySearchTree::printInOrder(BinaryNode *start) const
{
  if(start != nullptr) {
    printInOrder(start->left);
    std::cout << start->element << " ";
    printInOrder(start->right);
  }
}

/** printPostOrder
 * @brief Uses recursion to output left subtree, right subtree, then the root
 *
 * Runs in O( n ) time, since we need to visit each node in the tree once
 * + Where n is the total number of nodes within the BST
 *
 * @param start The root BinaryNode to begin the 'Post Order' output
 */
void BinarySearchTree::printPostOrder(BinaryNode *start) const
{
  if (start != nullptr) {
    printPostOrder(start->left);
    printPostOrder(start->right);
    std::cout << start->element << " ";
  }
}

/** printPreOrder
 * @brief Uses recursion to output the root, then left subtree, right subtrees
 *
 * Runs in O( n ) time, since we need to visit each node in the tree once
 * + Where n is the total number of nodes within the BST
 *
 * @param start The root BinaryNode to begin the 'Pre Order' output
 */
void BinarySearchTree::printPreOrder(BinaryNode *start) const
{
  if (start != nullptr) {
    std::cout << start->element << " ";
    printPreOrder(start->left);
    printPreOrder(start->right);
  }
}

/** search
 * @brief Search for a given value within a tree or subtree using recursion
 *
 * Runs in O( height ) time
 * + In the worst case, we are searching for a node at the bottom of the BST
 *
 * @param value The value to search for
 * @param start The node to start the search from; Can be a subtree
 * @return A pointer to the BinaryNode containing the value within the BST
 * + Returns nullptr if the node was not found
 */
BinarySearchTree::BinaryNode *BinarySearchTree::search(
    const int &value, BinaryNode *start) const
{
  // Base case: If BST is empty, or holds the value we are searching for
  // + Breaks out of recursion
  if (start == nullptr || start->element == value) return start;
  else if (start->element < value) return search(value, start->right);
  else if (start->element > value) return search(value, start->left);
  else return nullptr;
}

/** findMin
 * @brief Find the minimum value within the BST of the given BinaryNode
 *        + This example uses a while loop; findMax uses recursion
 *
 * Runs in O( height ) time
 * + In the worst case, we traverse to to the left-most bottom of the BST
 *
 * @param start The root BinaryNode to begin checking values
 * @return A pointer to the BinaryNode which contains the smallest value
 * + Returns nullptr if BST is empty
 */
BinarySearchTree::BinaryNode * BinarySearchTree::findMin(BinaryNode *start) const
{
  // If our tree is empty
  if (start == nullptr) return nullptr;

  while (start->left != nullptr) start = start->left;

  // If current node has no smaller children, it is min
  return start;
}

/** findMax
 * @brief Find the maximum value within the BST of the given BinaryNode
 *        + This example uses recursion; findMin uses a while loop
 *        ++ Both functions can be implemented using a loop or recursion
 *
 * Runs in O( height ) time
 * + In the worst case, we traverse to to the right-most bottom of the BST
 *
 * @param start The root BinaryNode to begin checking values
 * @return A pointer to the BinaryNode which contains the largest value
 * + returns nullptr if BST is empty
 */
BinarySearchTree::BinaryNode * BinarySearchTree::findMax(BinaryNode *start) const
{
  // If our tree is empty
  if (start == nullptr) return nullptr;

  // Base case: If current node has no larger children, it is max; Break recursion
  if (start->right == nullptr) return start;

  // Move down the right side of our tree and check again
  return findMax(start->right);
}

/** predecessor
 * @brief Finds the previous value in-order from the value at a given startNode
 *
 *  Runs in O( height ) time
 *  + In the worst case we traverse to the bottom of the BST
 *
 * @param startNode The node containing the value to find predecessor of
 * @return The node which is the predecessor of startNode
 */
BinarySearchTree::BinaryNode * BinarySearchTree::predecessor(BinaryNode *startNode) const
{
  if (startNode->left != nullptr) return findMax(startNode->left);

  // If startNode has a parent, walk up the tree until we reach the top
  // + If startNode has no parent, we set it to nullptr and return
  BinaryNode *temp = startNode->parent;
  while (temp != nullptr && temp->left == startNode) {
    startNode = temp;
    temp = temp->parent;
  }
  return temp;
}

/** successor
 * @brief Finds the next value in-order from the value at a given startNode
 *
 *  Runs in O( height ) time
 *  + In the worst case we traverse to the bottom of the BST
 *
 * @param startNode The node containing the value to find successor of
 * @return The node which is the successor of startNode
 */
BinarySearchTree::BinaryNode * BinarySearchTree::successor(BinaryNode *startNode) const
{
  // If there is a right subtree, next value in-order is findMin(rightSubtree)
  if (startNode->right != nullptr) return findMin(startNode->right);

  // If startNode has a parent, walk up the tree until we reach the top
  // + If startNode has no parent, we set it to nullptr and return
  BinaryNode *temp = startNode->parent;
  while (temp != nullptr && temp->right == startNode) {
    startNode = temp;
    temp = temp->parent;
  }
  return temp;
}


/*******************************************************************************
* Private Member Functions
*******************************************************************************/

/** clone
 * @brief Clone a BST node and all its children using recursion
 *
 * Runs in O( n ) time, since each node must be copied individually
 *
 * @param start The node to begin cloning from
 * @return A pointer to the BinaryNode which is root node of the copied tree
 */
BinarySearchTree::BinaryNode * BinarySearchTree::clone(BinaryNode *start)
{
  // Base case: There is nothing to copy, break from recursion
  if (start == nullptr) return nullptr;

  // Construct all child nodes through recursion, return root node
  return new BinaryNode(*start);
}

/** transplant
 * @brief Replaces, or overwrites, a node and with a new node
 * + The subtree attaches to oldNode is replace with that of newNode
 *
 * Runs in constant O( 1 ) time
 * + We only need to check and update values immediately available
 *
 * @param oldNode The node to overwrite with newNode
 * @param newNode The new node to take the place of oldNode
 */
void BinarySearchTree::transplant(BinaryNode *oldNode, BinaryNode *newNode)
{
  // case 1: If oldNode is the root node at this->root
  // + 2: if the oldNode is the left child of it's parent
  // + 3: case if the oldNode  is the right child of  it's parent
  if (oldNode->parent == nullptr) root = newNode;
  else if (oldNode == oldNode->parent->left) {
    // Update the parent of oldNode to reflect the transplant
    oldNode->parent->left = newNode;
  }
  else if (oldNode == oldNode->parent->right) {
    // Update the parent of oldNode to reflect the transplant
    oldNode->parent->right = newNode;
  }

  // If we did not replace oldNode with a nullptr, update newNode's parent
  if (newNode != nullptr) newNode->parent = oldNode->parent;
}
