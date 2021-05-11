
#include <iostream>

#include "factory.hpp"

Part* GearFactory::requestPart() {
  // Create a new part
  Part * newPart = makePart();
  // Increment the QTY for part in AbstractFactory::inventory base class
  // + If the item is not in the inventory map, this will also add it first.
  inventory[newPart->getName()]++;
  // Make the requested part
  return newPart;
}

Part* GearFactory::requestPart(std::string partName, float price)
{
  Part * newPart = makePart(partName, price);
  inventory[newPart->getName()]++;
  return newPart;
}

void GearFactory::showStock() const
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
