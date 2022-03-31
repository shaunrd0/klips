
#include <iostream>

#include "abstract-factory.hpp"

Part* AbstractFactory::requestPart() {
  // Create a new part
  Part * newPart = makePart();
  // Increment the QTY for part in AbstractFactory::inventory base class
  // + If the item is not in the inventory map, this will also add it first.
  inventory[newPart->getName()]++;
  // Make the requested part
  return newPart;
}

Part* AbstractFactory::requestPart(std::string partName, float price)
{
  Part * newPart = makePart(partName, price);
  inventory[newPart->getName()]++;
  return newPart;
}

void AbstractFactory::showStock() const
{
  for (const auto &item : inventory) {
    if (item.first.empty()) continue; // Don't show an empty item
    std::cout << item.first << " QTY in stock: " << item.second << std::endl;
  }
}


/*****************************************************************************/
// Gear

Part* GearFactory::makePart() {
  return new Gear();
}

Part* GearFactory::makePart(std::string name, float price)
{
  return new Gear(name, price);
}


/*****************************************************************************/
// Spring

Part* SpringFactory::makePart() {
  return new Spring();
}

Part *SpringFactory::makePart(std::string name, float price)
{
  return new Spring(name, price);
}
