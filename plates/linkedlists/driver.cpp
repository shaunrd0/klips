#include "linkedlist.h"
#include <iostream>

enum OPS {
  EXIT, INSERT, INSERTAT, EMPTY, PEEK, PRINT, FIND
};

int main()
{
  std::cout << "Driver: \n";

  SingleList testList;
  bool exit = false;
  int choice = -1;
  int val, ins;
  while (!exit)
  {
    std::cout << "##### Singly Linked List Menu #####\n\t0. Exit"
      << "\n\t1. Insert\n\t2. Insert at\n\t3. Empty list\n\t4. Peek top of list"
      << "\n\t5. Print list\n\t6. Find\n";
    std::cin >> choice;
    std::cin.clear();
    switch (choice)
    {
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
      std::cout << "Enter a value to insert at within our list: ";
      std::cin >> ins;
      std::cin.clear();
      std::cout << "Enter a value to add to our list: ";
      std::cin >> val;
      std::cin.clear();
      if (!testList.insert(val, ins)) {
        std::cout << "No changes made, [" << ins << "] was not found in our list\n";
      }
      else {
        std::cout << "List after inserting [" 
          << val << "] at [" << ins << "]: \n";
        testList.print();
      }
      break;

    case EMPTY:
      testList.makeEmpty();
      break;

    case PEEK:
      std::cout << "[" << testList.peek() << "] is at the top of our list\n";
      break;

    case PRINT:
      testList.print();
      break;

    case FIND:
      std::cout << "Enter a value to search for within our list: ";
      std::cin >> val;
      std::cin.clear();
      testList.find(val);
      break;

    default:
      std::cout << "Invalid entry...\n";
      break;
    }
  }
}

