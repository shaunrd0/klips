/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: An example of a circular singly linked list                        ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## circlesinglelist.cpp
*/

#include "circlesinglelist.h"

#include <cstdint>

/******************************************************************************
 * Constructors, Destructors, Operators
 *****************************************************************************/

/** copy constructor
 * @brief Construct a new CircleSingleList::CircleSingleList object from an existing one
 *
 * @param rhs CircleSingleList object
 */
CircleSingleList::CircleSingleList(const CircleSingleList& rhs)
{
  Node *cp = rhs.tail;
  Node *tempTail;
  if (cp == NULL) tail = NULL;
  else {
    tail = new Node(cp->data);
    tempTail = tail;
    while (cp->next != NULL) {
      cp = cp->next;
      tail->next = new Node(cp->data);
      tail = tail->next;
    }
    tail = tempTail;
  }
}

/** operator=
 * @brief Deep copy of the rhs CircleSingleList object
 *        Pass rhs by value to create local copy, swap its data with our tail
 *        Swapped local copy deleted at end of scope using destructor
 *
 * @param rhs CircleSingleList object
 * @return CircleSingleList& A deep copy of the rhs CircleSingleList
 */
CircleSingleList CircleSingleList::operator=(CircleSingleList rhs)
{
  if (this == &rhs) return *this;
  else std::swap(tail, rhs.tail);
  return *this;
}

/** destructor
 * @brief Destroy the CircleSingleList object
 */
CircleSingleList::~CircleSingleList()
{
  makeEmpty();
}


/******************************************************************************
 * Public Member Functions
 *****************************************************************************/

/** insert
 * @brief Inserts a value to the head of our linked list
 *
 * @param x The value to be inserted
 */
bool CircleSingleList::insert(int val)
{
  bool inserted = insert(val, tail);
  if (inserted)  std::cout << "[" << val << "] was inserted into the list\n";
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
bool CircleSingleList::insert(int val, int key)
{
  if (isEmpty()) {
    std::cout << "Cannot insert at an existing value using an empty list...\n";
    return false;
  }

  bool inserted = insert(val, key, tail);
  if (inserted) std::cout << "[" << val << "] was inserted into the list\n";
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
bool CircleSingleList::remove(int val)
{
  if (isEmpty()) {
    std::cout << "Cannot remove any values from an empty list...\n";
    return false;
  }

  bool removed = remove(val, tail);
  if (removed) std::cout << "[" << val << "] was removed from the list\n";
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
bool CircleSingleList::replace(int val, int key)
{
  if (isEmpty()) {
    std::cout << "Cannot replace any values from an empty list...\n";
    return false;
  }

  bool replaced = replace(val, key, tail);
  if (replaced) std::cout << "[" << key << "] was replaced by "
    << "[" << val << "] in the list\n";
  else std::cout << "[" << key << "] could not be replaced by "
    << "[" << val << "] in the list\n";
  return replaced;
}

/** makeEmpty
 * @brief Empty this CircleSingleList object, deleting all associated Nodes
 */
void CircleSingleList::makeEmpty()
{
  Node *nextNode, *temp;

  // If the list is empty
  if (tail == NULL) return;

  // If the list has members other than itself, keep a pointer to them
  if (tail != tail->next) nextNode = tail->next;
  // Delete the list nodes until we hit the tail
  while(nextNode != tail) {
    // Save pointer to delete previous node
    temp = nextNode;
    // Move to the next node
    nextNode = nextNode->next;
    // Delete the previous node and set it to NULL
    delete temp;
    temp = NULL;
  }

  // Always delete the tail node and set it to NULL
  delete tail;
  tail = NULL;
}

/** isEmpty
 * @brief Determine if the CircleSingleList is empty
 *
 * @return true If the CircleSingleList::tail is NULL
 * @return false If the CircleSingleList::tail contains data
 */
bool CircleSingleList::isEmpty() const
{
  return tail == NULL;
}

/** peek
 * @brief return the value at the head of the list
 *
 * @return int The value held at the Node at the head of our linked list
 */
int CircleSingleList::peek() const
{
  // If there is only one data member, a circular list node will point to itself
  if (!isEmpty())
    std::cout << "[" << tail->next->data << "] is at the top of our list\n";
  else std::cout << "Nothing to peek, our list is empty...\n";
  // If the list has data we return it, otherwise we return the smallest possible int (error)
  return (!isEmpty()) ? tail->next->data : INT32_MIN;
}

/** print
 * @brief Output the data held by the CircleSingleList object
 *        Calls to the private print()
 */
void CircleSingleList::print() const
{
  // Print the list starting from the head node
  if(!isEmpty()) print(tail->next);
  else std::cout << "Nothing to print, our list is empty...\n";
}

/** find
 * @brief Calls to the private member find() and handles return cases
 *
 * @param val The value to search for within our CircleSingleList
 * @return true If the value was found in this CircleSingleList
 * @return false If the value was not found in this CircleSingleList
 */
bool CircleSingleList::find(int val) const
{
  Node *result = find(val, tail);
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
 * @param tail The tail of the list to insert the value into
 * @return true If the value was inserted
 * @return false If the value could not be inserted
 */
bool CircleSingleList::insert(int val, Node *&tail)
{
  Node *newNode = new Node(val);
  // If the list is not empty, update next pointer to head node
  if (!isEmpty()) newNode->next = tail->next;
  else tail = newNode;
  // Always set head to our newNode
  tail->next = newNode;
  return true;
}

/** insert at
 * @brief Private member to handle inserting a value at a key within our list
 *
 * @param val Value to be inserted
 * @param key Key value to search for within the list
 * @param tail Tail node of the list to insert to
 * @return true If the value was inserted
 * @return false If the value was not inserted
 */
bool CircleSingleList::insert(int val, int key, Node *&tail)
{
  Node *newNode = new Node(val);
  if (isEmpty()) return false;
  // Let insert() handle inserting at the head
  else if (tail->next->data == key) return insert(val);

  Node *keyNode = findPrevious(key);
  // If there was no keyNode found, the key does is not in our list
  // Don't insert anything, return false and let caller decide whats next
  if (keyNode == NULL) return false;
  // Set the newNode to come between the keyNode and the Node we are inserting at
  // [keyNode]->[next]
  // [keyNode]->[newNode]->[next]
  // Where (keyNode->next->data == key) and keyNode is given by findPrevious()
  newNode->next = keyNode->next;
  keyNode->next = newNode;
  return true;
}

/** remove
 * @brief Private member to remove values from the list
 *
 * @param val Value to be removed
 * @param tail Tail of the list to remove the value from
 * @return true If the value has been removed from the list
 * @return false If the value has not been removed from the list
 */
bool CircleSingleList::remove(int val, Node *&tail)
{
  Node *exile, *tempHead;
  Node *prevNode = findPrevious(val);
  // If findPrevious returns NULL, the value was not found
  if (prevNode == NULL) return false;

  // If the node found is the only member of the list
  if (prevNode == prevNode->next) {
    // Delete, reset list to NULL
    delete tail;
    tail = NULL;
    return true;
  }
  // If the node to remove is the tail and the list has > 1 members
  else if (prevNode->next == tail) {
    tempHead = tail->next;
    exile = prevNode->next;
    // Create the new tail
    tail = prevNode;
    // Link the head Node, skipping over the exile Node
    tail->next = tempHead;
  }
  else {
    // Get a ptr to the member we are removing from the list
    exile = prevNode->next;
    // Relink the list, skipping the exile node
    prevNode->next = prevNode->next->next;
  }

  // Delete the dangling ptr to the exile Node we removed from the list
  delete exile;
  exile = NULL;
  return true;
}

/** replace
 * @brief Private member to replace values within the list
 *
 * @param val Value to insert into the list
 * @param key Value to be replaced within the list
 * @param tail Tail of the list to replace the value
 * @return true If the key has been replaced by val within the list
 * @return false If the key has not been replaced by val within the list
 */
bool CircleSingleList::replace(int val, int key, Node *&tail)
{
  Node *replacee = find(key, tail);
  if (replacee == NULL) return false;
  replacee->data = val;
  return true;
}

/** find
 * @brief Find and return a Node which contains the given value
 *
 * @param val The value to search for within our CircleSingleList
 * @param start The Node to begin the search at within the linked list, usually the head node
 * @return CircleSingleList::Node* A pointer to the Node containing the search value
 */
CircleSingleList::Node* CircleSingleList::find(int val, Node *start) const
{
  // Check the first Node, return if it is the value requested
  if (start->data == val) return start;
  Node *foundNode = start->next;
  // Move through the list, checking each member until we reach the start Node
  while (foundNode != start) {
    if (foundNode->data == val) return foundNode;
    foundNode = foundNode->next;
  }
  // If we have not yet returned a foundNode, the key is not in our list
  return NULL;
}

/** findPrevious
 * @brief Find and return the Node before a given value
 *
 * @param val The value to search for within our CircleSingleList
 * @return CircleSingleList::Node* A pointer to the Node previous to the  given value
 */
CircleSingleList::Node* CircleSingleList::findPrevious(int val) const
{
  if (isEmpty()) return NULL;
  else if (tail->next->data == val) return tail;

  // Create temp ptr to the head of our list
  Node *tempHead = tail->next;
  // Move through the list until we reach the head node again
  while (tempHead->next != tail->next) {
    // Check the value within the next node, if found return it
    if (tempHead->next->data == val) return tempHead;
    else tempHead = tempHead->next;
  }

  return NULL;
}

/** print
 * @brief Output the contents of a CircleSingleList until we hit a matching node
 *
 * @param start The Node to begin traversing output from
 */
void CircleSingleList::print(Node *start) const
{
  Node *temp = start;
  std::cout << "List Contents: " << temp->data << " | ";
  temp = temp->next;
  // Until we reach the start node again, print the list contents
  while (temp != start) {
    std::cout << temp->data << " | ";
    temp = temp->next;
  }
  std::cout << std::endl;
}
