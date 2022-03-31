/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved               ##
## About: Driver program to test BST algorithms from MIT intro to algorithms ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################
*/

#include "bst.h"

#include <iostream>
#include <vector>


int main (const int argc, const char * argv[])
{
  BinarySearchTree testTree;
  std::vector<int> inputValues {2, 6, 9, 1, 5, 8, 10};
  // Alternative input values
//  std::vector<int> inputValues {10, 12, 6, 4, 20, 8, 7, 15, 13};

  std::cout << "Building binary search tree with input: ";
  for (const auto &value : inputValues) std::cout << value << ", ";
  std::cout << std::endl;

  for (const auto &value : inputValues) testTree.insert(value);

  std::cout << "\nInorder traversal: \n";
  testTree.printInOrder();
  std::cout << std::endl;

  std::cout << "Postorder traversal: \n";
  testTree.printPostOrder();
  std::cout << std::endl;

  std::cout << "Preorder traversal: \n";
  testTree.printPreOrder();
  std::cout << std::endl;

  std::cout << "\nMinimum value: " << testTree.findMin()->element << std::endl;
  std::cout << "Maximum value: " << testTree.findMax()->element << std::endl;

  // Test removing a node, printing the result in-order
  std::cout << "\nRemoving root value...\n";
  testTree.remove(testTree.getRoot()->element);
  // Can use inline function to remove a value directly for testing -
//  testTree.remove(6);

  std::cout << "Inorder traversal: \n";
  testTree.printInOrder();
  std::cout << std::endl;

  // Test copy constructor
  std::cout << "\nCloning testTree to testTree2...\n";
  BinarySearchTree testTree2 = testTree;
  std::cout << "Inorder traversal of the cloned testTree2: \n";
  testTree2.printInOrder();
  std::cout << std::endl;

  // Test assignment operator
  std::cout << "\nCloning testTree to testTree3...\n";
  BinarySearchTree testTree3;
  testTree3 = testTree;
  std::cout << "Inorder traversal of the cloned testTree3 tree: \n";
  testTree3.printInOrder();
  std::cout << std::endl;

  // Test emptying the BST
  std::cout << "\nEmptying testTree...\n";
  testTree.makeEmpty();
  std::cout << "testTree isEmpty: " << (testTree.isEmpty() ? "true" : "false");
  std::cout << "\ntestTree2 isEmpty: " << (testTree2.isEmpty() ? "true" : "false");
  std::cout << "\ntestTree3 isEmpty: " << (testTree3.isEmpty() ? "true" : "false");

  // Testing integrity of deep copy (cloned) data after deletion of testTree
  std::cout << "\n\nTesting integrity of previously cloned testTree2...\n";
  std::cout << "Inorder traversal of the cloned testTree2: \n";
  testTree2.printInOrder();
  std::cout << std::endl;
  std::cout << "Inorder traversal of the cloned testTree3: \n";
  testTree3.printInOrder();
  std::cout << std::endl;

  std::cout << "\nChecking if tree contains value of 6: ";
  std::cout << (testTree2.contains(6) ? "true" : "false") << std::endl;
  std::cout << "Checking if tree contains value of 600: ";
  std::cout << (testTree2.contains(600) ? "true" : "false") << std::endl;

  std::cout << "\nSuccessor of node with value 6: "
            << testTree2.successor(testTree2.search(6))->element;
  std::cout << "\nPredecessor of node with value 6: "
            << testTree2.predecessor(testTree2.search(6))->element;
  std::cout << std::endl;

}
