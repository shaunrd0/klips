
#ifndef SINGLETON_H
#define SINGLETON_H

#include <iostream>
#include <string>

class Singleton {
public:
  static Singleton &getInstance();
  ~Singleton();

  inline void showMessage() const { std::cout << message;}
  inline void updateMessage(const std::string &m) { message = m;}

private:
  std::string message;

  // Don't allow copying of this class
  // Ignore -Wreturn-type warnings; It's intentional for this pattern
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wreturn-type"
  Singleton() { message = "New singleton\n";}
  Singleton(const Singleton &) {}
  Singleton &operator=(const Singleton &) {}
  // Unmatched pop reverts GCC to commandline options
#pragma GCC diagnostic pop
#pragma GCC diagnostic pop
};

#endif // SINGLETON_H
