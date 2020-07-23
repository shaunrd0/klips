/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: An example of a vector implementation                              ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## vector.cpp
*/

#include "vector.h"


/******************************************************************************
 * Constructors, Destructors, Operators
 *****************************************************************************/

/** copy constructor
 * @brief Construct a new Vector::Vector object from an existing one
 *        Creates a new deep copy of a given Vector
 *
 * @param rhs Vector object
 */
template<typename T>
Vector<T>::Vector(const Vector<T>& rhs)
{
  if (rhs.getIndex() >= 0) {
    curIndex = rhs.getIndex();
    // Avoid copying over unused indices from parent Vector
    maxSize = rhs.getSize();
    data = new T[curIndex];
    for (int i = 0; i <= rhs.getSize(); i++) {
      data[i] = rhs.getValue(i);
    }
  } 
  else {
    curIndex = -1;
    maxSize = 0;
    data = NULL;
  }
}

/** operator=
 * @brief Assign two Vector objects equal using copy constr and class destr
 *        Pass the rhs by value to create local copy, swap its contents
 *        Destructor called on previous Vector data at the end of this scope
 *
 * @param rhs Vector object passed by value, creating a local variable
 * @return Vector A deep copy of the rhs Vector object
 */
template<typename T>
Vector<T> Vector<T>::operator=(Vector<T> rhs)
{
  if (this == &rhs) return *this;
  // Swap the pointers, moving the previous head data to the local variable rhs
  std::swap(data, rhs.data);
  curIndex = rhs.getIndex();
  // Use the current size of the vector we are equal to
  // Avoids copying over unused indices
  maxSize = rhs.getSize();
  return *this;
}

/** destructor
 * @brief Destroy the Vector::Vector object
 */
template<typename T>
Vector<T>::~Vector()
{
  if (!isEmpty()) makeEmpty();
}


/******************************************************************************
 * Public Member Functions
 *****************************************************************************/

/** push
 * @brief Push a value to the end of our Vector
 *
 * @param val The value to be inserted
 */
template<typename T>
bool Vector<T>::push(T val)
{
  bool inserted = push(val, data);
  if (inserted)
    std::cout << "[" << val << "] was inserted into the vector\n";
  else std::cout << "[" << val << "] could not be inserted into the vector\n";
  return inserted;
}

/** pop
 * @brief returns the value at the Vector::data[curIndex] if it exists
 *        Once returned, the curIndex is decremented via data[curIndex--]
 *        If the vector is empty, returns INT32_MIN
 *
 * @return int The value held at the Node pointed to by Vector::data[index]
 */
template<typename T>
T Vector<T>::pop()
{
  T val;
  if (!isEmpty()) {
    val = pop(data);
    std::cout << "[" << val << "] has been popped from our Vector\n";
  }
  else std::cout << "Nothing to pop, our Vector is empty...\n";
  return val;
}

/** makeEmpty
 * @brief Empty this Vector object, deleting all associated data
 */
template<typename T>
void Vector<T>::makeEmpty()
{
  if (isEmpty()) {
    std::cout << "Cannot makeEmpty, our Vector is already empty...\n";
    return;
  }
  else makeEmpty(data);
}

/** peek
 * @brief returns the value at the end of the vector
 *  If the vector is empty, returns INT32_MIN
 *
 * @return int The value held at the current data[index] of the vector
 */
template<typename T>
T Vector<T>::peek() const
{
  T val = NULL;
  if (!isEmpty()) {
    val = peek(data);
    std::cout << "[" << peek(data) << "] is at the end of our vector\n";
  }
  else std::cout << "Nothing to peek, our vector is empty...\n";
  return val;
}

/** isEmpty
 * @brief Determine if the Vector is empty
 *
 * @return true If the Vector::data is NULL
 * @return false If the Vector::data contains any values
 */
template<typename T>
bool Vector<T>::isEmpty() const
{
  return data == NULL;
}

/** isFull
 * @brief Determine if the Vector is full
 *
 * @return true If the Vector::size is equal to the current index
 * @return false If the Vector::size is greater than the current index
 */
template<typename T>
bool Vector<T>::isFull() const
{
  return getSize() == getMax() || data == NULL;
}

/** print
 * @brief Output the data held by the Vector object
 *        Calls to the private print()
 */
template<typename T>
void Vector<T>::print() const
{
  if(!isEmpty()) print(data);
  else std::cout << "Nothing to print, our vector is empty...\n";
}

/** getMax
 * @brief Returns the literal maximum size of the vector
 *        Not offset to match any index - Vector with max size 3 has indices 0-2
 *
 * @return int at this->maxSize
 */
template<typename T>
T Vector<T>::getMax() const
{
  return maxSize;
}

/** getSize
 * @brief Returns the current size of the vector
 *        AKA the current number of indices being used, NOT the max indices
 * 
 * @return int at this->curIndex + 1
 */
template<typename T>
T Vector<T>::getSize() const
{
  return curIndex + 1;
}

/** getIndex
 * @brief Returns the current index of the vector
 *        AKA the last index the vector wrote to
 *
 * @return int at this->curIndex
 */
template<typename T>
T Vector<T>::getIndex() const
{
  return curIndex;
}

// TODO: use operator[](){...} instead

/** getValue
 * @brief Get the value stored at a given index within the vector
 * 
 * @param index The index containing the value to be returned
 * @return int The value held at the index given
 */
template<typename T>
T Vector<T>::getValue(T index) const
{
  return data[index];
}


/******************************************************************************
 * Private Member Functions
 *****************************************************************************/

/** push
 * @brief Private member to handle inserting value into the vector
 *
 * @param val Value to be inserted
 * @param data The data of the vector to push the value into
 *
 * @return true If the value was inserted
 * @return false If the value could not be inserted
 */
template<typename T>
bool Vector<T>::push(T val, T *&data)
{
  T *temp;
  if (isFull()) {
    if (maxSize <= 0) maxSize = 1;
    else maxSize *= 2;
    temp = new T[maxSize];
    for (int i = 0; i <= curIndex; i++) {
      temp[i] = data[i];
    }
    std::swap(data, temp);
  }
  curIndex += 1;
  data[curIndex] = val;
  return data[curIndex] == val;
}

/** pop
 * @brief Returns the value held at the last index within the Vector
 *        Decrements the curIndex after storing the value to be returned
 * 
 * @param data The Vector data to modify
 * @return int The value stored at the index removed from the end of the Vector
 */
template<typename T>
T Vector<T>::pop(T *&data)
{
  // We already know the vector is not empty from public pop()
  T val = data[curIndex--];
  if (curIndex < 0) makeEmpty(data);
  return val;
}

/** makeEmpty
 * @brief Private member to empty Vector object, deleting all associated data
 * 
 * @param data The data of the Vector to be deleted
 */
template<typename T>
void Vector<T>::makeEmpty(T *&data)
{
  delete[] data;
  maxSize = 0;
  curIndex = -1;
  data = NULL;
}

/** peek
 * @brief Private member to display the value at the end of our Vector
 * 
 * @param data The Vector data to peek
 * @return int The value stored at the end of the Vector
 */
template<typename T>
T Vector<T>::peek(T *data) const
{
  // We already know the vector is not empty from public peek()
  return data[curIndex];
}

/** print
 * @brief Output the contents of a Vector from the beginning to the end
 *
 * @param data The data within the Vector to output
 */
template<typename T>
void Vector<T>::print(T *data) const
{
  std::cout << "Vector Contents: ";
  for (int i = 0; i <= curIndex; i++) {
    std::cout << data[i] << " | ";
  }
  std::cout << std::endl;
}

template class Vector<int>;
template class Vector<std::string>;
