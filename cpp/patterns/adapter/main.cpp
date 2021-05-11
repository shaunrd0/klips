
#include <iostream>

#include "adapter.hpp"

int main(const int argc, const char * argv[]) {
  const int a = 5;
  const int b = 10;
  std::cout << "A = " << a << "\nB = " << b << std::endl;

  // Testing target implementation
  Add adder;
  std::cout << "Adding a + b: " << adder.doMath(a, b) << std::endl;

  // Testing RandomAddAdapter using RandomNumber as the adaptee
  RandomNumber *adaptee = new RandomNumber(100);
  RandomAddAdapter *adapter = new RandomAddAdapter(adaptee);
  std::cout << "\nAdding a + b + RandomNumber: " << adapter->doMath(a, b)
            << std::endl;
}
