
#include "singleton.h"

int main(const int argc, const char *argv[])
{
  // Creates a singleton, initializes message in ctor
  Singleton &s = Singleton::getInstance();
  s.showMessage();
  // Update already existing Singleton message, show it
  s.updateMessage("First update\n");
  Singleton::getInstance().showMessage();
  // Update already existing Singleton message, show it
  Singleton::getInstance().updateMessage("Second update\n");
  s.showMessage();
}
