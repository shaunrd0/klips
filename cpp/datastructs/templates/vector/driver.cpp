/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: A driver program to test a vector implementation                   ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## driver.cpp
*/

#include "vector.h"
#include <iostream>

enum OPS {
  EXIT, PUSH, POP, TOP, PRINT, EMPTY, CONSTRUCT, COPY,  ASSIGN, DESTRUCT
};

int main()
{
  std::cout << "Driver: \n";
  Vector<std::string> testlist;
  bool exit = false;
  int choice = -1;
  <typename T> T val;

  while (!exit)
  {
    std::cout << "##### vectors menu #####\n\t0. exit"
      << "\n\t1. push\n\t2. pop\n\t3. peek\n\t4. print\n\t5. empty"
      << "\n\t6. construct\n\t7. copy\n\t8. assign\n\t9. destruct\n\t";
    std::cin >> choice;
    std::cin.clear();
    switch (choice) {
    case EXIT:
      exit = true;
      break;

    case PUSH:
      std::cout << "enter a value to push to our vector: ";
      std::cin >> val;
      std::cin.clear();
      testlist.push(val);
      break;

    case POP:
      testList.pop();
      break;

    case TOP:
      testList.peek();
      break;

    case PRINT:
      testList.print();
      break;

    case EMPTY:
      testList.makeEmpty();
      break;

    // If this test is successful, we build a default empty Vector object
    // Will 'have nothing to print' because a default Vector contains no values
    case CONSTRUCT:
    {
      Vector<std::string> constrTest;
      std::cout << "##### Constructor Test #####\n";
      constrTest.print();
      std::cout << "Deleting local constrTest Vector...\n";
      break;
    }

    // If this is successful, we build a new Vector based on the existing Vector
    // The new Vector output here should be identical to this session's Vector
    case COPY:
    {
      Vector<std::string> copyTest(testList);
      std::cout << "##### Copy Constructor Test #####\n";
      copyTest.print();
      std::cout << "Deleting local copyTest Vector...\n";
      break;
    }

    // Test assignment operator, setting new Vector object equal to the existing
    case ASSIGN:
    {
      Vector<std::string> assignTest;
      assignTest = testList;
      std::cout << "##### Assignment Test #####\n";
      assignTest.print();
      std::cout << "Deleting local assignTest Vector...\n";
      break;
    }

    case DESTRUCT:
    {
      Vector<std::string> destrTest(testList);
      std::cout << "Current destrTest Vector contents...\n";
      destrTest.print();
      std::cout << "Deleting local destrTest Vector...\n";
      destrTest.~Vector(); // Implicitly called at the end of this scope {}
      destrTest.print();
      break;
    }

    default:
      std::cout << "Invalid entry...\n";
      break;
    }
  }
}

