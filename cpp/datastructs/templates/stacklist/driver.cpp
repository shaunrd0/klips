/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: A driver program to test a stack implementation using linked lists ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## driver.cpp
*/

#include "stacklist.h"
#include <iostream>

enum OPS {
  EXIT, PUSH, POP, TOP, PRINT, EMPTY
};

int main()
{
  std::cout << "Driver: \n";

  StackList testList;
  bool exit = false;
  int choice = -1;
  int val;

  while (!exit)
  {
    std::cout << "##### Stacks Using Linked Lists Menu #####\n\t0. Exit"
      << "\n\t1. Push\n\t2. Pop\n\t3. Top\n\t4. Print"
      << "\n\t5. Empty\n\t";
    std::cin >> choice;
    std::cin.clear();
    switch (choice) {
    case EXIT:
      exit = true;
      break;

    case PUSH:
      std::cout << "Enter a value to push to our stack: ";
      std::cin >> val;
      std::cin.clear();
      testList.push(val);
      break;

    case POP:
      testList.pop();
      break;

    case TOP:
      testList.top();
      break;

    case PRINT:
      testList.print();
      break;

    case EMPTY:
      testList.makeEmpty();
      break;

    default:
      std::cout << "Invalid entry...\n";
      break;
    }
  }
}
