
#include <iostream>

#include "state.hpp"

int main(const int argc, const char * argv[]) {
  Car * testCar = new Car;
  testCar->report();

  // Test transition from Stopped->Running
  testCar->Start();
  testCar->report();

  // Test transition from Running->Stopped
  testCar->Stop();
  testCar->report();

  // Test transition from Stopped->Broken
  testCar->Smash();
  testCar->report();

  std::cout << "\nTesting burning state...\n";

  Car *newCar = new Car;
  newCar->report();

  // Test transition from Stopped->Running->Burning
  newCar->Start();
  newCar->Smash();
  newCar->report();
}
