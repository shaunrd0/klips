/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: A driver program to test a queue implementation using linked lists ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## driver.cpp
*/

#include "queuelist.h"
#include <iostream>

enum OPS {
};

int main()
{
  std::cout << "Driver: \n";

  QueueList<TYPE> testList;
  bool exit = false;
  int choice = -1;
  TYPE val;

  while (!exit)
  {
    std::cout << "##### Queues Using Linked Lists Menu #####\n\t0. Exit"
      << "\n\t1. Enqueue\n\t2. Dequeue\n\t3. Next\n\t4. Print"
      << "\n\t5. Empty\n\t";
    std::cin >> choice;
    std::cin.clear();
    switch (choice) {
    case EXIT:
      exit = true;
      break;

    case ENQUEUE:
      std::cout << "Enter a value to add to the end of our queue: ";
      std::cin >> val;
      std::cin.clear();
      testList.enqueue(val);
      break;

    case DEQUEUE:
      testList.dequeue();
      break;

    case NEXT:
      testList.next();
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
