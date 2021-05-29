/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2019 Shaun Reed, all rights reserved               ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## src/lib-inherit.h
*/

#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <utility>
#include <vector>


class Shape {
public:
  // Provide ctor to set name of derived shape
  Shape(double w, double h, std::string name_) :
      width(w), height(h), name(std::move(name_)) {}
  Shape(double w, double h) : width(w), height(h) {}
  Shape() : width(2), height(2) {}
  virtual ~Shape() = default;

  // All derived inherit ability to show name
  virtual std::string PrintInfo();

  private:
    double width, height;
    const std::string name = "Shape";
};


/******************************************************************************/
// Rectangle derived Shape

class Rectangle: public Shape {
  public:
    Rectangle(double w, double h) : Shape(w, h, "Rectangle") {}
    Rectangle() : Shape(4, 2, "Rectangle") {}
    ~Rectangle() override = default;
};


/******************************************************************************/
// SDL helper functions

int InitScreen(SDL_Window* &window, SDL_Renderer* &renderer);

void DrawDelay(SDL_Renderer* renderer, int delay);
