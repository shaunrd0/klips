#include <lib-datastruct.h>
#include <iostream>

enum OPS {
  EXIT, LISTS, STACKS, QUEUES
};

int main ()
{
  // std::cout << "Running driver program version " << DS_VERSION;

  bool exit = false;
  LinkedList<int> t;
  int choice;
  while (!exit) {
    std::cout << "Enter a choice below...\n\t0. Exit"
      << "\n\t1. LISTS\n\t2. STACKS\n\t3. QUEUES\n";
    std::cin >> choice;
    std::cin.clear();

    switch (choice) {
    case EXIT: // 0
      exit = true;
      break;
    
    case LISTS: // 1
      break;
    
    case STACKS: // 2
      break;
    
    case QUEUES: // 3
      break;

    default:
      std::cout << "Invalid option selected\n";
      break;
    }
  }

  return 0;
}
