
#include <array>
#include <cstdlib>
#include <iostream>
#include <vector>

#include "abstract-factory.hpp"

int main(const int argc, const char * argv[]) {
  // Testing GearFactory
  GearFactory gearFactory;
  const int gearsRequired = 5;

  std::cout << "Testing " << gearFactory.getName() <<"...\nMaking 5 Gears...\n";
  for (int i = 0; i < gearsRequired; i++) gearFactory.requestPart();
  std::cout << std::endl << gearFactory.getName() << " inventory:\n";
  gearFactory.showStock();

  // Testing SpringFactory
  SpringFactory springFactory;
  const int springsRequired = 5;
  for (int i = 0; i < springsRequired; i++) springFactory.requestPart();
  std::cout << std::endl << springFactory.getName() << " inventory:\n";
  springFactory.showStock();


  // Making custom gears and springs
  for (int i = 0; i < gearsRequired; i++) gearFactory.requestPart("Big Gear", 2.5f);
  std::cout << std::endl << gearFactory.getName() << " inventory:\n";
  gearFactory.showStock();

  for (int i = 0; i < springsRequired; i++) springFactory.requestPart("Big Spring", 5.0f);
  std::cout << std::endl << springFactory.getName() << " inventory:\n";
  springFactory.showStock();
}
