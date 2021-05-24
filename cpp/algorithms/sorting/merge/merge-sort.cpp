/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: An example implementation of merge sort using a custom library     ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################
*/

#include "lib-merge.h"

#include <algorithm>
#include <iostream>
#include <vector>

int main(int const argc, char const * argv[]) {
  std::srand(time(nullptr));
  std::vector<int> array(ARRAY_LENGTH, 0);
  std::generate(array.begin(), array.end(), [](){ return rand() % 1000;});

  auto print = [](const std::vector<int> &array) {
    for (const auto &value : array) std::cout << value << ", ";
    std::cout << std::endl;
  };

  std::cout << "Unsorted array:\n";
  print(array);

  MergeSort(array, 0, array.size() - 1);

  std::cout << "Sorted array:\n";
  print(array);

  return 0;
}
