/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: An example implementation of bubble sort using a custom library    ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################
*/

#include "lib-bubble.hpp"

#include <algorithm>
#include <vector>

void BubbleSort(std::vector<int> &array)
{
  // For each value within the set, starting at 0
  for (int sortedPivot = 0; sortedPivot < array.size(); sortedPivot++) {
    // Check every other remaining value in the set
    for (int j = array.size() - 1; j > sortedPivot; j--) {
      // Swap if the value at j is less than the value before it
      if (array[j] < array[j - 1]) {
        std::swap(array[j], array[j - 1]);
      }
    }
    // Increment sortedPivot, marking the lhs portion of the set as sorted
  }
}

