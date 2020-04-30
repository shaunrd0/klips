/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: A driver program to test a circular singly linked list             ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## driver.cpp
*/

#include "circlesinglelist.h"
#include <iostream>

enum OPS {
  EXIT, INSERT, INSERTAT, EMPTY, PEEK, PRINT, FIND, REMOVE, REPLACE
};

int main()
{
  std::cout << "Driver: \n";

  CircleSingleList testList;
  bool exit = false;
  int choice = -1;
  int val, key;

  while (!exit)
  {
    std::cout << "##### Circular Singly Linked List Menu #####\n\t0. Exit"
      << "\n\t1. Insert\n\t2. Insert at\n\t3. Empty list\n\t4. Peek top of list"
      << "\n\t5. Print list\n\t6. Find\n\t7. Remove\n\t8. Replace\n";
    std::cin >> choice;
    std::cin.clear();
    switch (choice) {
    case EXIT:
      exit = true;
      break;

    case INSERT:
      std::cout << "Enter a value to add to our list: ";
      std::cin >> val;
      std::cin.clear();
      testList.insert(val);
      break;

    case INSERTAT:
      std::cout << "Enter a new value to add to our list: ";
      std::cin >> val;
      std::cin.clear();
      std::cout << "Enter an existing value to insert at within our list: ";
      std::cin >> key;
      std::cin.clear();
      if (testList.insert(val, key)) {
        std::cout << "List after inserting ["
          << val << "] at [" << key << "]: \n";
        testList.print();
      }
      break;

    case EMPTY:
      testList.makeEmpty();
      break;

    case PEEK:
      testList.peek();
      break;

    case PRINT:
      testList.print();
      break;

    case FIND:
      std::cout << "Enter an existing value to search for within our list: ";
      std::cin >> val;
      std::cin.clear();
      testList.find(val);
      break;

    case REMOVE:
      std::cout << "Enter an existing value to remove from our list: ";
      std::cin >> val;
      std::cin.clear();
      testList.remove(val);
      break;

    case REPLACE:
      std::cout << "Enter a new value to add to our list: ";
      std::cin >> val;
      std::cin.clear();
      std::cout << "Enter an existing value to replace within our list: ";
      std::cin >> key;
      std::cin.clear();
      if (testList.replace(val, key)) {
        std::cout << "List after replacing ["
          << key << "] by [" << val << "]: \n";
        testList.print();
      }
      break;

    default:
      std::cout << "Invalid entry...\n";
      break;
    }
  }
}

