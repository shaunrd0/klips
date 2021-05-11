
#ifndef ABSTRACTION_HPP
#define ABSTRACTION_HPP

#include <iostream>
#include <utility>

#include "implementation.hpp"

// Abstract calculator that can only perform one operation
class Calculator {
public:
  explicit Calculator(Implementation *method_) : method(method_) {}

  virtual std::string getName() const = 0;
  virtual int doMath(const int &a, const int &b) const = 0;

protected:
  Implementation *method;
};

// Simple calculator that can only perform one operation
class SimpleCalculator : public Calculator {
public:
  explicit SimpleCalculator(Implementation *method_) : Calculator(method_) {}

  inline std::string getName() const override { return method->getName();}
  inline int doMath(const int &a, const int &b) const override { return method->math(a, b);}
};

// Verbose calculator that prints information on method performed and result
class VerboseCalculator : public Calculator {
public:
  explicit VerboseCalculator(Implementation *method_) : Calculator(method_) {}

  inline std::string getName() const override { return method->getName();}
  int doMath(const int &a, const int &b) const override;
};

#endif // ABSTRACTION_HPP
