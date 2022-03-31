/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved               ##
## About: An example implementation of selection sort using a custom library ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################
*/

#include "lib-select.h"

#include <vector>

void SelectionSort(std::vector<int> &arr) {
  for (int leftIndex = 0; leftIndex < arr.size(); leftIndex++) {
    // Get the index for the minimum number in the unsorted set
    int min = leftIndex;
    for (int i = leftIndex; i < arr.size(); i++) {
      // Check if value at i is smaller than value at min index
      min = (arr[min] > arr[i]) ? i : min; // Update min value to i if true
    }

    // If the minimum index has changed from it's origin, swap the elements
    if (min != leftIndex) std::swap(arr[leftIndex], arr[min]);
  }
}
