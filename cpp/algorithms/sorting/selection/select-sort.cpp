/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved               ##
## About: An example implementation of selection sort using a custom library ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################
*/

#include "lib-select.h"

#include <algorithm>
#include <iostream>
#include <vector>

int main(const int argc, char const * argv[]) {
  // Create a random vector with size ARRAY_LENGTH set within lib-select.cpp
  std::srand(time(nullptr));
  std::vector<int> array(ARRAY_LENGTH, 0);
  std::generate(array.begin(), array.end(), [](){return rand() % 1000;});

  // Lambda for printing a vector
  auto print = [](std::vector<int> const &array)->void {
    for (const auto &i : array) std::cout << i << ", ";
    std::cout << std::endl;
  };

  // Print vector before we sort it
  std::cout << "Unsorted array: \n";
  print(array);

  // Sort the vector
  SelectionSort(array);

  // Print sorted vector
  std::cout << "\nSorted array: \n";
  print(array);

  return 0;
}
