/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: An example of a circular doubly linked list                        ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## circledoublelist.cpp
*/

#include "circledoublelist.h"


/******************************************************************************
 * Constructors, Destructors, Operators
 *****************************************************************************/

/** copy constructor
 * @brief Construct a new CircleDoubleList::CircleDoubleList object from an existing one
 *
 * @param rhs CircleDoubleList object
 */
CircleDoubleList::CircleDoubleList(const CircleDoubleList& rhs)
{
  Node *cp = rhs.tail;
  Node *tempHead;
  if (cp == NULL) tail = NULL;
  else {
    tail = new Node(cp->data);
    tempHead = tail;
    while (cp->next != NULL) {
      cp = cp->next;
      tail->next = new Node(cp->data);
      tail = tail->next;
    }
    tail = tempHead;
  }
}

/** operator=
 * @brief Assign two CircleDoubleList objects equal using copy constr and class destr
 *        Pass the rhs by value to create local copy, swap its contents
 *        Destructor called on previous CircleDoubleList data at the end of this scope
 *
 * @param rhs CircleDoubleList object passed by value
 * @return CircleDoubleList A deep copy of the rhs CircleDoubleList object
 */
CircleDoubleList CircleDoubleList::operator=(CircleDoubleList rhs)
{
  if (this != &rhs) return *this;
  std::swap(tail, rhs.tail);
  return *this;
}

/** destructor
 * @brief Destroy the CircleDoubleList::CircleDoubleList object
 */
CircleDoubleList::~CircleDoubleList()
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
bool CircleDoubleList::insert(int val)
{
  bool inserted = insert(val, tail);
  if (inserted)
    std::cout << "[" << val << "] was inserted into the list\n";
  else std::cout << "[" << val << "] could not be inserted into the list\n";
  return inserted;
}

/** insert at
 * @brief Inserts a value in the place of a given key
 *        Key Node found is moved to the newNode->next positon
 *
 * @param key The value to search for to determine insert location
 * @param val The value to be inserted into the list
 */
bool CircleDoubleList::insert(int val, int key)
{
  // Check that we are not trying to insert at a position within an empty list
  if (tail == NULL) {
    std::cout << "Cannot insert at a key value using an empty list\n";
    return false;
  }

  bool inserted = insert(val, key, tail->next);
  if (inserted)
    std::cout << "[" << val << "] was inserted into the list\n";
  else std::cout << "[" << val << "] could not be inserted into the list\n";
  return inserted;
}

/** remove
 * @brief Removes a value in the list by calling overloaded private member and handling output
 *
 * @param val Value to be removed from the list
 * @return true If the value was removed from the list
 * @return false If the value was not removed from the list
 */
bool CircleDoubleList::remove(int val)
{
  // Check that we are not trying to remove from an empty list
  if (isEmpty()) {
    std::cout << "Cannot remove from an empty list\n";
    return false;
  }

  // Attempt to remove the item
  bool removed = remove(val, tail->next);
  if (removed)
    std::cout << "[" << val << "] was removed from the list\n";
  else std::cout << "[" << val << "] could not be removed from the list\n";
  return removed;
}

/** replace
 * @brief Replaces a value in the list by calling overloaded private member and handling output
 *
 * @param val Value to insert into the list
 * @param key Value to be replaced within the list
 * @return true If the key has been replaced in the list by val
 * @return false If the key has not been replaced in the list by val
 */
bool CircleDoubleList::replace(int val, int key)
{
  // Check that we are not trying to replace within an empty list
  if (isEmpty()) {
    std::cout << "Cannot replace anything within an empty list\n";
    return false;
  }

  // Attempt to replace the item
  bool replaced = replace(val, key, tail->next);
  if (replaced)
    std::cout << "[" << key << "] was replaced by [" << val << "] in the list\n";
  else std::cout << "[" << key << "] could not be replaced by [" << val << "] in the list\n";
  return replaced;
}

/** makeEmpty
 * @brief Empty this CircleDoubleList object, deleting all associated Nodes
 */
void CircleDoubleList::makeEmpty()
{
  Node *nextNode;
  if (isEmpty()) return;
  
  // Start deletion from the head of the list
  nextNode = tail->next;
  while(!isEmpty()) {
    nextNode = nextNode->next;
    remove(nextNode->prev->data);
  }
  nextNode = NULL;
  return;
}

/** isEmpty
 * @brief Determine if the CircleDoubleList is empty
 *
 * @return true If the CircleDoubleList::tail is NULL
 * @return false If the CircleDoubleList::tail contains data
 */
bool CircleDoubleList::isEmpty() const
{
  return tail == NULL;
}

/** peek
 * @brief returns the value at the CircleDoubleList::head
 *
 * @return int The value held at the Node pointed to by CircleDoubleList::head
 */
int CircleDoubleList::peek() const
{
  if (!isEmpty())
    std::cout << "[" << tail->next->data << "] is at the top of our list\n";
  else std::cout << "Nothing to peek, our list is empty...\n";
  return tail->data;
}

/** print
 * @brief Output the data held by the CircleDoubleList object
 *        Calls to the private print()
 */
void CircleDoubleList::print() const
{
  // Print from the head of our list
  if(!isEmpty()) print(tail->next);
  else std::cout << "Nothing to print, our list is empty...\n";
}

/** find
 * @brief Calls to overloaded private member find() and handles output
 *
 * @param val The value to search for within our CircleDoubleList
 * @return true If the value was found in this CircleDoubleList
 * @return false If the value was not found in this CircleDoubleList
 */
bool CircleDoubleList::find(int val) const
{
  // Check that we are not trying to search an empty list
  if (isEmpty()) {
    std::cout << "Cannot search an empty list\n";
    return false;
  }

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
 * @param tail The tail node of the list to insert the value into
 * @return true If the value was inserted
 * @return false If the value could not be inserted
 */
bool CircleDoubleList::insert(int val, Node *&tail)
{
  Node *newNode = new Node(val);
  if (!isEmpty()) {
    // Relink the current head to the node after newNode
    newNode->next = tail->next;
    tail->next->prev = newNode;
    // Relink our head and tail nodes, makine newNode the head node
    tail->next = newNode;
    newNode->prev = tail;
  }
  else tail = newNode;
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
bool CircleDoubleList::insert(int val, int key, Node *&head)
{
  Node *newNode = new Node(val);
  // Let insert() handle inserting at the head
  if (head->data == key) return insert(val);

  // Get the node which contains our value
  Node *keyNode = find(key, head);
  // If there was no keyNode found, the key is not in our list, do nothing
  if (keyNode == NULL) return false;
  // Insert the newNode in front of the previous to the keyNode
  // [head]->[key]->[tail]
  // [head]->[new]->[key]->[tail]
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
bool CircleDoubleList::remove(int val, Node *&head)
{
  // If there is only one node in the list
  // Synonymous with: if (tail = tail->next)
  if (head == head->next) {
    delete tail;
    tail = NULL;
    // Nothing to relink, list is empty
    return true;
  }
  
  // If the head node contains the value to remove
  if (head->data == val) {
    Node *temp = head;
    // Move head to the next node in the list
    head = head->next;
    // Relink head and tail nodes
    head->prev = tail;
    tail->next = head;
    // Delete dangling pointer created by relinking
    delete temp;
    return true;
  }
  
  // If the tail node contains the value to remove
  if (tail->data == val) {
    Node *temp = tail;
    // Move tail to the previous node in the list
    tail = tail->prev;
    // Relink head and tail nodes
    head->prev = tail;
    tail->next = head;
    // Delete dangling pointer created by relinking
    delete temp;
    return true;
  }

  // Search for the value further within our list
  Node *keyNode = find(val, head);
  // If NULL, the value does not exist within our list
  if (keyNode == NULL) return false;
  // Relink surrounding nodes to make keyNode a dangling ptr
  keyNode->next->prev = keyNode->prev;
  keyNode->prev->next = keyNode->next;
  // Delete the dangling node created by relinking above
  delete keyNode;
  keyNode = NULL;
  return true;
}

/** replace
 * @brief Private member to replace values within the list
 *
 * @param val Value to insert into the list
 * @param key Value to be replaced within the list
 * @param head Head node of the list to modify
 * @return true If the key has been replaced by val within the list
 * @return false If the key has not been replaced by val within the list
 */
bool CircleDoubleList::replace(int val, int key, Node *&head)
{
  Node *replacee = find(key, head);
  if (replacee == NULL) return false;
  replacee->data = val;
  return true;
}

/** find
 * @brief Find and return a Node which contains the given value
 *
 * @param val The value to search for within our CircleDoubleList
 * @param start The node to begin the search from, returns on the first found result
 * @return CircleDoubleList::Node* A pointer to the Node containing the search value
 */
CircleDoubleList::Node* CircleDoubleList::find(int val, Node *start) const
{
  // If given a NULL list, return NULL
  // If given a head which contains the requested value, return the foundNode
  if (start == NULL || start->data == val) return start;

  // Copy our start position, check its value 
  Node *foundNode = start;
  if (foundNode->data == val) return foundNode;
  // Keep checking the next node until we reach the start value again
  while (foundNode->next != start) {
    foundNode = foundNode->next;
    if (foundNode->data == val) return foundNode;
  }
  // If we have not yet returned a foundNode, the key is not in our list
  return NULL;
}

/** print
 * @brief Output the contents of a CircleDoubleList from the given Node to NULL
 *
 * @param start The Node to begin traversing output from
 */
void CircleDoubleList::print(Node *start) const
{
  Node *temp = start;
  std::cout << "List Contents: " << temp->data << " | ";
  temp = temp->next;
  while (temp != start) {
    std::cout << temp->data << " | ";
    temp = temp->next;
  }
  std::cout << std::endl;
}
