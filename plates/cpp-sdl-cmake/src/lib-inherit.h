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
#include <vector>

class Shape {
  private:
    double width, height;
    std::string info;
    const std::string name = "Shape";

  public:
    Shape(double w, double h);
    Shape();
    ~Shape();
    virtual const std::string PrintInfo();
};

class Rectangle: public Shape {
  private:
    double width, height;
    std::string info;

  public:
    Rectangle(double w, double h);
    Rectangle();
    ~Rectangle();

};

int InitScreen(SDL_Window* &window, SDL_Renderer* &renderer);

void DrawDelay(SDL_Renderer* renderer, int delay);
