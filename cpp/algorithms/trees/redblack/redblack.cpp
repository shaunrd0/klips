/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: An example of a red-black tree implementation                      ##
##        The algorithms in this example are seen in MIT Intro to Algorithms ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
*/

#include "redblack.h"


/*******************************************************************************
* Constructors, Destructors, Operators
*******************************************************************************/

// Use a static member for nil
// + All RBTs will share this value to represent values Not In the List
RedBlackTree::RedBlackNode *RedBlackTree::nil = new RedBlackTree::RedBlackNode();


/*  RedBlackNode Copy Constructor
 *
 * Runs in O( n ) time, since we visit each node in the RBT once
 * + Where n is the total number of nodes within the RBT
 *
 * @param rhs An existing RBT to initialize this node (and children) with
 */
RedBlackTree::RedBlackNode::RedBlackNode(RedBlackNode * toCopy)
{
  // Base case, breaks recursion when we hit a null node
  // + Returns to the previous call in the stack
  if (toCopy == nil) return;
  // Set the element of this RedBlackNode to the value in toCopy->element
  element = toCopy->element;
  // If there is a left / right node, copy it using recursion
  //  + If there is no left / right node, set them to nullptr
  if (toCopy->left != nil) {
    left = new RedBlackNode(toCopy->left);
    left->parent = this;
  }
  else left = nil;

  if (toCopy->right != nil) {
    right = new RedBlackNode(toCopy->right);
    right->parent = this;
  }
  else right = nil;

  if (toCopy->parent == nil) parent = nil;

  // TODO: Fix the copying of the RBT
  color = toCopy->color;
}

/** RedBlackTree Copy Assignment Operator
 * @brief Empty the calling object's root RedBlackNode, and copy the rhs data
 *
 * Runs in O( n ) time, since we visit each node in the RBT once
 * + Where n is the total number of nodes within the RBT
 *
 * makeEmpty() and clone() are both O( n ), and we call each sequentially
 * + This would appear to be O( 2n ), but we drop the constant of 2
 *
 * @param rhs The RBT to copy, beginning from its root RedBlackNode
 * @return RedBlackTree The copied RedBlackTree object
 */
RedBlackTree& RedBlackTree::operator=(const RedBlackTree &rhs)
{
  // If the objects are already equal, do nothing
  if (this == &rhs) return *this;

  // Empty this->root
  makeEmpty(root);

//  if (root == nil) root = new RedBlackNode();
  // Copy rhs to this->root
  root = clone(rhs.root);
  return *this;
}

RedBlackTree::RedBlackTree(const RedBlackTree &rhs) {
  root = clone(rhs.getRoot());
}

/*******************************************************************************
* Public Member Functions
*******************************************************************************/

/** contains
 * @brief Determines if value exists within a RedBlackNode and its children
 *
 * Runs in O( height ) time, given the height of the current RBT
 * + In the worst case, we search for a node at the bottom of the RBT
 *
 * @param value The value to search for within the RBT
 * @param start The root RedBlackNode to begin the search
 * @return true If the value is found within the root node or its children
 * @return false If the value is not found within the root node or its children
 */
bool RedBlackTree::contains(const int &value, RedBlackNode *start) const
{
  // If tree is empty
  if (start == nil) return false;
    // If x is smaller than our current value
  else if (value < start->element) return contains(value, start->left);
    // If x is larger than our current value, check the right node
  else if (value > start->element) return contains(value, start->right);
  else return true;
}

/** rotateLeft
 * @brief Rotates a node and it's children counter-clockwise around a pivotNode
 *
 * Runs in O( 1 ) constant time, only immediately available values are used
 *
 * @param pivotNode The node to begin rotation from
 */
void RedBlackTree::rotateLeft(RedBlackNode *pivotNode)
{
  // To rotateRight, we must relocate the rightChild node
  RedBlackNode *rightChild = pivotNode->right;

  pivotNode->right = rightChild->left;
  // If the rightChild->left node exists, update it's parent to the pivotNode
  if (rightChild->left != nil) rightChild->left->parent = pivotNode;
  // After we rotateLeft, the rightChild will be in the position of pivotNode
  // + So we update rightChild->parent to reflect this
  rightChild->parent = pivotNode->parent;

  // The following conditions relocate the rightChild to its new position
  // Case 1: pivotNode has no parent, so it must be the rootNode
  // Case 2: pivotNode is the left child of its parent node
  // Case 2: pivotNode is the right child of its parent node
  if (pivotNode->parent == nil) root = rightChild;
  else if (pivotNode == pivotNode->parent->left) {
    pivotNode->parent->left = rightChild;
  }
  else pivotNode->parent->right = rightChild;

  // The rightChild is now the parent of pivotNode
  // + Since we rotated left, set rightChild->left to point to the pivotNode
  // + Update the pivotNode->parent to reflect this
  rightChild->left = pivotNode;
  pivotNode->parent = rightChild;
}

/** rotateRight
 * @brief Rotates a node and it's children clockwise around a pivotNode
 *
 * Runs in O( 1 ) constant time, only immediately available values are used
 *
 * @param pivotNode The node to begin rotation from
 */
void RedBlackTree::rotateRight(RedBlackTree::RedBlackNode *pivotNode)
{
  // To rotateRight, we must relocate the leftChild node
  RedBlackNode *leftChild = pivotNode->left;

  pivotNode->left = leftChild->right;
  // If the leftChild->left node exists, update it's parent to the pivotNode
  if (leftChild->left != nil) leftChild->right->parent = pivotNode;
  // After we rotateRight, the leftChild will be in the position of pivotNode
  // + So we update leftChild->parent to reflect this
  leftChild->parent = pivotNode->parent;

  // The following conditions relocate the leftChild to its new position
  // Case 1: pivotNode has no parent, so it must be the rootNode
  // Case 2: pivotNode is the left child of its parent node
  // Case 2: pivotNode is the right child of its parent node
  if (pivotNode->parent == nil) root = leftChild;
  else if (pivotNode == pivotNode->parent->left) {
    pivotNode->parent->left = leftChild;
  }
  else pivotNode->parent->right = leftChild;

  // The leftChild is now the parent of pivotNode
  // + Since we rotated right, set leftChild->right to point to the pivotNode
  // + Update the pivotNode->parent to reflect this
  leftChild->right = pivotNode;
  pivotNode->parent = leftChild;
}

/** insertFixup
 * @brief Corrects RBT properties to enforce proper node colors after insertion
 *
 * Runs in O( lg(n) ) time, where n is the number of nodes in the RBT
 *
 * @param start The node to begin the fixup operation from
 */
void RedBlackTree::insertFixup(RedBlackTree::RedBlackNode *start)
{
  // While the parent of start node is valid and colored red
  // + Check for the two red nodes in a row, and update their colors
  while (start->parent != nil && start->parent->color == Red) {

    // If the parent of start node is a *left* child
    if (start->parent == start->parent->parent->left) {
      // Check the *right* uncle node to enforce RBT properties
      // + Since the start->parent->right would be the start node's sibling
      // ++ The start->parent->parent->left would be the start node's uncle
      RedBlackNode *uncleNode = start->parent->parent->right;

      // If the uncleNode is red, we are in case 1
      // + In case 1, start->parent->color and uncleNode->color are both Red
      if (uncleNode->color == Red) {
        start->parent->color = Black;
        uncleNode->color = Black;
        start->parent->parent->color = Red;
        // Advance start to it's grandparent node
        start = start->parent->parent;
      }
      else { // Otherwise, if case 1 is not violated...

        // If the start node is a right child, we are in case 2
        // + In case 2, uncleNode is Black, and start node is a right child
        if (start == start->parent->right) {
          // Advance start up the tree to it's parent node, then *rotateLeft*
          start = start->parent;
          rotateLeft(start);
          // After this rotation, we have forced ourselves into case 3
          // + So, whether this case (2) executes or not, we end up in case 3
        }

        // No need for an if statement here, since the start node must be either
        // + a right or left child. It cannot be neither always run these steps.
        // ++ The only time these steps are skipped, is when we are in case 1

        // Start node is a left child, we are in case 3
        // + In case 3, uncleNode is Black and start node is a left child
        start->parent->color = Black;
        start->parent->parent->color = Red;
        // Rotate around the grandparent node
        rotateRight(start->parent->parent);
      }

    }
    else { // If the parent of start node is a *right* child
      // We follow the same 3 cases as above..
      // + but with all left / right rotations and references swapped

      // Check the *left* uncle node to enforce RBT properties
      RedBlackNode *uncleNode = start->parent->parent->left;
      // If the uncleNode is red, we are in case 1
      if (uncleNode != nil && uncleNode->color == Red) {
        start->parent->color = Black;
        uncleNode->color = Black;
        start->parent->parent->color = Red;
        // Advance start to it's grandparent node
        start = start->parent->parent;
      }
      else { // Otherwise, if case 1 is not violated...

        // If the start node is a left child, we are in case 2
        if (start == start->parent->left) {
          // Advance start up the tree to it's parent node, then *rotateRight*
          start = start->parent;
          rotateRight(start);
          // After this rotation, we have forced ourselves into case 3
          // + So, whether this case (2) executes or not, we end up in case 3
        }

        // The only time these steps are skipped, is when we are in case 1
        // + Always perform these steps when not in case 1

        // Start node is a *right* child, we are in case 3
        start->parent->color = Black;
        start->parent->parent->color = Red;
        // Rotate around the grandparent node
        rotateLeft(start->parent->parent);
      }
    }

    // The while() loop will always terminate after case 2 and (or) 3 is ran
  }

  // The root of the RBT should always be black
  root->color = Black;
}

/** deleteFixup
 * @brief Corrects RBT properties to enforce proper node colors after removal
 *
 * Runs in O( lg(n) ) time, where n is the number of nodes in the RBT
 *
 * @param start The node to begin the fixup operation from
 */
void RedBlackTree::deleteFixup(RedBlackTree::RedBlackNode *start)
{
  // Until we reach the root of the RBT, move the extra black node up the tree
  while (start != root && start->color == Black) {
    // If the start node is a *left* child
    if (start == start->parent->left) {

      RedBlackNode *siblingNode = start->parent->right;
      // If start node's siblingNode is colored Red, we are in case 1
      // + In case 1, the only requirement is siblingNode is Red
      if (siblingNode->color == Red) {
        // Color the siblingNode Black, and the start->parent node Red
        siblingNode->color = Black;
        start->parent->color = Red;

        // rotateLeft around the parent node, and update the siblingNode
        // + siblingNode now represents the new sibling
        // + start->parent is now a Red node with two Black siblings
        // ++ This is ideal, since Red nodes can only have Black children nodes
        rotateLeft(start->parent);
        siblingNode = start->parent->right;
      }

      // If the siblingNode is Black, we are in case 2
      // + In case 2, siblingNode is Black and has two Black children nodes
      if (siblingNode->left->color == Black && siblingNode->right->color == Black) {
        // Color the siblingNode Red and advance start node up the tree
        siblingNode->color = Red;
        start = start->parent;
      }
      else { // If either one of the siblingNode's children are Red...

        // If the siblingNode->right child node is Black, we are in case 3
        // + In case 3, the start node's siblingNode is black
        // ++ And the siblingNode's right child is Black
        if (siblingNode->right->color == Black) {
          // Color the left child of siblingNode Black, and siblingNode to Red
          siblingNode->left->color = Black;
          siblingNode->color = Red;

          // rotateRight(siblingNode) places the Red siblingNode as the right
          // + child of the previous siblingNode->left
          rotateRight(siblingNode);
          // Update the siblingNode of start node to reflect the new sibling
          siblingNode = start->parent->right;
          // After rotateRight(siblingNode), we have put ourselves into case 4
        }

        // siblingNode->left is colored Black, we are in case 4
        // + In case 4, the start node's sibling is Black
        // ++ And the siblingNode's right child is Red
        siblingNode->color = start->parent->color;
        start->parent->color = Black;
        siblingNode->right->color = Black;
        // rotateLeft around the start->parent node, placing the siblingNode
        // + In the previous position of the start->parent node
        rotateLeft(start->parent);
        // The previous start->parent node is now siblingNode's left child

        // Setting the start node to root node ensures the while() terminates
        start = root;
      }
    }
    else { // If the start node is a right child
      // We follow the same 3 cases as above..
      // + but with all left / right rotations and references swapped

      RedBlackNode *siblingNode = start->parent->left;
      // If start node's siblingNode is colored Red, we are in case 1
      if (siblingNode->color == Red) {
        // Color the siblingNode Black, and the start->parent node Red
        siblingNode->color = Black;
        start->parent->color = Red;

        // *rotateRight* around the parent node, and update the siblingNode
        rotateRight(start->parent);
        siblingNode = start->parent->left;
      }

      // If the siblingNode is Black, we are in case 2
      if (siblingNode->left->color == Black && siblingNode->right->color == Black) {
        siblingNode->color = Red;
        start = start->parent;
      }
      else { // If either one of the siblingNode's children are Red...

        // If the siblingNode->left child node is Black, we are in case 3
        if (siblingNode->left->color == Black) {
          // Color the *left* child of siblingNode Black, and siblingNode to Red
          siblingNode->right->color = Black;
          siblingNode->color = Red;

          // rotateLeft(siblingNode) places the Red siblingNode as the *left*
          // + child of the previous siblingNode->right
          rotateLeft(siblingNode);
          // Update the siblingNode of start node to reflect the new sibling
          siblingNode = start->parent->left;
          // After rotateRight(siblingNode), we have put ourselves into case 4
        }

        // siblingNode->left is colored Black, we are in case 4
        siblingNode->color = start->parent->color;
        start->parent->color = Black;
        siblingNode->left->color = Black;

        // rotateRight around the start->parent node, placing the siblingNode
        // + In the previous position of the start->parent node
        rotateRight(start->parent);

        // Setting the start node to root node ensures the while() terminates
        start = root;
      }
    }

  }

  // TODO: I could only get this working by using nil->parent
  //   to store the parent of the last replacementNode within removeNode()
  //   Is this expected, or have I missed something and hacked this?

  // Update nil->parent to nullptr if it is any other value
  // + When we transplant(), we temporarily store the parent of the relocatedNode
  // + relocatedNode is seen passed to transplant() within remove()
  if (nil->parent != nullptr) nil->parent = nullptr;
}

/** makeEmpty
 * @brief Recursively delete the given root RedBlackNode and all of its children
 *
 * Runs in O( n ) time, since we need to visit each node in the tree once
 * + Where n is the total number of nodes in the tree
 *
 * @param tree The root RedBlackNode to delete, along with all child nodes
 */
void RedBlackTree::makeEmpty(RedBlackTree::RedBlackNode * & tree)
{
  // Base case: When all nodes have been deleted, tree is a nullptr
  // + Breaks from recursion
  if (tree != nil) {
    makeEmpty(tree->left);
    makeEmpty(tree->right);
    delete tree;
    // Set each deleted node = nil, overwriting unused children with nullptr
    tree = nil;
  }

}

/** isEmpty
 * @brief Determine whether or not the calling RBT object is empty
 *
 * Runs in constant time, O( 1 )
 *
 * @return true If this->root node points to an empty tree (nullptr)
 * @return false If this->root node points to a constructed RedBlackNode
 */
bool RedBlackTree::isEmpty() const
{
  return root == nil;
}

/** insert
 * @brief Insert a value into the tree starting at a given RedBlackNode
 * + Uses recursion
 *
 * Runs in O( lg(n) ) time, since the height of RBTs are <= lg(n)
 * + Where n is the number of nodes in the RBT
 * + The *sequential* call to insertFixup is also O( lg(n) )..
 * ++ Appears to be O( 2lg(n) ), but we drop the constant 2; No extra overhead
 *
 * @param newValue The value to be inserted
 * @param start The RedBlackNode to begin insertion
 * @param prevNode The last checked RedBlackNode
 * + prevNode is used to initialize new node's parent
 */
void RedBlackTree::insert(const int &newValue,
                          RedBlackNode *&start, RedBlackNode *prevNode)
{
  // Base case: We found a valid position which is empty for the newValue
  if (start == nil) {
    // Build a new node, place it at the current position
    // + Breaks out of recursion after this code block finishes

    // TODO: Valgrind thinks there is a memory leak here
    //   It seems to me that calling `delete start` would delete the static nil?
    start = new RedBlackNode(newValue, Red, nil, nil, prevNode);

    // Enforce RBT properties on the entire subtree of start node
    // + By default, start is the root node of the RBT unless specified
    // + This is done with a call to the inlined insert(int) function
    insertFixup(start);
  }
  else if (newValue < start->element) insert(newValue, start->left, start);
  else if (newValue > start->element) insert(newValue, start->right, start);
  else return;
}

/** remove
 * @brief Removes a value from the RBT of the given RedBlackNode
 *
 * Runs in O( lg(n) ) time, since the height of RBTs are <= lg(n)
 * + Where n is the number of nodes in the RBT
 * + The *sequential* call to removeFixup is also O( lg(n) )..
 * ++ Appears to be O( 2lg(n) ), but we drop the constant 2; No extra overhead
 *
 * @param removeNode The RedBlackNode to remove from the RBT
 */
void RedBlackTree::remove(RedBlackNode *removeNode)
{
  RedBlackNode *replacementNode = removeNode;
  Color originalColor = removeNode->color;

  // This node will be passed to removeFixup() later to enforce RBT properties
  RedBlackNode *fixupNode;

  if (removeNode->left == nil) {
    // removeNode has no left node; Replace removeNode with removeNode->right
    // + It doesn't matter if removeNode->right is nullptr or a valid node
    // + Since there is no left node, this is the only possible valid transplant

    // Transplant the right node and its subtree over this node
    fixupNode = removeNode->right;
    transplant(removeNode, removeNode->right);
  }
  else if (removeNode->right == nil) {
    // removeNode has no right node; Replace removeNode with removeNode->right
    // + removeNode->left exists, in this case
    fixupNode = removeNode->left;
    transplant(removeNode, removeNode->left);
  }
  else {
    // The node to remove has both left and right child nodes
    // + We should find a replacement within the child with a larger subtree

    // Compare the depth of subtrees for both children of removeNode...
    // + Red child node indicates the equal or longer subtree
    // + Black child node indicates the depth of the child's subtree is smaller
    if (removeNode->left->color) {
      // + findMax(removeNode->right) returns the next smallest value in the RBT
      replacementNode = findMax(removeNode->left);
      originalColor = replacementNode->color;

      fixupNode = replacementNode->right;

      if (replacementNode->parent == removeNode) {
        fixupNode->parent = replacementNode;
      }
      else {
        transplant(replacementNode, replacementNode->right);
        replacementNode->right = removeNode->right;
        replacementNode->right->parent = replacementNode;
      }
      transplant(removeNode, replacementNode);
      replacementNode->left = removeNode->left;
      replacementNode->left->parent = replacementNode;
      replacementNode->color = removeNode->color;
    }
    else {
      // If the removeNode->left child is black, use the right subtree
      // + findMin(removeNode->right) returns the next largest value in the RBT
      replacementNode = findMin(removeNode->right);
      originalColor = replacementNode->color;
      fixupNode = replacementNode->right;

      if (replacementNode->parent == removeNode) {
        fixupNode->parent = replacementNode;
      }
      else {
        transplant(replacementNode, replacementNode->right);
        replacementNode->right = removeNode->right;
        replacementNode->right->parent = replacementNode;
      }
      transplant(removeNode, replacementNode);
      replacementNode->left = removeNode->left;
      replacementNode->left->parent = replacementNode;
      replacementNode->color = removeNode->color;

    }
  }

  // If originalColor of the replacementNode is black, enforce RBT properties
  if (!originalColor) deleteFixup(fixupNode);
}

/** printInOrder
 * @brief Uses recursion to output left subtree, root node, then right subtrees
 *
 * Runs in O( n ) time, since we need to visit each node in the tree once
 * + Where n is the total number of nodes within the RBT
 *
 * @param start The root RedBlackNode to begin the 'In Order' output
 */
void RedBlackTree::printInOrder(RedBlackNode *start) const
{
  if(start != nil) {
    printInOrder(start->left);
    std::cout << start->element << " ";
    printInOrder(start->right);
  }
}

/** printPostOrder
 * @brief Uses recursion to output left subtree, right subtree, then the root
 *
 * Runs in O( n ) time, since we need to visit each node in the tree once
 * + Where n is the total number of nodes within the RBT
 *
 * @param start The root RedBlackNode to begin the 'Post Order' output
 */
void RedBlackTree::printPostOrder(RedBlackNode *start) const
{
  if (start != nil) {
    printPostOrder(start->left);
    printPostOrder(start->right);
    std::cout << start->element << " ";
  }
}

/** printPreOrder
 * @brief Uses recursion to output the root, then left subtree, right subtrees
 *
 * Runs in O( n ) time, since we need to visit each node in the tree once
 * + Where n is the total number of nodes within the RBT
 *
 * @param start The root RedBlackNode to begin the 'Pre Order' output
 */
void RedBlackTree::printPreOrder(RedBlackNode *start) const
{
  if (start != nil) {
    std::cout << start->element << " ";
    printPreOrder(start->left);
    printPreOrder(start->right);
  }
}

/** search
 * @brief Search for a given value within a tree or subtree using recursion
 *
 * Runs in O( height ) time
 * + In the worst case, we are searching for a node at the bottom of the RBT
 *
 * @param value The value to search for
 * @param start The node to start the search from; Can be a subtree
 * @return A pointer to the RedBlackNode containing the value within the RBT
 * + Returns nullptr if the node was not found
 */
RedBlackTree::RedBlackNode *RedBlackTree::search(
    const int &value, RedBlackNode *start) const
{
  // Base case: If RBT is empty, or holds the value we are searching for
  // + Breaks out of recursion
  if (start == nil || start->element == value) return start;
  else if (start->element < value) return search(value, start->right);
  else if (start->element > value) return search(value, start->left);
}

/** findMin
 * @brief Find the minimum value within the RBT of the given RedBlackNode
 *        + This example uses a while loop; findMax uses recursion
 *
 * Runs in O( height ) time
 * + In the worst case, we traverse to to the left-most bottom of the RBT
 *
 * @param start The root RedBlackNode to begin checking values
 * @return A pointer to the RedBlackNode which contains the smallest value
 * + Returns nullptr if RBT is empty
 */
RedBlackTree::RedBlackNode * RedBlackTree::findMin(RedBlackNode *start) const
{
  // If our tree is empty
  if (start == nil) return nullptr;

  while (start->left != nil) start = start->left;

  // If current node has no smaller children, it is min
  return start;
}

/** findMax
 * @brief Find the maximum value within the RBT of the given RedBlackNode
 *        + This example uses recursion; findMin uses a while loop
 *        ++ Both functions can be implemented using a loop or recursion
 *
 * Runs in O( height ) time
 * + In the worst case, we traverse to to the right-most bottom of the RBT
 *
 * @param start The root RedBlackNode to begin checking values
 * @return A pointer to the RedBlackNode which contains the largest value
 * + returns nullptr if RBT is empty
 */
RedBlackTree::RedBlackNode * RedBlackTree::findMax(RedBlackNode *start) const
{
  // If our tree is empty
  if (start == nil) return nullptr;

  // Base case: If current node has no larger children, it is max; Break recursion
  if (start->right == nil) return start;

  // Move down the right side of our tree and check again
  return findMax(start->right);
}

/** predecessor
 * @brief Finds the previous value in-order from the value at a given startNode
 *
 *  Runs in O( height ) time
 *  + In the worst case we traverse to the bottom of the RBT
 *
 * @param startNode The node containing the value to find predecessor of
 * @return The node which is the predecessor of startNode
 */
RedBlackTree::RedBlackNode * RedBlackTree::predecessor(RedBlackNode *startNode) const
{
  if (startNode->left != nil) return findMax(startNode->left);

  // If startNode has a parent, walk up the tree until we reach the top
  // + If startNode has no parent, we set it to nullptr and return
  RedBlackNode *temp = startNode->parent;
  while (temp != nil && temp->left == startNode) {
    startNode = temp;
    temp = temp->parent;
  }
  return temp;
}

/** successor
 * @brief Finds the next value in-order from the value at a given startNode
 *
 *  Runs in O( height ) time
 *  + In the worst case we traverse to the bottom of the RBT
 *
 * @param startNode The node containing the value to find successor of
 * @return The node which is the successor of startNode
 */
RedBlackTree::RedBlackNode * RedBlackTree::successor(RedBlackNode *startNode) const
{
  // If there is a right subtree, next value in-order is findMin(rightSubtree)
  if (startNode->right != nil) return findMin(startNode->right);

  // If startNode has a parent, walk up the tree until we reach the top
  // + If startNode has no parent, we set it to nullptr and return
  RedBlackNode *temp = startNode->parent;
  while (temp != nil && temp->right == startNode) {
    startNode = temp;
    temp = temp->parent;
  }
  return temp;
}


/*******************************************************************************
* Private Member Functions
*******************************************************************************/

/** clone
 * @brief Clone a RBT node and all its children using recursion
 *
 * Runs in O( n ) time, since each node must be copied individually
 *
 * @param start The node to begin cloning from
 * @return A pointer to the RedBlackNode which is root node of the copied tree
 */
RedBlackTree::RedBlackNode * RedBlackTree::clone(RedBlackNode *start)
{
  if (root == nil) root = new RedBlackNode();

  // Base case: There is nothing to copy, break from recursion
  if (start == nil) return nil;

  // Construct all child nodes through recursion, return root node
  return new RedBlackNode(start);
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
void RedBlackTree::transplant(RedBlackNode *oldNode, RedBlackNode *newNode)
{
  // case 1: If oldNode is the root node at this->root
  // + 2: if the oldNode is the left child of it's parent
  // + 3: case if the oldNode  is the right child of  it's parent
  if (oldNode->parent == nil) root = newNode;
  else if (oldNode == oldNode->parent->left) {
    // Update the parent of oldNode to reflect the transplant
    oldNode->parent->left = newNode;
  }
  else if (oldNode == oldNode->parent->right) {
    // Update the parent of oldNode to reflect the transplant
    oldNode->parent->right = newNode;
  }

  // If we did not replace oldNode with a nullptr, update newNode's parent
  newNode->parent = oldNode->parent;
}
