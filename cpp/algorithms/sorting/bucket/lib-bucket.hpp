/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2022 Shaun Reed, all rights reserved               ##
## About: An example implementation of bucket sort using a custom library    ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################
*/

#ifndef LIB_BUCKET_HPP
#define LIB_BUCKET_HPP

#include <list>
#include <vector>

// For this example double the size of the array to increase chance of collision
#define ARRAY_LENGTH 20
// Define how many buckets we want to use
#define BUCKET_ARRAY_LENGTH 10

void BucketSort(std::vector<float> &array);

#endif // LIB_BUCKET_HPP
