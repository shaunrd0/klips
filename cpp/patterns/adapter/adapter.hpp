
#ifndef ADAPTER_HPP
#define ADAPTER_HPP

#include <random>

// Target implementation to adapt to a new interface
class Add {
public:
  virtual ~Add() = default;

  virtual int doMath(const int &a, const int &b) const { return a + b;}
};

// An adaptee with some useful behavior to adapt to our Add target
class RandomNumber {
public:
  explicit RandomNumber(const int &max) : maxNum(max) { srand(time(nullptr));}

  int getRandom() const { return rand() % maxNum;}

private:
  int maxNum;
};

// An adapter that combines behaviors of Add and RandomNumber
class RandomAddAdapter : public Add {
public:
  explicit RandomAddAdapter(RandomNumber *random_) : random(random_) {}

  int doMath(const int &a, const int &b) const override { return a + b + random->getRandom();}

private:
  RandomNumber *random;
};

#endif // ADAPTER_HPP
