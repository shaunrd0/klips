/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: An example implementation of selection sort using a custom library ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
###############################################################################
*/

#ifndef LIB_SELECT_H
#define LIB_SELECT_H

#define ARRAY_LENGTH 10

/** RandomArray
 * Returns an array automatically filled with random values
 *  Sizes array to match length setting ARRAY_LENGTH
 * @return A pointer to a static array
 */
int * RandomArray();

/** SelectionSort
 * Sorts an array of integers in ascending order
 * @param arr The array to sort
 */
void SelectionSort(int arr[]);

/** PrintArray
 * Prints an array based on the define ARRAY_LENGTH
 * @param arr The array to print
 */
void PrintArray(int arr[]);

#endif // LIB_SELECT_H
