#include <lib-datastruct.h>

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

