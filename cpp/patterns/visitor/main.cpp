
#include <iostream>

#include "visitor.hpp"

int main(const int argc, const char * argv[])
{
  Gear *newGear = new Gear(1.5f, 1.0f);
  PartVisitor *newVisitor = new PartVisitor;
  // Test visiting the Gear concrete component with PartVisitor
  newGear->accept(newVisitor);

  // Testing a Spring concrete component on the same visitor
  auto *newSpring = new Spring(2.5f, 5.0f);
  newSpring->accept(newVisitor);
}
