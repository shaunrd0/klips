/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: An example of a doubly linked list                                 ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## doublelist.cpp
*/

#include "doublelist.h"


/******************************************************************************
 * Constructors, Destructors, Operators
 *****************************************************************************/

/** copy constructor
 * @brief Construct a new DoubleList::DoubleList object from an existing one
 *
 * @param rhs DoubleList object
 */
template <typename T>
DoubleList<T>::DoubleList(const DoubleList& rhs)
{
  Node *cp = rhs.head;
  Node *tempHead;
  if (cp == NULL) head = NULL;
  else {
    head = new Node(cp->data);
    tempHead = head;
    while (cp->next != NULL) {
      cp = cp->next;
      head->next = new Node(cp->data);
      head = head->next;
    }
    head = tempHead;
  }
}

/** operator=
 * @brief Assign two DoubleList objects equal using copy constr and class destr
 *        Pass the rhs by value to create local copy, swap its contents
 *        Destructor called on previous DoubleList data at the end of this scope
 *
 * @param rhs DoubleList object passed by value
 * @return DoubleList A deep copy of the rhs DoubleList object
 */
template <typename T>
DoubleList<T> DoubleList<T>::operator=(DoubleList<T> rhs)
{
  if (this == &rhs) return *this;
  std::swap(head, rhs.head);
  return *this;
}

/** destructor
 * @brief Destroy the DoubleList::DoubleList object
 */
template <typename T>
DoubleList<T>::~DoubleList()
{
  makeEmpty();
}


/******************************************************************************
 * Public Member Functions
 *****************************************************************************/

/** insert
 * @brief Inserts a value to the head of our linked list
 *
 * @param val The value to be inserted
 */
template <typename T>
bool DoubleList<T>::insert(T val)
{
  bool inserted = insert(val, head);
  if (inserted)
    std::cout << "[" << val << "] was inserted into the list\n";
  else std::cout << "[" << val << "] could not be inserted into the list\n";
  return inserted;
}

/** insert at
 * @brief Inserts a value in the place of a given key
 *        Key Node found is moved to the newNode->next position
 *
 * @param key The value to search for to determine insert location
 * @param val The value to be inserted into the list
 */
template <typename T>
bool DoubleList<T>::insert(T val, T key)
{
  bool inserted = insert(val, key, head);
  if (inserted)
    std::cout << "[" << val << "] was inserted into the list\n";
  else std::cout << "[" << val << "] could not be inserted into the list\n";
  return inserted;
}

/** remove
 * @brief Removes a value in the list by calling a private member and handling output
 *
 * @param val Value to be removed from the list
 * @return true If the value was removed from the list
 * @return false If the value was not removed from the list
 */
template <typename T>
bool DoubleList<T>::remove(T val)
{
  bool removed = remove(val, head);
  if (removed)
    std::cout << "[" << val << "] was removed from the list\n";
  else std::cout << "[" << val << "] could not be removed from the list\n";
  return removed;
}

/** replace
 * @brief Replaces a value in the list by calling a private member and handling output
 *
 * @param val Value to insert into the list
 * @param key Value to be replaced within the list
 * @return true If the key has been replaced in the list by val
 * @return false If the key has not been replaced in the list by val
 */
template <typename T>
bool DoubleList<T>::replace(T val, T key)
{
  bool replaced = replace(val, key, head);
  if (replaced)
    std::cout << "[" << key << "] was replaced by [" << val << "] in the list\n";
  else std::cout << "[" << key << "] could not be replaced by [" << val << "] in the list\n";
  return replaced;
}

/** makeEmpty
 * @brief Empty this DoubleList object, deleting all associated Nodes
 */
template <typename T>
void DoubleList<T>::makeEmpty()
{
  Node *nextNode, *temp;

  if (head == NULL) return;
  nextNode = head->next;
  delete head;
  head = NULL;
  while(nextNode != NULL) {
    temp = nextNode;
    nextNode = nextNode->next;
    delete temp;
    temp = NULL;
  }
}

/** isEmpty
 * @brief Determine if the DoubleList is empty
 *
 * @return true If the DoubleList::head is NULL
 * @return false If the DoubleList::head contains data
 */
template <typename T>
bool DoubleList<T>::isEmpty() const
{
  return head == NULL;
}

/** peek
 * @brief returns the value at the DoubleList::head
 *
 * @return T The value held at the Node pointed to by DoubleList::head
 */
template <typename T>
T DoubleList<T>::peek() const
{
  if (!isEmpty())
    std::cout << "[" << head->data << "] is at the top of our list\n";
  else std::cout << "Nothing to peek, our list is empty...\n";
  // If the list has data we return it, otherwise we return the smallest possible int (error)
  return (!isEmpty()) ? head->data : T();
}

/** print
 * @brief Output the data held by the DoubleList object
 *        Calls to the private print()
 */
template <typename T>
void DoubleList<T>::print() const
{
  if(!isEmpty()) print(head);
  else std::cout << "Nothing to print, our list is empty...\n";
}

/** find
 * @brief Calls to the private member find() and handles return cases
 *
 * @param val The value to search for within our DoubleList
 * @return true If the value was found in this DoubleList
 * @return false If the value was not found in this DoubleList
 */
template <typename T>
bool DoubleList<T>::find(T val) const
{
  Node *result = find(val, head);
  if( result == NULL) {
    std::cout << "[" << val << "] Was not found in our list\n";
    return false;
  }

  std::cout << "[" << result->data << "] Was found in our list\n";
  return true;
}


/******************************************************************************
 * Private Member Functions
 *****************************************************************************/

/** insert
 * @brief Private member to handle inserting value into the list
 *
 * @param val Value to be inserted
 * @param head The head of the list to insert the value into
 * @return true If the value was inserted
 * @return false If the value could not be inserted
 */
template <typename T>
bool DoubleList<T>::insert(T val, Node *&head)
{
  Node *newNode = new Node(val);
  // If the list is not empty, update next pointer to head node
  if (!isEmpty()) {
    newNode->next = head;
    // Create a prev ptr for the head node
    head->prev = newNode;
  }
  // Always set head to our newNode
  head = newNode;
  return true;
}

/** insert at
 * @brief Private member to handle inserting a value at a key within our list
 *
 * @param val Value to be inserted
 * @param key Key value to search for within the list
 * @param head Head node of the list to insert to
 * @return true If the value was inserted
 * @return false If the value was not inserted
 */
template <typename T>
bool DoubleList<T>::insert(T val, T key, Node *&head)
{
  Node *newNode = new Node(val);
  if (isEmpty()) return false;
  // Let insert() handle inserting at the head
  else if (head->data == key) return insert(val, head);

  Node *keyNode = find(key, head);
  // If there was no keyNode found, the key does is not in our list
  // Don't insert anything, return false and let caller decide whats next
  if (keyNode == NULL) return false;
  // Insert the newNode infront of the previous to the keyNode
  newNode->prev = keyNode->prev;
  keyNode->prev->next = newNode;

  // Change the keyNode->prev ptr to newNode
  newNode->next = keyNode;
  keyNode->prev = newNode;
  return true;
}

/** remove
 * @brief Private member to remove values from the list
 *
 * @param val Value to be removed
 * @param head Head of the list to remove the value from
 * @return true If the value has been removed from the list
 * @return false If the value has not been removed from the list
 */
template <typename T>
bool DoubleList<T>::remove(T val, Node *&head)
{
  if (head == NULL) return false;
  else if (head->data == val) {
    head = head->next;
    return true;
  }

  Node *keyNode = find(val, head);
  if (keyNode == NULL) return false;
  Node *gtfo = keyNode;
  if (keyNode->next != NULL) keyNode->next->prev = keyNode->prev;
  if (keyNode->prev != NULL) keyNode->prev->next = keyNode->next;
  delete gtfo;
  gtfo = NULL;
  return true;
}

/** replace
 * @brief Private member to replace values within the list
 *
 * @param val Value to insert into the list
 * @param key Value to be replaced within the list
 * @param head Head of the list to replace the value
 * @return true If the key has been replaced by val within the list
 * @return false If the key has not been replaced by val within the list
 */
template <typename T>
bool DoubleList<T>::replace(T val, T key, Node *&head)
{
  Node *replacee = find(key, head);
  if (replacee == NULL) return false;
  replacee->data = val;
  return true;
}

/** find
 * @brief Find and return a Node which contains the given value
 *
 * @param val The value to search for within our DoubleList
 * @param start The Node to begin the search from
 * @return DoubleList::Node* A pointer to the Node containing the search value
 */
template <typename T>
typename DoubleList<T>::Node* DoubleList<T>::find(T val, Node *start) const
{
  // If given a NULL list, return NULL
  // If given a head which contains the requested value, return the foundNode
  if (start == NULL || start->data == val) return start;

  Node *foundNode = start;
  while (foundNode->next != NULL) {
    foundNode = foundNode->next;
    if (foundNode->data == val) return foundNode;
  }
  // If we have not yet returned a foundNode, the key is not in our list
  return NULL;
}

/** print
 * @brief Output the contents of a DoubleList from the given Node to NULL
 *
 * @param start The Node to begin traversing output from
 */
template <typename T>
void DoubleList<T>::print(Node *start) const
{
  Node *temp = start;
  std::cout << "List Contents: ";
  while (temp != NULL) {
    std::cout << temp->data << " | ";
    temp = temp->next;
  }
  std::cout << std::endl;
}

template class DoubleList<TYPE>;
