/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved               ##
## About: An example implementation of merge sort using a custom library     ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################
*/

#include "lib-merge.h"

#include <algorithm>
#include <iostream>
#include <vector>

void MergeSort(std::vector<int> &array, size_t lhs, size_t rhs)
{
  // Base case to break recursion; When we are left with < 2 values
  // + Since we cannot split a single value into two arrays without duplicating
  if (lhs >= rhs) {
    return; // Insert breakpoint here and walk up call stack for more info
  }
  // We will never have a negative result from (l + r)
  // + Truncation to zero will floor division by 2
  size_t mid = (lhs + rhs) / 2;

  // Recurse into lhsArray[lhs ... mid]; Repeat until we hit base case
  // + Next call will recurse into a smaller lhsArray
  MergeSort(array, lhs, mid);
  // Recurse into rhsArray[mid + 1 ... rhs]; Repeat until we hit base case
  MergeSort(array, mid + 1, rhs);
  // Merge is called after we reach the first base case
  Merge(array, lhs, mid, rhs);
}

void Merge(std::vector<int> &array, size_t lhs, size_t mid, size_t rhs)
{
  size_t lhsLength = mid - lhs + 1;
  size_t rhsLength = rhs - mid;

  // Create lhsArray, rhsArray with one additional index for a sentinel value
  std::vector<int> lhsArray(lhsLength + 1);
  std::vector<int> rhsArray(rhsLength + 1);

  // Initialize lhsArray from array[0] to array[mid]
  for (size_t i = 0; i < lhsLength; i++) lhsArray[i] = array[lhs + i];
  // Initialize rhsArray from array[mid + 1] to array[rhs]
  for (size_t j = 0; j < rhsLength; j++) rhsArray[j] = array[mid + 1 + j];

  // Set the sentinel values for final index of lhsArray, rhsArray
  // + When we hit these values during a merge, they are always greater than
  // ++ Set to the maximum possible value; There can never be anything larger
  lhsArray[lhsLength] = INT32_MAX;
  rhsArray[rhsLength] = INT32_MAX;

  // Start at the beginning of both subarrays
  // + i
  size_t lhsIndex = 0;
  size_t rhsIndex = lhsIndex; // Starting at 0, same as lhsIndex

  // For each value across both subarrays; From lhs to rhs
  // + Check all values across lhsArray[lhs... mid] and rhsArray[mid + 1.. rhs]
  // ++ When mergeIndex hits the value of rhs, we are done scanning both arrays
  for (size_t mergeIndex = lhs; mergeIndex <= rhs; mergeIndex++) {
    // If either value is a sentinel, the non-sentinel value is always less than
    if (lhsArray[lhsIndex] <= rhsArray[rhsIndex]) {
      array[mergeIndex] = lhsArray[lhsIndex++];
    }
    else { // rhsArray[rhsIndex] < lhsArray[lhsIndex]
      array[mergeIndex] = rhsArray[rhsIndex++];
    }
  }

}
