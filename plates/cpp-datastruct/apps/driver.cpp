#include <lib-datastruct.h>
#include <iostream>

// StackArray menu
void Stack();

// Main menu
int main ()
{
  // std::cout << "Running driver program version " << DS_VERSION;
  enum OPS {
    EXIT, LISTS, STACKS, QUEUES
  };

  bool exit = false;
  int choice;
  while (!exit) {
    std::cout << "\n##### Main Menu #####\n"
      << "Enter a choice below...\n\t0. Exit"
      << "\n\t1. Lists\n\t2. Stacks\n\t3. Queues\n";
    std::cin >> choice;
    std::cin.clear();

    switch (choice) {
    case EXIT: // 0
      exit = true;
      break;
    
    case LISTS: // 1
      break;
    
    case STACKS: // 2
      Stack();
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

// StackArray menu
void Stack()
{
  enum STACK_OPS {
    EXIT, PUSH, POP, TOP, DISPLAY
  };

  StackArray stack;
  bool exit = false;
  int choice;
  while (!exit) {
    std::cout << "\n##### StackArray Menu #####\n"
      << "Enter a choice below...\n\t0. Exit"
      << "\n\t1. Push\n\t2. Pop\n\t3. Top\n\t4. Display\n";
    std::cin >> choice;
    std::cin.clear();

    switch (choice) {
    case EXIT: // 0
      exit = true;
      break;

    case PUSH: // 1
      char val;
      std::cout << "Enter a character to push to our stack: ";
      std::cin >> val;
      std::cin.clear();
      stack.Push(val);
      break;
    

    case POP: // 2
      std::cout << "[" << stack.Pop() << "] has been removed from our stack\n";
      break;
    

    case TOP: // 3
      std::cout << "[" << stack.Top() << "] is at the top of our stack\n";
      break;
    

    case DISPLAY: // 4
      stack.Display();
      break;
    
    default:
      std::cout << "Invalid option selected\n";
      break;
    }
  }
  
}
