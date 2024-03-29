/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved               ##
## About: An example implementation of quick sort using a custom library     ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################
*/

#include "lib-quick.hpp"

#include <algorithm>
#include <vector>
#include <random>
#include <iostream>

int main(const int argc, const char * argv[])
{
  srand(time(nullptr));
  std::vector<int> array(ARRAY_LENGTH);
  std::generate(array.begin(), array.end(), [](){ return rand() % 1000;});

  auto print = [](std::vector<int> array) {
    for (const auto &i : array) {
      std::cout << i << ", ";
    }
    std::cout << std::endl;
  };

  std::cout << "Unsorted array: \n";
  print(array);

  QuickSort(array, 0, array.size() - 1);

  std::cout << "Sorted array: \n";
  print(array);
}
