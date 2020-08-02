/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: An example of a queue implementation using linked lists            ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## queuelist.h
*/

#ifndef QUEUELIST_H
#define QUEUELIST_H

#include <iostream>


#define TYPE std::string

template <typename T>
class QueueList {
  public:
    QueueList() : head(NULL), tail(NULL){};
    QueueList(const QueueList<T>& rhs);
    QueueList operator=(QueueList<T> rhs);
    ~QueueList();
    bool enqueue(T val);
    T dequeue();
    T next() const;
    bool isEmpty() const;
    void print() const;
    void makeEmpty();

  private:
    struct Node {
      TYPE data;
      Node *next;
      Node(): data(), next(NULL) {};
      Node(TYPE val): data(val), next(NULL) {};
    };
    Node *head, *tail;
    bool enqueue(T val, Node *&head);
    T dequeue(Node *&tail);
    void print(Node *start) const;
    void makeEmpty(Node *&head);
    
};


/******************************************************************************
 * Constructors, Destructors, Operators
 *****************************************************************************/

/** copy constructor
 * @brief Construct a new QueueList::QueueList object from an existing one
 *        Creates a new deep copy of a given QueueList
 *
 * @param rhs QueueList object
 */
template<typename T>
QueueList<T>::QueueList(const QueueList<T>& rhs)
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
template<typename T>
QueueList<T> QueueList<T>::operator=(QueueList<T> rhs)
{
  if (this == &rhs) return *this;
  // Swap the pointers, moving the previous head data to the local variable rhs
  std::swap(head, rhs.head);
  return *this;
}

/** destructor
 * @brief Destroy the QueueList::QueueList object
 */
template<typename T>
QueueList<T>::~QueueList()
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
 * @return true If the value was inserted in the queue
 * @return false If the value could not be queued
 */
template<typename T>
bool QueueList<T>::enqueue(T val)
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
 * @return T The value held at the Node pointed to by QueueList::head
 */
template<typename T>
T QueueList<T>::dequeue()
{
  if (!isEmpty())
    std::cout << "[" << dequeue(head) << "] has been removed from our queue\n";
  else std::cout << "Nothing to dequeue, our queue is empty...\n";
  // If the queue has data we return it, otherwise we return the smallest possible int (error)
  return (!isEmpty()) ? head->data : T();
}

/** next
 * @brief returns the value at the QueueList::head
 *
 * @return T The value held at the Node pointed to by QueueList::head
 */
template<typename T>
T QueueList<T>::next() const
{
  if (!isEmpty())
    std::cout << "[" << head->data << "] is next in queue\n";
  else std::cout << "Our queue is empty...\n";
  // If the queue has data we return it, otherwise we return the smallest possible int (error)
  return (!isEmpty()) ? head->data : T();
}

/** isEmpty
 * @brief Determine if the QueueList is empty
 *
 * @return true If the QueueList::head is NULL
 * @return false If the QueueList::head contains data
 */
template<typename T>
bool QueueList<T>::isEmpty() const
{
  return head == NULL;
}

/** print
 * @brief Output the data held by the QueueList object
 *        Calls to the private print()
 */
template<typename T>
void QueueList<T>::print() const
{
  if(!isEmpty()) print(head);
  else std::cout << "Nothing to print, our queue is empty...\n";
}

/** makeEmpty
 * @brief Empty this QueueList object, deleting all associated Nodes
 */
template<typename T>
void QueueList<T>::makeEmpty()
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
template<typename T>
bool QueueList<T>::enqueue(T val, Node *&tail)
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
 * @return T The value held at the node removed
 */
template<typename T>
T QueueList<T>::dequeue(Node *&head)
{
  // We already know the queue is not empty from public dequeue()
  Node *temp = head;
  // Store the data at the front of the queue before we delete the node
  T data = head->data;

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
template<typename T>
void QueueList<T>::print(Node *start) const
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
template<typename T>
void QueueList<T>::makeEmpty(Node *&head)
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


#endif
