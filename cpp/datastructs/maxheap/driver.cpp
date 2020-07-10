/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: A driver program to test a max heap implementation                 ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## driver.cpp
*/

#include "maxheap.h"
#include <iostream>

enum OPS {
  EXIT, INSERT, DELETE, PRINT, EMPTY, MIN, MAX
};

int main()
{
  std::cout << "Driver: \n";
  MaxHeap testList;
  bool exit = false;
  int choice = -1;
  int val;

  while (!exit)
  {
    std::cout << "##### Max Heap Menu #####\n\t0. Exit"
       "\n\t1. Insert\n\t2. Delete\n\t3. Print"
      << "\n\t4. Empty\n\t5. Min\n\t6. Max\n";
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

    case DELETE:
      testList.del();
      break;

    case PRINT:
      testList.print();
      break;

    case EMPTY:
      testList.makeEmpty();
      break;

    case MIN:
      std::cout << "Min value within our tree: " << testList.findMin() << endl;
      break;

    case MAX:
      std::cout << "Max value within our tree: " << testList.findMax() << endl;
      break;

    default:
      std::cout << "Invalid entry...\n";
      break;
    }
  }
}

