
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
  Singleton() { message = "New singleton\n";}
  Singleton(const Singleton &) {}
  Singleton &operator=(const Singleton &) {}
};

#endif // SINGLETON_H
