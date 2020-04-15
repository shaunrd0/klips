#include "linkedlist.h"

/******************************************************************************
 * Constructors, Destructors, Operators
 *****************************************************************************/ 

/**
 * @brief Construct a new SingleList::SingleList object from an existing one
 * 
 * @param rhs SingleList object
 */
SingleList::SingleList(const SingleList& rhs)
{
  head = rhs.head;
}

/**
 * @brief Copy the rhs SingleList::SingleList into the lhs of an assignemnt
 * 
 * @param rhs SingleList object 
 * @return SingleList& The copied rhs SingleList to the lhs of the assignment
 */
SingleList& SingleList::operator=(const SingleList& rhs)
{
  makeEmpty();
  head = rhs.head;
  return *this;
}

/**
 * @brief Destroy the SingleList::SingleList object
 */
SingleList::~SingleList()
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
bool SingleList::insert(int val)
{
  Node *newNode = new Node(val);
  if (isEmpty())
    head = newNode; 
  else {
    newNode->next = head;
    head = newNode;
  }
  return true;
}

/** insert at
 * @brief Inserts a value in the place of a given key
 *        Key Node found is moved to the newNode->next positon
 * 
 * @param key The value to search for to determine insert location
 * @param val The value to be inserted into the list
 */
bool SingleList::insert(int val, int key)
{
  Node *newNode = new Node(val);
  if (isEmpty() || head->data == key) return insert(val);

  Node *result = findPrevious(key, head);
  if (result == NULL) return false;
  else {
    newNode->next = result->next;
    result->next = newNode;
    return true;
  }
}

/** makeEmpty
 * @brief Empty this SingleList object, deleting all associated Nodes
 */
void SingleList::makeEmpty()
{
  Node *temp;
  while(head != NULL) {
    temp = head;
    head = head->next;
    delete temp;
  }
}

/** isEmpty
 * @brief Determine if the SingleList is empty
 * 
 * @return true If the SingleList::head is NULL
 * @return false If the SingleList::head contains data
 */
bool SingleList::isEmpty() const
{
  return head == NULL;
}

/** peek
 * @brief returns the value at the SingleList::head
 * 
 * @return int The value held at the Node pointed to by SingleList::head
 */
int SingleList::peek() const
{
  if (head == NULL) return -1;
  else return head->data;
}

/** print
 * @brief Output the data held by the SingleList object
 *        Calls to the private print()
 */
void SingleList::print() const
{
  print(head);
}

/** find
 * @brief Calls to the private member find() and handles return cases
 * 
 * @param val The value to search for within our SingleList
 * @return true If the value was found in this SingleList
 * @return false If the value was not found in this SingleList
 */
bool SingleList::find(int val) const
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

/** find
 * @brief Find and return a Node which contains the given value
 * 
 * @param val The value to search for within our SingleList
 * @return SingleList::Node* A pointer to the Node containing the search value
 */
SingleList::Node* SingleList::find(int val, Node *start) const
{
  if (start == NULL || start->data == val) return start;

  Node *temp = start;
  while (temp->next != NULL) {
    temp = temp->next;
    if (temp->data == val) break;
  }

  if (temp->data == val) return temp;
  else return NULL;
}

/** findPrevious
 * @brief Find and return the Node before a given value
 * 
 * @param val The value to search for within our SingleList
 * @return SingleList::Node* A pointer to the Node previous to the  given value
 */
SingleList::Node* SingleList::findPrevious(int val, Node *start) const
{
  if (isEmpty()) return NULL;
  else if (start->data == val) return start;

  Node *temp = start;
  while (temp->next != NULL) {
    if (temp->next->data == val) return temp;
    temp = temp->next;
  }

  return NULL;
}

/** print
 * @brief Output the contents of a SingleList from the given Node to NULL
 * 
 * @param start The Node to begin traversing output from
 */
void SingleList::print(Node *start) const
{
  Node *temp = start;
  std::cout << "List Contents: ";
  while (temp != NULL) {
    std::cout << temp->data << " | ";
    temp = temp->next;
  }
  std::cout << std::endl;
}

