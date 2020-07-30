/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: An example of a stack implementation using linked lists            ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## stacklist.cpp
*/

#include "stacklist.h"


/******************************************************************************
 * Constructors, Destructors, Operators
 *****************************************************************************/

/** copy constructor
 * @brief Construct a new StackList::StackList object from an existing one
 *        Creates a new deep copy of a given StackList
 *
 * @param rhs StackList object
 */
template <typename T>
StackList<T>::StackList(const StackList<T>& rhs)
{
  Node *cp = rhs.head;
  Node *tempHead;
  // If we are copying from an empty stack, create a new StackList with a NULL head
  if (cp == NULL) head = NULL;
  else {
    // If the stack has data, initialize a new stack with the head data
    head = new Node(cp->data);
    // Keep a temporary head node so we can return to it later
    tempHead = head;
    while (cp->next != NULL) {
      // Until we hit an end, create new nodes with the next node data
      cp = cp->next;
      head->next = new Node(cp->data);
      head = head->next;
    }
    head = tempHead;
  }
}

/** operator=
 * @brief Assign two StackList objects equal using copy constr and class destr
 *        Pass the rhs by value to create local copy, swap its contents
 *        Destructor called on previous StackList data at the end of this scope
 *
 * @param rhs StackList object passed by value
 * @return StackList A deep copy of the rhs StackList object
 */
template <typename T>
StackList<T> StackList<T>::operator=(StackList<T> rhs)
{
  if (this == &rhs) return *this;
  // Swap the pointers, moving the previous head data to the local variable rhs 
  std::swap(head, rhs.head);
  return *this;
}

/** destructor
 * @brief Destroy the StackList::StackList object
 */
template <typename T>
StackList<T>::~StackList()
{
  makeEmpty(head);
}


/******************************************************************************
 * Public Member Functions
 *****************************************************************************/

/** push
 * @brief Push a value to the head of our linked list
 *
 * @param val The value to be inserted
 */
template <typename T>
bool StackList<T>::push(T val)
{
  bool inserted = push(val, head);
  if (inserted)
    std::cout << "[" << val << "] was inserted into the stack\n";
  else std::cout << "[" << val << "] could not be inserted into the stack\n";
  return inserted;
}

/** pop
 * @brief returns the value at the StackList::head
 *
 * @return T The value held at the Node pointed to by StackList::head
 */
template <typename T>
T StackList<T>::pop()
{
  if (!isEmpty())
    std::cout << "[" << pop(head) << "] has been popped from our stack\n";
  else std::cout << "Nothing to pop, our stack is empty...\n";
  // If the stack has data we return it, otherwise we return the smallest possible int (error)
  return (!isEmpty()) ? head->data : T();
}

/** top
 * @brief returns the value at the StackList::head
 *
 * @return T The value held at the Node pointed to by StackList::head
 */
template <typename T>
T StackList<T>::top() const
{
  if (!isEmpty())
    std::cout << "[" << head->data << "] is at the top of our stack\n";
  else std::cout << "Our stack is empty...\n";
  // If the stack has data we return it, otherwise we return the smallest possible int (error)
  return (!isEmpty()) ? head->data : T();
}

/** makeEmpty
 * @brief Empty this StackList object, deleting all associated Nodes
 */
template <typename T>
void StackList<T>::makeEmpty()
{
  Node *nextNode, *temp;

  if (head == NULL) std::cout << "Our stack is empty...\n";
  else {
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
}

/** isEmpty
 * @brief Determine if the StackList is empty
 *
 * @return true If the StackList::head is NULL
 * @return false If the StackList::head contains data
 */
template <typename T>
bool StackList<T>::isEmpty() const
{
  return head == NULL;
}

/** print
 * @brief Output the data held by the StackList object
 *        Calls to the private print()
 */
template <typename T>
void StackList<T>::print() const
{
  if(!isEmpty()) print(head);
  else std::cout << "Nothing to print, our stack is empty...\n";
}


/******************************************************************************
 * Private Member Functions
 *****************************************************************************/

/** push
 * @brief Private member to handle inserting value into the stack
 *
 * @param val Value to be inserted
 * @param head The head of the stack to push the value into
 * @return true If the value was inserted
 * @return false If the value could not be inserted
 */
template <typename T>
bool StackList<T>::push(T val, Node *&head)
{
  Node *newNode = new Node(val);
  // If the stack is not empty, update next pointer to head node
  if (!isEmpty()) newNode->next = head;
  // Always set head to our newNode
  head = newNode;
  return true;
}

/** pop
 * @brief Private member to handle removing the head node from the stack
 *
 * @param head The head node of the stack
 * @return T The last known value held at the head node before removal
 */
template <typename T>
T StackList<T>::pop(Node *&head)
{
  // We already know the stack is not empty from public pop()
  Node *temp = head;
  T data = temp->data;
  head = head->next;
  delete temp;
  return data;
}

/** print
 * @brief Output the contents of a StackList from the given Node to NULL
 *
 * @param start The Node to begin traversing output from
 */
template <typename T>
void StackList<T>::print(Node *start) const
{
  Node *temp = start;
  std::cout << "Stack Contents: ";
  while (temp != NULL) {
    std::cout << temp->data << " | ";
    temp = temp->next;
  }
  std::cout << std::endl;
}

/** makeEmpty
 * @brief Private member to empty this StackList object, deleting all associated Nodes
 *        Does not print any output. Avoids destructors printing to cout
 * 
 * @param head The head of the stack to be deleted
 */
template <typename T>
void StackList<T>::makeEmpty(Node *&head)
{
  Node *nextNode, *temp;

  if (head == NULL) return;
  else {
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
}

template class StackList<TYPE>;
