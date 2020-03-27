#include <lib-datastruct.h>

// LinkedList

void LinkedList::Append(char val)
{
  Node *temp = new Node(val);
  
  if (isEmpty()) {
    this->tail = this->head = temp;
    // head->next = tail;
    return;
  }
  else {
    tail->next = temp;
    tail = temp;
    return;
  }
}

void LinkedList::Push(char val)
{
  Node *temp = new Node(val);

  if (isEmpty())
  {
    this->head = this->tail = temp;
    return;
  }
  else {
    temp->next = head;
    this->head = temp;
    return;
  }
}

void LinkedList::Remove(char val)
{
  Node *foundNode = new Node;
  
  if (isEmpty()) {
    // if list is empty
    std::cout << "Error: List is empty\n";
    return;
  }
  else if (this->head->data == val) {
    // check the head node, return if found val
    foundNode = this->head;
    std::cout << "[" << foundNode->data << "] has been removed from our list\n";
    this->head = foundNode->next;
    delete foundNode;
    // Does this set head to NULL?
    // this->head = NULL;
    return;
  }

  Node *temp = head;
  while (temp->next->data != val) {
    temp = temp->next;
    if (temp->next == NULL) {
      std::cout << "Value [" << val << "] not found in our list\n";
      return;
    }
  }
  foundNode = temp->next;
  // If we made it our of the loop, we found val at the next node
  temp->next = foundNode->next;
  std::cout << "[" << foundNode->data << "] has been removed from our list\n";
  delete foundNode;
  return;  
}

void LinkedList::Replace(char remove, char replace)
{
  return;
}

Node* LinkedList::Find(char val) const
{
  Node *foundNode(NULL);
  Node *temp = head;
  
  if(isEmpty())  {
    std::cout << "Error: The list is empty\n";
    return foundNode;
  }

  bool found = false;

  while (!found && temp->next != NULL) {
    if(temp->next->data == val) {
      found = true;
      foundNode = temp->next;
      std::cout << "[" << foundNode->data << "] has been found in our list\n";
      // temp->next = foundNode->next;
      // delete foundNode;
    }
    temp = temp->next;
  }
  return foundNode;
}

void LinkedList::Display() const
{
  Node *temp = head;
  while (temp != NULL) {
    std::cout << "[" << temp->data << "] | ";
    temp = temp->next;
  }
  return;
}

bool LinkedList::isEmpty() const
{
  return this->head == NULL;
}

// StackArray

void StackArray::Push(char val)
{
  
  if (top < MAX && !isEmpty()) {
    this->stack[++top].data = val;
  }
  else if (isEmpty()) {
    this->stack[++top].data = val;
  }
  else {
    std::cout << "Error: stack is full!\n";
  }
  return;
}

char StackArray::Pop() 
{
  
  if (!isEmpty()) {
    char temp = this->Top();
    this->top -= 1;
    return temp;
  }
  return '\0';
}

char StackArray::Top() const
{
  return this->stack[top].data;
}

void StackArray::Display() const
{
  if (isEmpty()) {
    std::cout << "Error: Stack is empty\n";
    return;
  }

  int tempTop = this->top;
  while (tempTop >= 0) {
    std::cout << "Value at stack [" << tempTop << "]: " 
      << this->stack[tempTop].data << std::endl;
    tempTop--;
  }
  
  return;
}

bool StackArray::isEmpty() const
{
  return this->top <= EMPTY;
}

