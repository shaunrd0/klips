/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved               ##
## About: An example implementation of selection sort using a custom library ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################
*/

#ifndef LIB_SELECT_H
#define LIB_SELECT_H

#define ARRAY_LENGTH 10

#include <vector>

/** SelectionSort
 * Sorts an array of integers in ascending order
 * @param arr The array to sort
 */
void SelectionSort(std::vector<int> &arr);

#endif // LIB_SELECT_H
