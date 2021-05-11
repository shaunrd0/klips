
#include <iostream>

#include "prototype.hpp"

int main(const int argc, const char * argv[]) {
  // Create a new prototype factory
  auto *factory = new PrototypeFactory;

  // Create a gear by cloning from factory prototypes
  auto *gear = factory->createPrototype(Types::GEAR);
  gear->show();

  // Create a spring by cloning from factory prototypes
  auto *spring = factory->createPrototype(Types::SPRING);
  spring->show();

  // Create a spring by cloning from an existing spring
  auto *otherSpring = spring->clone();
  otherSpring->show();
}
