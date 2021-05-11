
#include <array>
#include <iostream>
#include <vector>

#include "abstraction.hpp"
#include "implementation.hpp"

int main(const int argc, const char * argv[]) {
  Add *add = new Add;
  SimpleCalculator adder(add);
  const int a = 5;
  const int b = 10;
  std::cout << "A = " << a << "\nB = " << b << std::endl;

  std::cout << "\nTesting " << adder.getName() << ".doMath(a, b)...\n";
  std::cout << "Result: " << adder.doMath(a, b);

  auto *sub = new Subtract;
  SimpleCalculator subtractor(sub);
  std::cout << "\n\nTesting " << subtractor.getName() << ".doMath(a, b)...\n";
  std::cout << "Result: " << subtractor.doMath(a, b);

  // Testing extension of abstraction
  std::cout << "\n\nTesting VerboseCalculator.doMath(a, b)...\n";
  VerboseCalculator verboseCalculator(add);
  verboseCalculator.doMath(a, b);
}
