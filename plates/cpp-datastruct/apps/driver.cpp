#include <lib-datastruct.h>
#include <iostream>

// StackArray menu
void Stack();

void List();

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
      List();
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

// LinkedList menu
void List()
{
  enum LIST_OPS {
    EXIT, APPEND, PUSH, DEQUEUE, POP, DISPLAY
  };
  bool exit = false;
  int choice;
  char val;
  LinkedList list;

  while(!exit) {
    std::cout << "\n##### LinkedList Menu #####\n"
       << "Enter a choice below...\n\t0. Exit"
       << "\n\t1. Append\n\t2. Push\n\t3. Dequeue\n\t4. Pop"
       << "\n\t5. Display\n\t6. Find\n\t7. Remove\n";
    std::cin >> choice;
    std::cin.clear();
    switch(choice) {
      case EXIT: // 0
        exit = true;
        break;

      case APPEND: // 1
        std::cout << "Enter a character to append to our list: ";
        std::cin >> val;
        std::cin.clear();
        list.Append(val);
        break;

      case PUSH: // 2
        std::cout << "Enter a character to push to our list: ";
        std::cin >> val;
        std::cin.clear();
        list.Push(val);
        break;
      
      case DEQUEUE: // 3
        std::cout << "Enter a value to remove from the list: ";
        std::cin >> val;
        std::cin.clear();
        list.Remove(val);
        break;

      case POP: // 4
        // list.Pop();
        list.Append('a');
        Node *tem = list.Find('a');
        list.Remove('a');
        if (tem != NULL) {
          std::cout << "Found [" << tem->data << "] within the list\n";
        }
        delete tem;
        break;

      case DISPLAY: // 5
        list.Display();
        break;

      default:
        std::cout << "Invalid option selected\n";
        break;
    }
  }

  return;
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
