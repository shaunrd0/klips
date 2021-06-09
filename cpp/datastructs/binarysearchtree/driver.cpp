/*##############################################################################
## Author: Shaun Reed                                                         ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved                ##
## About: A driver program to test a binary search tree implementation        ##
##                                                                            ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0   ##
################################################################################
## driver.cpp
*/

#include "bst.h"

#include <iostream>

enum OPS {
  EXIT, INSERT, REMOVE, CONTAINS, INFIX, PREFIX, POSTFIX, EMPTY, MIN, MAX,
  COPY, EQUAL
};

int main()
{
  std::cout << "Driver: \n";
  BinarySearchTree testTree;
  bool exit = false;
  int choice = -1;
  int val;

  while (!exit)
  {
    std::cout << "##### Binary Search Tree Menu #####\n\t0. Exit"
                 "\n\t1. Insert\n\t2. Remove\n\t3. Contains\n\t4. In-order\n\t"
                 "5. Pre-order\n\t6. Post-order\n\t7. Empty\n\t8. Min\n\t9. Max"
                 "\n\t10. Copy BST\n\t11. Equal BST\n";
    std::cin >> choice;
    std::cin.clear();
    switch (choice) {
      case EXIT:
        exit = true;
        break;

      case INSERT:
        std::cout << "Enter a value to insert to our tree: ";
        std::cin >> val;
        std::cin.clear();
        testTree.insert(val);
        break;

      case REMOVE:
        std::cout << "Enter a value to remove from our tree: ";
        std::cin >> val;
        std::cin.clear();
        testTree.remove(val);
        break;

      case CONTAINS:
        std::cout << "Enter a value to search for within our tree: ";
        std::cin >> val;
        std::cin.clear();
        if (testTree.contains(val)) std::cout << val << " exists in our tree\n";
        else std::cout << val << " does not exist in our tree\n";
        break;

      case INFIX:
        testTree.printInOrder();
        break;

      case PREFIX:
        testTree.printPreOrder();
        break;

      case POSTFIX:
        testTree.printPostOrder();
        break;

      case EMPTY:
        testTree.makeEmpty();
        std::cout << "The BST is empty: "
                  << (testTree.isEmpty() ? "true" : "false") << std::endl;
        break;

      case MIN:
        std::cout << "Min value within our tree: " << testTree.findMin() << "\n";
        break;

      case MAX:
        std::cout << "Max value within our tree: " << testTree.findMax() << "\n";
        break;

      case COPY:
      {
        BinarySearchTree copiedTree(testTree);
        std::cout << "Inorder output from copied tree: ";
        copiedTree.printInOrder();
        std::cout << std::endl;
        // copiedTree calls destructor when leaving this scope
        break;
      }

      case EQUAL: {
        BinarySearchTree equalTree;
        equalTree = testTree;
        std::cout << "Inorder output from equal tree: ";
        equalTree.printInOrder();
        std::cout << std::endl;
        // equalTree calls destructor when leaving this scope
        break;
      }

      default:
        std::cout << "Invalid entry...\n";
        break;
    }
  }
}

