/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: An example implementation of insertion sort using a custom library ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################
*/

#include "lib-insertion.hpp"

#include <algorithm>
#include <vector>

void InsertionSort(std::vector<int> &array)
{
  // For each value, move left until we find sortedPosition for keyValue
  // + Starting with keyValue at array[1], to check sortedPosition at array[0]
  for (int keyIndex = 1; keyIndex <= array.size(); keyIndex++) {
    // Save the current key value
    // + We will look for the sorted position of this value
    const int keyValue = array[keyIndex];
    // First, check if the value at the previous index is > keyValue
    int sortedPosition = keyIndex - 1;
    // While array[sortedPosition] > keyValue
    while (sortedPosition >= 0 && array[sortedPosition] > keyValue) {
      // The value in the lower index is larger than the keyValue
      // + Move the value at sortedPosition to the right (ascending order)
      array[sortedPosition + 1] = array[sortedPosition];
      // Decrement sortedPosition so we can check the next value
      sortedPosition--;
    }
    // Insert the keyValue in its final sorted position
    // + Once array[sortedPosition] < keyValue, keyValue belongs one index right
    array[sortedPosition + 1] = keyValue;

  }
}

