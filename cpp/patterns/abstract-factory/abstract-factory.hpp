
#ifndef FACTORY_HPP
#define FACTORY_HPP

#include <array>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "parts.hpp"

class AbstractFactory {
public:
  AbstractFactory(std::string name_): name(std::move(name_)) {}
  virtual ~AbstractFactory() = default;

  Part* requestPart();
  Part* requestPart(std::string partName, float price);
  void showStock() const;
  std::string getName() const { return name;}

protected:
  virtual Part* makePart() = 0;
  virtual Part* makePart(std::string name, float price) = 0;

private:
  std::string name;
  std::unordered_map<std::string, int> inventory;
};


/*****************************************************************************/
// Gear Concrete Factory

class GearFactory : public AbstractFactory {
public:
  explicit GearFactory(std::string name_="GearFactory") :
      AbstractFactory(std::move(name_)) {}

protected:
  Part* makePart() override;
  Part* makePart(std::string name, float price);
};


/*****************************************************************************/
// Spring Concrete Factory

class SpringFactory : public AbstractFactory {
public:
  explicit SpringFactory (std::string name_="SpringFactory"):
      AbstractFactory(std::move(name_)) {}

protected:
  Part* makePart() override;
  Part* makePart(std::string name, float price);
};

#endif // FACTORY_HPP
