/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: An example implementation of radix sort using a custom library     ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################
*/

#include "lib-counting.hpp"
#include "lib-radix.hpp"

#include <algorithm>
#include <vector>
#include <random>
#include <iostream>

// More values increase chance that the set provides colliding placeValue digits
#define ARRAY_LENGTH 20


int main(const int argc, const char * argv[])
{
  srand(time(nullptr));
  std::vector<int> array(ARRAY_LENGTH);
  // For this example, we limit the maximum value to 150
  // + This helps to provide values with 1, 2, or 3 total placeValue digits
  // + Possible to get 0-9, 10-99, and 100-149
  std::generate(array.begin(), array.end(), [](){ return rand() % 150;});

  auto print = [](std::vector<int> array) {
    for (const auto &i : array) {
      std::cout << i << ", ";
    }
    std::cout << std::endl;
  };

  std::cout << "Unsorted array: \n";
  print(array);

  RadixSort(array);

  std::cout << "Sorted array: \n";
  print(array);
}
