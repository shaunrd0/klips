/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: An example implementation of counting sort using a custom library  ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################
*/

#ifndef LIB_COUNT_HPP
#define LIB_COUNT_HPP

#include <vector>

// For this example double the size of the array so we have more values to count
#define ARRAY_LENGTH 20


void CountingSort(std::vector<int> &array);

#endif // LIB_COUNT_HPP
