/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: An example implementation of counting sort using a custom library  ##
##        + In support of a radix sort implementation                        ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################
*/

#include "lib-counting.hpp"

#include <algorithm>
#include <vector>
#include <cstdint>


void CountingSort(std::vector<int> &array, int placeValue)
{
  std::vector<int> sortedArray(array.size(), 0);

  // Find the maximum value within the array to sort
  int32_t maxValue = INT32_MIN;
  for (const auto &val : array) maxValue = (val > maxValue) ? val : maxValue;

  // Create an array with element for all *placeValues* within range of the set
  // + Not the size of the array to sort, but instead a element of
  // + tempArray[digit] = 0; Considering only the digit at placeValue of array[n]
  // Using this vector, we have a place to count all possible digits at placeValue
  std::vector<int> tempArray(10, 0);

  // Count the occurrences of each digit at this placeValue within the array
  // + Store the end result as tempArray[digit] = count;
  // + Where digit is found at the decimal placeValue of each value within array
  for (const auto &val : array) {
    // Get the digit at the decimal placeValue of arrayValue
    auto index = static_cast<size_t>((val / placeValue) % tempArray.size());
    // Running total of each value with the same digit at decimal placeValue
    tempArray[index] = tempArray[index] + 1;
  }

  // Count the values less than or equal to each element of tempArray
  // + Since each element stores its own count, just add the count at index i-1
  for (int i = 1; i < tempArray.size(); i++) {
    tempArray[i] = tempArray[i] + tempArray[i - 1];
  }

  for (ssize_t arrayIndex = array.size() - 1; arrayIndex >= 0; arrayIndex--) {
    // Get the value to consider from the unsorted array
    const int &arrayValue = array[arrayIndex];

    // Get the digit at the decimal placeValue of arrayValue
    // + Use this index to update count of values as we use them
    const auto tempIndex =
        static_cast<size_t>((arrayValue / placeValue) % tempArray.size());

    // Store valueCount as a reference so we can update it
    int &valueCount = tempArray[tempIndex];
    // Offset valueCount by 1 to allow for zero index of sortedArray
    sortedArray[valueCount - 1] = arrayValue;
    valueCount = valueCount - 1;
  }

  array = sortedArray;
}
