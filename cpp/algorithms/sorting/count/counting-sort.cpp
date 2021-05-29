/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: An example implementation of counting sort using a custom library  ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################
*/

#include "lib-counting.hpp"

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>


int main(const int argc, const char * argv[])
{
  srand(time(nullptr));
  std::vector<int> array(ARRAY_LENGTH);
  // For this example, we limit the maximum value to 10
  // + This helps to provide duplicates so we have > 1 count of some values
  std::generate(array.begin(), array.end(), [](){ return rand() % 10;});

  auto print = [](std::vector<int> array) {
    for (const auto &i : array) {
      std::cout << i << ", ";
    }
    std::cout << std::endl;
  };

  std::cout << "Unsorted array: \n";
  print(array);

  CountingSort(array);

  std::cout << "Sorted array: \n";
  print(array);
}
