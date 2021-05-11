
#ifndef PROTOTYPE_HPP
#define PROTOTYPE_HPP

#include <string>
#include <utility>
#include <unordered_map>
#include <iostream>

#include "prototype.hpp"

enum Types {
  GEAR = 0,
  SPRING,
};

class Prototype {
public:
  Prototype(std::string name_, float price_) :
      name(std::move(name_)), price(price_) {}
  virtual ~Prototype() = default;

  virtual Prototype *clone() const = 0;
  virtual void setField(std::string field_) { field = std::move(field_);}

  void show() const { std::cout << name << " with price: " << price << std::endl;}

protected:
  std::string name;
  float price;
  std::string field;
};

class Gear : public Prototype {
public:
  explicit Gear(const float &price_) : Prototype("Gear", price_) {}

  Prototype *clone() const override { return new Gear(*this);}
};

class Spring : public Prototype {
public:
  explicit Spring(const float &price_) : Prototype("Spring", price_) {}

  Prototype *clone() const override { return new Spring(*this);}
};

class PrototypeFactory {
public:
  PrototypeFactory();

  Prototype *createPrototype(Types type) { return prototypes[type]->clone();}

private:
  std::unordered_map<Types, Prototype *> prototypes;
};

#endif // PROTOTYPE_HPP
