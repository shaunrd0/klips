/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2019 Shaun Reed, all rights reserved               ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## lib-launcher.cpp
*/

#include <lib-launcher.hpp>

/* This function allows for selection of the next problem to run.
 *
 * @param pSelect - The index to use within our enumeration.
 *                  Allows for easy integer to problem selection.
 */
void RunProblem(Problem pSelect) { 

  switch (pSelect) {
    
    case Problem::One:  
      std::printf("\nYou are on problem 1!\n"
      "Press enter to continue.");
      std::cin.ignore();
      break;
    
    case Problem::Two:
      std::printf("\nYou are on problem 2!\n"
      "Press enter to continue.");
      std::cin.ignore();
      break;
    
    case Problem::Three:
      std::printf("\nYou are on problem 3!\n"
      "Press enter to continue.");
      std::cin.ignore();
      break;
    
    case Problem::Four:
      std::printf("\nYou are on problem 4!\n"
      "Press enter to continue.");
      std::cin.ignore();
      break;
    
    case Problem::Five:
      std::printf("\nYou are on problem 5!\n"
      "Press enter to continue.");
      std::cin.get();
      break;

    case Problem::Exit:
      std::printf("\nYou are on problem 0! This is a safe exit.\n"
      "Press enter to continue.");
      std::cin.ignore();
      break;

    case Problem::Error:
      std::printf("\nYou are on problem -1! This is considered and error.\n"
      "Press enter to exit.");
      std::cin.ignore();
      break;

    case Problem::Launch:
      // Do nothing, break and let main() restart the launcher
      std::printf("\nRestarting the launcher...\n"
      "Press enter to continue.");
      std::cin.ignore();
      break;

    default:
      std::printf("\nYou have entered an invalid value."
      "\nPress Enter to try again.");
      //ProblemList();
      break;

  }

  return;
}

