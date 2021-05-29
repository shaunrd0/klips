/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2021 Shaun Reed, all rights reserved               ##
## About: An example implementation of bucket sort using a custom library    ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################
*/

#include "lib-bucket.hpp"

#include <algorithm>
#include <list>
#include <vector>


void BucketSort(std::vector<float> &array)
{
  // For this example, we need an array of linked lists
  // + Each value of this array will be referred to as a bucket
  // + Each list stores the values that fall within the range of that bucket
  std::vector<std::list<float>> bucketArray(BUCKET_ARRAY_LENGTH);

  // Truncation to zero will always floor the result of division
  // + If the bucket contains negative values, convert them to their absolutes
  // + Run BucketSort on the abs values, then convert them back to negative
  // ++ For a mixed-bag of negative and positive, track which values you absolute
  // ++ Then only negate those values after BucketSort
  for (const auto & value : array) {
    bucketArray[value / static_cast<float>(bucketArray.size())].push_back(value);
  }

  // Track the last used index in the final sorted array; Starting at 0
  int currentIndex = 0;
  // Sort each bucket in the bucketArray
  for (std::list<float> &bucket : bucketArray) {
    bucket.sort();
    // After sorting each bucket, rewrite values in-order to final sorted array
    for (const auto &value : bucket) array[currentIndex++] = value;
  }

}
