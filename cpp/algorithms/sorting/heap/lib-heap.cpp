/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: An example implementation of heap sort using a custom library      ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################
*/

#include "lib-heap.hpp"

#include <algorithm>
#include <vector>

// Parent is unused, but included for completeness
size_t Parent(const size_t &index) { return index / 2;}
size_t Left(const size_t &index) { return 2 * index + 1;}
size_t Right(const size_t &index) { return (2 * index) + 2;}

void MaxHeapify(std::vector<int> &array, size_t thisIndex, int &heapSize)
{
  // Get an index for the left and right nodes attached to thisIndex
  size_t l = Left(thisIndex);
  size_t r = Right(thisIndex);
  // Assume thisIndex holds the largest value until proven otherwise
  size_t largest = thisIndex;
  // For both conditions, make sure l and r are within the heaps size
  // If either index l or r hold values that are larger than that of thisIndex
  // + Update the largest index
  if (l < heapSize && array[l] > array[thisIndex]) {
    largest = l;
  }
  if (r < heapSize && array[r] > array[largest]) {
    largest = r;
  }
  // If l or r contain any value larger than that of thisIndex
  if (largest != thisIndex) {
    // Swap their values
    std::swap(array[thisIndex], array[largest]);
    // Run MaxHeapify on the array, using the largest index as thisIndex
    MaxHeapify(array, largest, heapSize);
  }
}

void BuildMaxHeap(std::vector<int> &array, int &heapSize)
{
  // For each value within the heap, starting at last index moving to the first
  for (int i = (array.size() / 2); i >= 0; i--) {
    // Call MaxHeapify, sorting the value held at index i
    MaxHeapify(array, i, heapSize);
  }
}

void HeapSort(std::vector<int> &array)
{
  // Track the size of the heap
  // + Since HeapSort will remain on the call stack until all recursion returns
  // + Pass this value by reference to track size of heap as modifiable value
  int heapSize = array.size();
  // Create a maximum heap from the array using its size
  BuildMaxHeap(array, heapSize);
  // For each value within the max heap, starting from its final value
  for (int i = array.size() - 1; i > 0; i--) {
    // Swap the top value within the heap with the value at i
    std::swap(array[0], array[i]);
    //
    heapSize--;
    MaxHeapify(array, 0, heapSize);
  }

}

