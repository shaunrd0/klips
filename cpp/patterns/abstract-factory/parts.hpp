
#ifndef PARTS_HPP
#define PARTS_HPP

#include <string>

class Part {
public:
  std::string getName() const { return partName;}
  float getPrice() const { return partPrice;}

protected:
  std::string partName; // The name of the part
  float partPrice; // The partPrice of the part
};


/*****************************************************************************/
// Gear

class Gear : public Part {
public:
  Gear(std::string name="Gear", float price = 1.0f);
};


/*****************************************************************************/
// Spring

class Spring : public Part {
public:
  Spring(std::string name = "Spring", float price = 2.0f);
};

#endif // PARTS_HPP
