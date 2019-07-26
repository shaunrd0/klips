/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2019 Shaun Reed, all rights reserved               ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## lib-launcher.hpp
*/

#include <iostream>
#include <limits>

// Define our constants
// These are used for ranges within our control loops
const int QTY = 5;
const int EXIT = 0;
const int ERROR = -1;
const int LAUNCH = 99;

/* An enumeration for use with RunProblem() when selecting which problem to run
 * This is meant to be expanded as needed.
 * Be sure to add a corresponding case within RunProblem()
 *
 * @Launcher (LAUNCH 99) the value used for the launcher as a problem number
 * @Exit (EXIT 0) is the normal exit index
 * @Error (ERROR -1) is considered an error
 */
enum class Problem 
{ Launch = 99, Error = -1, Exit, One, Two, Three, Four, Five };

/* This function allows for selection of the next problem to run.
 *
 * @param pSelect - The index to use within our enumeration.
 *                  Allows for easy integer to problem selection.
 */
void RunProblem(Problem pSelect);

