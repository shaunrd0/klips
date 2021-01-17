/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: An example implementation of selection sort using a custom library ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################
*/

#include "lib-select.h"

#include <iostream>

static int FindMinIndex(int const arr[], int start) {
  // Assume we are at the minimum index until another is found
  int min = start;
  for (int i = start; i < 10; i++) {
    if (arr[min] > arr[i]) min = i;
  }
  return min;
}

int * RandomArray() {
  static int newArray[ARRAY_LENGTH];
  srand(time(NULL));

  int randMax = 1000;
  for (int i = 0; i < ARRAY_LENGTH; i++) {
    newArray[i] = random() % randMax;
  }
  return newArray;
}

void SelectionSort(int arr[]) {
  for (int leftIndex = 0; leftIndex < ARRAY_LENGTH; leftIndex++) {
    // Check for a different minimum in the unsorted portion of the array
    int min = FindMinIndex(arr, leftIndex);

    // If the minimum index has changed from it's origin, swap the elements
    if (min != leftIndex) std::swap(arr[leftIndex], arr[min]);
  }
}

void PrintArray(int arr[]) {
  for (int i = 0; i < ARRAY_LENGTH; i++) {
    std::cout << arr[i] << std::endl;
  }
  std::cout << std::endl;
}
