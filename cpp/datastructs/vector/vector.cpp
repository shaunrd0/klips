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
// TODO: Fix const, destr, op=

/** copy constructor
 * @brief Construct a new Vector::Vector object from an existing one
 *        Creates a new deep copy of a given Vector
 *
 * @param rhs Vector object
 */
Vector::Vector(const Vector& rhs)
{
  if (rhs.getSize() >= 0) {
    curIndex = rhs.getSize();
    maxSize = rhs.getMax();
    data = new int[curIndex];
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
 * @param rhs Vector object passed by valuIt would be easier to emulate the android app on a PCe
 * @return Vector A deep copy of the rhs Vector object
 */
Vector Vector::operator=(Vector rhs)
{
  if (this == &rhs) return *this;
  // Swap the pointers, moving the previous head data to the local variable rhs 
  std::swap(data, rhs.data);
  return *this;
}

/** destructor
 * @brief Destroy the Vector::Vector object
 */
Vector::~Vector()
{
  if (getSize() + 1 >= 1) makeEmpty();
}


/******************************************************************************
 * Public Member Functions
 *****************************************************************************/

/** push
 * @brief Push a value to the end of our Vector
 *
 * @param x The value to be inserted
 */
bool Vector::push(int val)
{
  bool inserted = push(val, data);
  if (inserted)
    std::cout << "[" << val << "] was inserted into the vector\n";
  else std::cout << "[" << val << "] could not be inserted into the vector\n";
  return inserted;
}

/** pop
 * @brief returns the value at the Vector::data[index -1] if it exists
 *        If the vector is empty, returns INT32_MIN
 *
 * @return int The value held at the Node pointed to by Vector::data[index -1]
 */
int Vector::pop()
{
  int val = INT32_MIN;
  if (!isEmpty()) {
    // (!isEmpty()) ? data[index - 1] : INT32_MIN;
    val = pop(data);
    std::cout << "[" << val << "] has been popped from our Vector\n";
  }
  else std::cout << "Nothing to pop, our stack is empty...\n";
  return val;
}

/** makeEmpty
 * @brief Empty this Vector object, deleting all associated data
 */
void Vector::makeEmpty()
{
  if (isEmpty()) {
    std::cout << "Our vector is empty...\n";
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
int Vector::peek() const
{
  int val = INT32_MIN;
  if (!isEmpty()) {
    // (!isEmpty()) ? data[index - 1] : INT32_MIN;
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
bool Vector::isEmpty() const
{
  return curIndex <= -1;
}

/** isFull
 * @brief Determine if the Vector is full
 *
 * @return true If the Vector::size is equal to the current index
 * @return false If the Vector::size is greater than the current index
 */
bool Vector::isFull() const
{
  return getSize() == getMax() || data == NULL;
}

/** print
 * @brief Output the data held by the Vector object
 *        Calls to the private print()
 */
void Vector::print() const
{
  if(!isEmpty()) print(data);
  else std::cout << "Nothing to print, our vector is empty...\n";
}

/** getMax
 * @brief Returns the maximum size of the vector
 * 
 * @return int at this->maxSize
 */
int Vector::getMax() const
{
  return maxSize;
}

/** getSize
 * @brief Returns the current size of the vector
 * 
 * @return int at this->curIndex + 1
 */
int Vector::getSize() const
{
  return curIndex + 1;
}

/** getIndex
 * @brief Returns the current index of the vector
 * 
 * @return int at this->curIndex
 */
int Vector::getIndex() const
{
  return curIndex;
}

// TODO: use operator[](){...} instead

/** getValue
 * @brief Get the value stored at a given index within the vector
 * 
 * @param index 
 * @return int 
 */
int Vector::getValue(int index) const
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
 * @param head The head of the vector to push the value into
 * @return true If the value was inserted
 * @return false If the value could not be inserted
 */
bool Vector::push(int val, int *&data)
{
  int *temp;
  if (isFull()) {
    if (maxSize <= 0) maxSize = 1;
    else maxSize *= 2;
    temp = new int[maxSize];
    for (int i = 0; i <= curIndex; i++) {
      temp[i] = data[i];
    }
    // data = temp;
    std::swap(data, temp);
  }
  curIndex += 1;
  data[curIndex] = val;
  return data[curIndex] == val;
}

/** pop
 * @brief 
 * 
 * @param data 
 * @return int 
 */
int Vector::pop(int *&data)
{
  // We already know the vector is not empty from public pop()
  int val = data[curIndex--];
  return val;
}

/** makeEmpty
 * @brief Private member to empty this Vector object, deleting all associated Nodes
 *        Does not print any output. Avoids destructors printing to cout
 * 
 * @param head The head of the stack to be deleted
 * 
 */
void Vector::makeEmpty(int *&data)
{
  delete[] data;
  maxSize = 0;
  curIndex = -1;
  data = NULL;
}

/** peek
 * @brief 
 * 
 * @param data 
 * @return int 
 */
int Vector::peek(int *data) const
{
  // We already know the vector is not empty from public peek()
  return data[curIndex];
}

/** print
 * @brief Output the contents of a Vector from the beginning to the end
 */
void Vector::print(int *data) const
{
  // int *temp = data;
  std::cout << "Vector Contents: ";
  for (int i = 0; i <= curIndex; i++) {
    std::cout << data[i] << " | ";
  }
  std::cout << std::endl;
}
