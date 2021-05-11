
#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <array>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "parts.hpp"

// Gear Concrete Factory
class GearFactory {
public:
  explicit GearFactory(std::string name_="GearFactory") :
      name(std::move(name_)) {}

  Part* requestPart();
  Part* requestPart(std::string partName, float price);
  void showStock() const;
  std::string getName() const { return name;}

protected:
  Part* makePart();
  Part* makePart(std::string name, float price);

private:
  std::string name;
  std::unordered_map<std::string, int> inventory;
};

#endif // FACTORY_HPP
