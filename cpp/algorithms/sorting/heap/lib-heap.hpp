/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: An example implementation of heap sort using a custom library      ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################
*/

#ifndef LIB_HEAP_HPP
#define LIB_HEAP_HPP

#include <vector>

#define ARRAY_LENGTH 10

size_t Parent(const size_t &index);
size_t Left(const size_t &index);
size_t Right(const size_t &index);

void MaxHeapify(std::vector<int> &array, size_t thisIndex, const int &heapSize);

void BuildMaxHeap(std::vector<int> &array);

void HeapSort(std::vector<int> &array);

#endif // LIB_HEAP_HPP
