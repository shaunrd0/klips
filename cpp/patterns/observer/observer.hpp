
#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include <string>
#include <list>
#include <iostream>

#include "observer.hpp"

class Observer;

class Subject {
public:
  Subject(std::string name_) : name(name_) {}
  virtual ~Subject() { std::cout << name << " subject destroyed\n";}

  void Attach(Observer * o) { observerList.push_back(o);}
  void Detach(Observer * o) { observerList.remove(o);}
  void Notify();

  void SendMessage(std::string message_);
  inline std::string getName() const { return name;}

private:
  std::list<Observer *> observerList;
  std::string message, name;
};


/******************************************************************************/
// Observer

class Observer {
public:
  Observer(Subject &s);

  void Update(std::string &message);
  void Detach();

private:
  Subject &subject;
  int number;
  static int totalObservers;
};

#endif // OBSERVER_HPP
