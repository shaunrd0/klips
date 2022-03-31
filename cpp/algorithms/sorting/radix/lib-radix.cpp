/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved               ##
## About: An example implementation of radix sort using a custom library     ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################
*/

#include "lib-radix.hpp"
#include "lib-counting.hpp"

#include <algorithm>
#include <vector>


void RadixSort(std::vector<int> &array)
{
  int maxValue = *std::max_element(array.begin(), array.end());
  // Get the total number of digits in the maximum value within the set
  // + 100 has 3 digits; 10 has 2 digits; etc..
  int digits = 0;
  for (int tempMax = maxValue; tempMax > 0; tempMax /= 10) digits++;

  // For each placeValue of the maximum value within the set
  for (int placeValue = 1; maxValue / placeValue > 0; placeValue *= 10) {
    // Perform counting sort on all values, only considering the placeValue digit
    // Result of sorting the first placeValue:
    // + 12, 10, 15, 5, 3, 101, 109, 115 -> 10, 101, 12, 3, 115, 15, 5, 109
    // Result of sorting the second placeValue:
    // + 10, 101, 12, 3, 115, 15, 5, 109 -> 3, 5, 101, 109, 10, 12, 115, 15
    // Result of sorting the third placeValue:
    // + 3, 5, 101, 109, 10, 12, 115, 15 -> 3, 5, 10, 12, 15, 101, 109, 115
    CountingSort(array, placeValue);
  }

}
