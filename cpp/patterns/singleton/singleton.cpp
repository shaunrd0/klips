
#include "singleton.hpp"

Singleton::~Singleton()
{
  // Delete any allocated data, close any opened files, etc..
}

Singleton &Singleton::getInstance()
{
  // Construct a new singleton if it doesnt exist, return it
  // + If a static Singleton exists already, just return it
  static Singleton l;
  return l;
}
