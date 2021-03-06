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
#include <cstdint>
#include <vector>


void CountingSort(std::vector<int> &array)
{
  std::vector<int> sortedArray(ARRAY_LENGTH);
  // Find the maximum value within the array to sort
  int32_t maxValue = INT32_MIN;
  for (const auto &val : array) maxValue = (val > maxValue) ? val : maxValue;

  // Create an array with element for all *values* within the range of the set
  // + Not the size of the array to sort, but instead a element of
  // + tempArray[val] = 0; for each val within the array we want to sort
  // Add one to maxValue to make up for zero index; 0's are possible, too!
  std::vector<int> tempArray(maxValue + 1, 0);

  // Count the occurrences of each value within the array to sort
  // + Store the end result as tempArray[value] = count;
  for (const auto &val : array) tempArray[val] += 1;

  // Count the values less than or equal to each element of tempArray
  // + Since each element stores its own count, just add the count at index i-1
  for (size_t i = 1; i <= maxValue; i++) {
    tempArray[i] += tempArray[i - 1];
  }

  for (ssize_t arrayIndex = array.size() - 1; arrayIndex >= 0; arrayIndex--) {
    // Store as references; Changes reflect on actual values within each array
    const int &arrayValue = array[arrayIndex];
    int &valueCount = tempArray[arrayValue];
    sortedArray[valueCount - 1] = arrayValue;
    valueCount = valueCount - 1;
  }

  array = sortedArray;
}
