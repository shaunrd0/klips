
#include "singleton.hpp"
#include "singleton-pointer.hpp"

int main(const int argc, const char *argv[])
{

  /****************************************************************************/
  // Meyers Singleton - static getInstance

  // Creates a singleton, initializes message in ctor
  Singleton &s = Singleton::getInstance();
  s.showMessage();
  // Update already existing Singleton message, show it
  s.updateMessage("First update\n");
  Singleton::getInstance().showMessage();
  // Update already existing Singleton message, show it
  Singleton::getInstance().updateMessage("Second update\n");
  s.showMessage();

  /****************************************************************************/
  // Classic Singleton - pointer getInstance


  std::cout << "\n##### ClassicSingleton #####\n\n";

  // Creates a classic singleton, initializes message in ctor
  ClassicSingleton *classicSingleton = ClassicSingleton::getInstance();
  classicSingleton->showMessage();
  // Update already existing ClassicSingleton message, show it
  classicSingleton->updateMessage("First update\n");
  ClassicSingleton::getInstance()->showMessage();
  // Update already existing ClassicSingleton message, show it
  ClassicSingleton::getInstance()->updateMessage("Second update\n");
  classicSingleton->showMessage();
}
