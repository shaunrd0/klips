/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2019 Shaun Reed, all rights reserved               ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## launcher.cpp
*/

#include <iostream>
#include <lib-launcher.hpp>

int main () {
  // Because the launcher is this executable.. (main() will become our exe)
  // Initialize the user choice to launcher problem at runtime
  int pChoice = LAUNCH;

  // Cast the integer pChoice into an assignment for our Problem enum
  // No failsafes needed here since we know pChoice = LAUNCH
  Problem pSelect = static_cast<Problem>(pChoice);

  do
  {
    printf("\nWelcome to the cpp launcher!\n"
           "Input the problem number to run the example.\n");

    //ProblemList(); List and explain problem selection
    //ProblemSelect(); Select problem, handle errors, return result to &pSelect
    
    std::cin >> pChoice;
    
    if(pChoice == LAUNCH)
    { // Ensure that pSelect = LAUNCH and restart
    pSelect = static_cast<Problem>(pChoice);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    RunProblem(pSelect);
    continue;
    }
    else if ( pChoice > QTY )
    { // If we have entered a value too large, restart
    std::printf("\nThe value you entered is too large."
    "\nPlease enter a value below %d\n", QTY);
    pSelect = Problem::Launch; // Set our launcher to restart and continue
    continue;
    }

    if (!std::cin ) 
    { // Check for cin error state
    std::cin.clear();
    std::cin.ignore();
    pChoice = ERROR;
    }
    // One last input check for other error values
    if (pChoice < EXIT) pChoice = ERROR;

    // Cast the integer pChoice into an assignment for our Problem enum    
    pSelect = static_cast<Problem>(pChoice);

    /*
    * We should expect a clear input buffer at this point
    * Clear cin up to next endline to prepare for the next input
    * Depends on include <limits> for numeric_limits<streamsize>
    */
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // Run the problem, print exit, or print error.
    RunProblem(pSelect); 

  // Run loop until invalid or exit input recieved
  } while (pChoice > EXIT || pChoice == LAUNCH); 
  // Exit the launcher if the selection is in range
  // Exit if pSelect is set to ERROR state value

  return 0;
}

