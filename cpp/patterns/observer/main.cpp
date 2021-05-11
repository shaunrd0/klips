
#include <iostream>

#include "observer.hpp"

int main(const int argc, const char * argv[])
{
  Subject subject("Radio");
  Observer *john = new Observer(subject);

  // Test alerting john as the only subscribed observer
  std::cout << "\nAlerting one observer...\n\n";
  subject.SendMessage("Alert 1\n");


  // Attach a new observer
  Observer joe(subject);
  // Alert all subscribed observers
  std::cout << "\nAlerting all observers...\n\n";
  subject.SendMessage("Alert 2\n");

  std::cout << std::endl;
  // Detach joe from the subject
  joe.Detach();
  // Send another alert to john
  std::cout << "Alerting one observer...\n\n";
  subject.SendMessage("Alert 3\n");
  john->Detach();

  // This alert will not be heard by anyone
  std::cout << "\nAlerting no observers...\n\n";
  subject.SendMessage("Alert 4\n");
}
