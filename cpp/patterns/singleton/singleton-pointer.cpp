
#include "singleton-pointer.hpp"

// Initialize pointer to instance to null; Allocate on first call to getInstance
ClassicSingleton* ClassicSingleton::instance = nullptr;

ClassicSingleton* ClassicSingleton::getInstance(){
  // If the instance is null, return a new one; Otherwise return instance
  if(instance == nullptr) instance = new ClassicSingleton;
  return instance;
}
