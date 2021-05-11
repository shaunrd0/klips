
#include "abstraction.hpp"

int VerboseCalculator::doMath(const int &a, const int &b) const
{
  int result = method->math(a, b);
  std::cout << "Performing " << method->getName() << " on input: a = " << a
            << ", b = " << b << std::endl << "Result: " << result << std::endl;
  return result;
}
