
#include "observer.hpp"

void Subject::Notify()
{
  for (const auto &o : observerList) { o->Update(message);}
}

void Subject::SendMessage(std::string message_)
{
  message = message_;
  Notify();
}


/******************************************************************************/
// Observer

int Observer::totalObservers = 0;

Observer::Observer(Subject &s) : subject(s) {
  std::cout << "Observer " << ++totalObservers << " is subscribed to "
            << s.getName() << "\n";
  s.Attach(this);
  number = totalObservers;
}

void Observer::Update(std::string &message)
{
  std::cout << "Observer " << number << " has message from "
            << subject.getName() << ": " << message;
}

void Observer::Detach()
{
  std::cout << "Observer " << number << " has detached from "
            << subject.getName() << std::endl;
  subject.Detach(this);
}
