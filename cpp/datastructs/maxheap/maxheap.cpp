/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: An example of a max heap implementation                            ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## maxheap.cpp
*/

#include "maxheap.h"


/********************************************************************************
* Constructors, Destructors, Operators
*********************************************************************************/

/** default constructor
 *  Constructs a heap with the given default values
 */
MaxHeap::MaxHeap() : size(0), index(0), heap(NULL) {}

/** copy constructor
 *  Creates a new heap which is identical to an existing MaxHeap object
 *
 * @param rhs
 */
MaxHeap::MaxHeap(const MaxHeap& rhs) : size(rhs.size), index(rhs.index)
{
  heap = new int[size];
  for (int i = 0; i < index; i++) {
    heap[i] = rhs.heap[i];
  }
}

/** constructor
 *  Constructs a new heap with a predefined size
 *  Does not input any values
 *
 * @param _size The maximum number of indices within the heap
 */
MaxHeap::MaxHeap(int _size) : size(_size), index(0)
{
  grow(heap, size);
  heap[index++] = INT32_MIN;
}

/** destructor
 *  Empties the heap, freeing used memory
 */
MaxHeap::~MaxHeap()
{
  makeEmpty();
}

/** operator=
 *  Sets one existing MaxHeap equal to another existing MaxHeap
 *
 * @param rhs An existing MaxHeap
 * @return The copied MaxHeap object
 */
MaxHeap MaxHeap::operator=(MaxHeap rhs)
{
  if (this == &rhs) return *this;
  std::swap(heap, rhs.heap);
  size = rhs.size;
  index = rhs.index;
  return *this;
}


/********************************************************************************
* Public Member Functions
*********************************************************************************/

/** insert
 *  Calls private member to insert variable into our heap
 *
 * @param val The value to be inserted into the heap
 */
void MaxHeap::insert(int val)
{
  insert(heap, size, val);
}

/** del
 *  Removes the ROOT value from the heap
 */
void MaxHeap::del()
{
  del(heap);
}

/** print
 *  Outputs all values held within the heap
 */
void MaxHeap::print() const
{
  print(heap, index);
}

/** makeEmpty
 *  Deletes the heap object if it exists
 */
void MaxHeap::makeEmpty()
{
  if (!isEmpty()) {
    delete[] heap;
    heap = NULL;
    size = index = 0;
  }
}

/** findMin
 *  Finds and returns the minimum value stored within our heap
 *
 * @return The smallest value stored in our heap
 */
int MaxHeap::findMin() const
{
  int min = INT32_MAX;
  for (int i = ROOT; i < index; i++)
    if (min > heap[i]) min = heap[i];
  return min;
}

/** findMax
 *  Finds and returns the max value stored within our heap
 *
 * @return The largest value stored in our heap
 */
int MaxHeap::findMax() const
{
  return heap[ROOT];
}

/** isEmpty
 *  Checks if our heap is empty or not
 *
 * @return true if the heap is empty, false if it has contents
 */
bool MaxHeap::isEmpty() const
{
  return heap == NULL;
}

/** isFull
 *  Checks if our heap is full or not
 *
 * @return true if the heap is full, false if it is not
 */
bool MaxHeap::isFull() const
{
  // Offset for the 0 index
  return index >= size-1;
}


/********************************************************************************
* Private Member Functions
*********************************************************************************/

/** insert
 * @brief Inserts a given value into a heap array at the last free position
 *
 * @param heap Address of the heap array to modify
 * @param _size Last free position within the heap array
 * @param val Value to insert into the heap
 */
void MaxHeap::insert(int*& heap, int _size, int val)
{
  if (isFull()) grow(heap, _size * 2);
  heap[index] = val;
  //Check the root node < all parent nodes
  siftUp(heap, index++);
  // Increment index
}

/** del
 * @brief Delete at the root index of the heap (1)
 *
 * @param heap Address of the heap to modify
 */
void MaxHeap::del(int* heap)
{
  std::swap(heap[ROOT], heap[index-1]);
  heap[index-1] = int();
  //Check the root node > all child nodes
  siftDown(heap, ROOT);
}

/** print
 * @brief Print the contents of the heap array
 *        Start from the 0 index, regardless of the ROOT
 *
 * @param heap Address of the heap array
 * @param _index Last free position in the array
 */
void MaxHeap::print(int* heap, int _index) const
{
  if (isEmpty()) return;
  for (int i = 0; i < _index; i++)
    std::cout << "[" << heap[i] << "] | ";
  std::cout << std::endl;
}

/** grow
 * @brief Expands the maximum length of the heap
 *
 * @param heap Modifiable reference to the dynamic heap array to expand
 * @param _size The new maximum size for the given heap
 */
void MaxHeap::grow(int*& heap, int _size)
{
  if (isEmpty()) {
    // Offset size for the 0 index
    size = 2;
    heap = new int[size];
    // Store smallest int possible at 0 index to show its value isn't to be used
    heap[index++] = INT32_MIN;
    return;
  }
  int *newHeap = new int[_size];
  if (!isEmpty()) for (int i = 0; i < _size; i++)
    // Deep copy of previous heap
    newHeap[i] = heap[i];
  // Delete the previous heap before we reassign
  delete[] heap;
  size = _size;
  heap = newHeap;
}

/** siftUp
 * @brief Sorts the last item inserted into the heap against items above it
 *        Swap nodes until given item is < parent node
 *
 * @param heap Address of heap array to sort through
 * @param _index Last used position within the heap array
 */
void MaxHeap::siftUp(int* heap, int _index)
{
  // Swap until parent value > new value
  for(; heap[_index] > heap[_index / 2]; _index/=2)
  {
    if (heap[_index / 2] == INT32_MIN) return;
    std::swap(heap[_index], heap[_index / 2]);


  }
}

/** siftDown
 * @brief Sorts the item at the given currentMax against lower items in the heap
 *        Swap nodes until the given item is > all child nodes
 *
 * @param heap Address of heap array to sort through
 * @param currentMax Last known largest position within the heap
 */
void MaxHeap::siftDown(int* heap, int currentMax)
{
  int left = currentMax * 2; // Left subtree of the heap
  int right = currentMax * 2 + 1; // Right subtree of the heap
  // Set the last known largest position in the heap
  int largest = currentMax;

  // Check if the left tree value is > the last known largest
  if (left < index && heap[left] > heap[largest])
    largest = left;
  // Check if the right tree value is > the last known largest
  if (right < index && heap[right] > heap[largest])
    largest = right;

  // If there was any change in the last known largest node, siftDown again
  if (currentMax != largest) {
    std::swap(heap[currentMax], heap[largest]);
    siftDown(heap, largest);
  }
}
