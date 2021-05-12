
#ifndef VISITOR_HPP
#define VISITOR_HPP

#include <string>
#include <iostream>
#include <utility>

class PartVisitor;

// Abstract component
class Part {
public:
  Part(std::string name_, const float &price_) :
      name(std::move(name_)), price(price_) {}

  inline std::string getName() const { return name;}
  inline float getPrice() const { return price;}

  virtual void accept(PartVisitor *v) = 0;
private:
  std::string name;
  float price;
};


/******************************************************************************/
// Concrete components
class Gear : public Part  {
public:
  Gear(const float &price_, const float &radius_) :
      Part("Gear", price_), radius(radius_) {}

  void accept(PartVisitor *v) override;
  inline float getRadius() const { return radius;}

private:
  float radius;
};

class Spring : public Part  {
public:
  Spring(const float &price_, const float &elasticity_) :
      Part("Spring", price_), elasticity(elasticity_) {}

  void accept(PartVisitor *v) override;
  inline float getElasticity() const { return elasticity;}

private:
  float elasticity;
};


/******************************************************************************/
// Concrete visitors
class PartVisitor {
public:
  // Handle visiting different components accordingly
  virtual void visit(Gear *g);
  virtual void visit(Spring *g);
};

#endif // VISITOR_HPP
