
#include "prototype.hpp"

PrototypeFactory::PrototypeFactory()
{
  prototypes[Types::GEAR] = new Gear(1.5f);
  prototypes[Types::SPRING] = new Spring(2.25f);
}
