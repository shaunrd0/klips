/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: An example of a queue implementation using linked lists            ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## queuelist.cpp
*/

#include "queuelist.h"

#include <cstdint>

/******************************************************************************
 * Constructors, Destructors, Operators
 *****************************************************************************/

/** copy constructor
 * @brief Construct a new QueueList::QueueList object from an existing one
 *        Creates a new deep copy of a given QueueList
 *
 * @param rhs QueueList object
 */
QueueList::QueueList(const QueueList& rhs)
{
  Node *cp = rhs.head;
  Node *tempHead;
  // If we are copying from an empty queue, create a new QueueList with a NULL head
  if (cp == NULL) head = NULL;
  else {
    // If the queue has data, initialize a new queue with the head data
    head = new Node(cp->data);
    // Keep a temporary head node so we can return to it later
    tempHead = head;
    while (cp->next != NULL) {
      // Until we hit an end, create new nodes with the next node data
      cp = cp->next;
      head->next = new Node(cp->data);
      head = head->next;
    }
    tail = head;
    head = tempHead;
  }
}

/** operator=
 * @brief Assign two QueueList objects equal using copy constr and class destr
 *        Pass the rhs by value to create local copy, swap its contents
 *        Destructor called on previous QueueList data at the end of this scope
 *
 * @param rhs QueueList object passed by value
 * @return QueueList A deep copy of the rhs QueueList object
 */
QueueList QueueList::operator=(QueueList rhs)
{
  if (this == &rhs) return *this;
  // Swap the pointers, moving the previous head data to the local variable rhs 
  std::swap(head, rhs.head);
  return *this;
}

/** destructor
 * @brief Destroy the QueueList::QueueList object
 */
QueueList::~QueueList()
{
  makeEmpty(head);
}


/******************************************************************************
 * Public Member Functions
 *****************************************************************************/

/** enqueue
 * @brief Queue a value to the tail of our linked list
 *
 * @param val The value to be inserted into the queue
 */
bool QueueList::enqueue(int val)
{
  bool inserted = enqueue(val, tail);
  if (inserted)
    std::cout << "[" << val << "] was inserted into the queue\n";
  else std::cout << "[" << val << "] could not be inserted into the queue\n";
  return inserted;
}

/** dequeue
 * @brief returns the value at the QueueList::head and moves head to the next in queue
 *
 * @return int The value held at the Node pointed to by QueueList::head
 */
int QueueList::dequeue()
{
  if (!isEmpty())
    std::cout << "[" << dequeue(head) << "] has been removed from our queue\n";
  else std::cout << "Nothing to dequeue, our queue is empty...\n";
  // If the queue has data we return it, otherwise we return the smallest possible int (error)
  return (!isEmpty()) ? head->data : INT32_MIN;
}

/** next
 * @brief returns the value at the QueueList::head
 *
 * @return int The value held at the Node pointed to by QueueList::head
 */
int QueueList::next() const
{
  if (!isEmpty())
    std::cout << "[" << head->data << "] is next in queue\n";
  else std::cout << "Our queue is empty...\n";
  // If the queue has data we return it, otherwise we return the smallest possible int (error)
  return (!isEmpty()) ? head->data : INT32_MIN;
}

/** isEmpty
 * @brief Determine if the QueueList is empty
 *
 * @return true If the QueueList::head is NULL
 * @return false If the QueueList::head contains data
 */
bool QueueList::isEmpty() const
{
  return head == NULL;
}

/** print
 * @brief Output the data held by the QueueList object
 *        Calls to the private print()
 */
void QueueList::print() const
{
  if(!isEmpty()) print(head);
  else std::cout << "Nothing to print, our queue is empty...\n";
}

/** makeEmpty
 * @brief Empty this QueueList object, deleting all associated Nodes
 */
void QueueList::makeEmpty()
{
  Node *nextNode, *temp;

  if (head == NULL) std::cout << "Our queue is empty...\n";
  else {
    nextNode = head->next;
    delete head;
    head = NULL;
    tail = NULL;
    while(nextNode != NULL) {
      temp = nextNode;
      nextNode = nextNode->next;
      delete temp;
      temp = NULL;
    }

  }
}


/******************************************************************************
 * Private Member Functions
 *****************************************************************************/

/** queue
 * @brief Private member to handle inserting value into the back of the queue
 *
 * @param val Value to be inserted
 * @param tail The tail of the queue to insert into
 * @return true If the value was inserted
 * @return false If the value could not be inserted
 */
bool QueueList::enqueue(int val, Node *&tail)
{
  Node *newNode = new Node(val);
  // If the queue is not empty, update next pointer to tail node
  if (!isEmpty()) {
    tail->next = newNode;
  }
  else head = newNode;
  // Always set tail to our newNode
  tail = newNode;
  return true;
}

/** dequeue
 * @brief Removes a node from the front of the queue
 * 
 * @param head The head of the queue to remove a node from
 * @return int The value held at the node removed
 */
int QueueList::dequeue(Node *&head)
{
  // We already know the queue is not empty from public dequeue()
  Node *temp = head;
  // Store the data at the front of the queue before we delete the node
  int data = head->data;

  // If there is only one item in the queue 
  if (temp == tail) {
    tail = head = NULL;
    delete temp;
    return data;
  }

  // Move the front of the queue to the next node
  head = head->next;
  // tail->next = NULL;
  // Delete the previous head node
  delete temp;
  return data;
}

/** print
 * @brief Output the contents of a QueueList from the given Node to NULL
 *
 * @param start The Node to begin traversing output from
 */
void QueueList::print(Node *start) const
{
  Node *temp = start;
  std::cout << "Queue Contents: ";
  while (temp != NULL) {
    std::cout << temp->data << " | ";
    temp = temp->next;
  }
  std::cout << std::endl;
}

/** makeEmpty
 * @brief Private member to empty this QueueList object, deletes all Nodes in the queue
 *        Does not print any output. Avoids destructors printing to cout
 * 
 * @param head The head of the queue to be deleted
 * 
 */
void QueueList::makeEmpty(Node *&head)
{
  Node *nextNode, *temp;

  if (head == NULL) return;
  else {
    nextNode = head->next;
    delete head;
    head = NULL;
    tail = NULL;
    while(nextNode != NULL) {
      temp = nextNode;
      nextNode = nextNode->next;
      delete temp;
      temp = NULL;
    }

  }
}
