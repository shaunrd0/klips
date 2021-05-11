
#ifndef IMPLEMENTATION_HPP
#define IMPLEMENTATION_HPP

#include <string>

// Base class for abstract implementation
class Implementation {
public:
  explicit Implementation(std::string name_) : name(std::move(name_)) {}
  virtual ~Implementation() = default;

  inline std::string getName() const { return name;}

  virtual int math(const int &a, const int &b) const = 0;

private:
  std::string name;
};

// Concrete Add implementation
class Add : public Implementation {
public:
  explicit Add(std::string name_="Add") :
      Implementation(std::move(name_)) {}

  inline int math(const int &a, const int &b) const override { return a + b;}
};

// Concrete Subtract implementation
class Subtract : public Implementation {
public:
  explicit Subtract(std::string name_="Subtract") :
      Implementation(std::move(name_)) {}
  inline int math(const int &a, const int &b) const override { return a - b;}
};

#endif // IMPLEMENTATION_HPP
