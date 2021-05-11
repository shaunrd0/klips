
#ifndef SINGLETON_POINTER_HPP
#define SINGLETON_POINTER_HPP

#include <iostream>
#include <string>

class ClassicSingleton{
public:
  // returns pointer to single getInstance
  static ClassicSingleton* getInstance();

  // example functions manipulating singleton object
  inline void showMessage() const { std::cout << message;}
  void updateMessage(const std::string &m) { message=m;}

private:
  // Do not allow construction of this object; Use getInstance() instead
  ClassicSingleton(){ message = "New ClassicSingleton\n";}
  // Do not allow copying of this object
  ClassicSingleton(const ClassicSingleton&){}
  ClassicSingleton& operator=(const ClassicSingleton&){}

  // Static pointer to instance of this singleton
  static ClassicSingleton* instance;
  std::string message;
};

#endif // SINGLETON_POINTER_HPP
