/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved               ##
## About: An example implementation of bucket sort using a custom library    ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################
*/

#include "lib-bucket.hpp"

#include <algorithm>
#include <iostream>
#include <random>
#include <vector>


int main(const int argc, const char * argv[])
{
  srand(time(nullptr));
  std::vector<float> array(ARRAY_LENGTH);
  std::generate(array.begin(), array.end(),
                [](){ return static_cast<float>(rand() % 1000) * 0.1f;}
                );

  auto print = [](std::vector<float> array) {
    for (const auto &i : array) {
      std::cout << i << ", ";
    }
    std::cout << std::endl;
  };

  std::cout << "Unsorted array: \n";
  print(array);

  BucketSort(array);

  std::cout << "Sorted array: \n";
  print(array);
}
