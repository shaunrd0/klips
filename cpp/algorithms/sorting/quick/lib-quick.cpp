/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: An example implementation of quick sort using a custom library     ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################
*/

#include "lib-quick.hpp"

#include <algorithm>
#include <vector>


void QuickSort(std::vector<int> &array, size_t begin, size_t end)
{
  // Base case breaks out of recursion once begin and end converge on each other
  if (begin >= end) return;

  // Search through array, finding the correct position for array[end]
  // + Returns the index *after* the new position for array[end]
  size_t pivot = Partition(array, begin, end);
  // array[end] is now at array[pivot]

  // Continue to sort the lhs partition of the set
  // + Using pivot-1 as the end index, we only consider the unsorted lhs portion
  QuickSort(array, begin, (pivot > 0) ? pivot - 1 : pivot);
  // In the top-level call to QuickSort, we don't reach this point until
  // + all values in the lhs portion of the array are < array[pivot]

  // At this point, pivot+1 now effectively represents the begin of unsorted rhs
  // + From pivot+1 to end, the array is currently unsorted

  // Continue to sort the rhs partition of the array
  // + Using pivot+1 as the begin index, we only consider the unsorted rhs portion
  QuickSort(array, pivot + 1, end);

  // The entire array, or the entire partition, is now sorted
  // + Return to previous QuickSort on call stack, or return to main
}

size_t Partition(std::vector<int> &array, size_t begin, size_t end)
{
  // Find the correct position for keyValue within the array partition
  // + Partition is within the range of array[begin ... end]
  int keyValue = array[end];

  // As we find values smaller than keyValue, track the last used index
  // + Return this value when done, so we know where the lhs partition ends
  ssize_t lhsIndex = begin - 1;
  // For each value within this partition, check for values < keyValue
  for (int j = begin; j <= end - 1; j++) {
    if (array[j] <= keyValue) {
      // Swap all values < keyValue into the lhs portion of array
      std::swap(array[++lhsIndex], array[j]);
    }
  }
  // Swap keyValue into lhsIndex+1, since we know all values before are smaller
  std::swap(array[++lhsIndex], array[end]);
  // Return the last used index for the lhs partition
  return lhsIndex;
}
