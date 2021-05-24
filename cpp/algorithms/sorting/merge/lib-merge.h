/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: An example implementation of merge sort using a custom library     ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################
*/

#ifndef LIB_MERGE_H
#define LIB_MERGE_H

#define ARRAY_LENGTH 10

#include <vector>

void MergeSort(std::vector<int> &array, size_t lhs, size_t rhs);

void Merge(std::vector<int> &array, size_t lhs, size_t mid, size_t rhs);

#endif // LIB_MERGE_H
