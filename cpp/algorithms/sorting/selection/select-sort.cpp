/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: An example implementation of selection sort using a custom library ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################
*/

#include "lib-select.h"

#include <iostream>

int main(const int argc, char const * argv[]) {
  // Create a random array based on ARRAY_LENGTH setting in lib-select.cpp
  int * numArray = RandomArray();

  std::cout << "Unsorted array: \n";
  PrintArray(numArray);

  // Sort the array and print the new contents
  SelectionSort(numArray);
  std::cout << "\nSorted array: \n";
  PrintArray(numArray);

  return 0;
}
