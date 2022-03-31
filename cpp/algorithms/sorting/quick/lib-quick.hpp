/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved               ##
## About: An example implementation of quick sort using a custom library     ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################
*/

#ifndef LIB_QUICK_HPP
#define LIB_QUICK_HPP

#include <vector>

#define ARRAY_LENGTH 10

void QuickSort(std::vector<int> &array, size_t begin, size_t end);

size_t Partition(std::vector<int> &array, size_t begin, size_t end);

#endif // LIB_QUICK_HPP
