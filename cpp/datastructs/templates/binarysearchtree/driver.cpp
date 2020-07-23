/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: A driver program to test a binary search tree implementation       ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## driver.cpp
*/

#include "bst.h"
#include <iostream>

enum OPS {
  EXIT, INSERT, REMOVE, CONTAINS, INFIX, PREFIX, POSTFIX, EMPTY, MIN, MAX
};

int main()
{
  std::cout << "Driver: \n";
  BinarySearchTree testList;
  bool exit = false;
  int choice = -1;
  int val;

  while (!exit)
  {
    std::cout << "##### Binary Search Tree Menu #####\n\t0. Exit"
       "\n\t1. Insert\n\t2. Remove\n\t3. Contains\n\t4. Infix\n\t5. Prefix"
      << "\n\t6. Postfix\n\t7. Empty\n\t8. Min\n\t9. Max\n";
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
      testList.insert(val);
      break;

    case REMOVE:
      std::cout << "Enter a value to remove from our tree: ";
      std::cin >> val;
      std::cin.clear();
      testList.remove(val);
      break;

    case CONTAINS:
      std::cout << "Enter a value to search for within our tree: ";
      std::cin >> val;
      std::cin.clear();
      if (testList.contains(val))
        std::cout << val << " exists within our tree\n";
      else std::cout << val << " does not exist within our tree\n";
      break;

    case INFIX:
      testList.printInOrder();
      break;

    case PREFIX:
      testList.printPreOrder();
      break;

    case POSTFIX:
      testList.printPostOrder();
      break;

    case EMPTY:
      testList.makeEmpty();
      break;

    case MIN:
      std::cout << "Min value within our tree: " << testList.findMin();
      break;

    case MAX:
      std::cout << "Max value within our tree: " << testList.findMax();
      break;

    default:
      std::cout << "Invalid entry...\n";
      break;
    }
  }
}

