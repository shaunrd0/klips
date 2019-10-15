/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2019 Shaun Reed, all rights reserved               ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## apps/inherited.cpp
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
    Shape(double w, double h) {
      height = h;
      width = w;
    };
    Shape() {
      height = 2;
      width = 2;
    };
    ~Shape() { /* Shape destructor */};
    virtual const std::string PrintInfo() {
      info = name + " HxW: " + std::to_string(height) + "x" + std::to_string(width);
      return info;
    };
};

class Rectangle: public Shape {
  private:
    double width, height;
    std::string info;

  public:
    Rectangle(double w, double h) {
      height = h;
      width = w;
    };
    Rectangle() {
      height = 2;
      width = 4;
    };
    ~Rectangle() { /* Rectangle destructor */ };

};

int InitScreen(SDL_Window* &window, SDL_Renderer* &renderer) {
  int state = 0;

  // Create window, renderer to draw to screen
  if (SDL_CreateWindowAndRenderer(500, 500, 0, &window, &renderer) < 0) {
    std::cout << "Error - Unable to create SDL screen and renderer objects\n";
    state = -1;
  }
  
	// Set render DrawColor, fill screen with color
  if (SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255) < 0 || SDL_RenderClear(renderer) < 0) {
    std::cout << "Error - Unable to set renderer draw color\n";
    state = -1;
  }

  return state;
}

void DrawDelay(SDL_Renderer* renderer, int delay) {
  // Show what we have rendered
	SDL_RenderPresent(renderer);
  // Wait 3000ms, then continue
	SDL_Delay(delay);

  return;
}

int main (int argc, char const * argv[]) {
  // Cast cli arguments to void since they are unused in this exe
  (void)argc;
  (void)argv;
  
  // Ensure SDL is initialized before continuing
 	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    exit(2);  
  
  SDL_Window *window;
  SDL_Renderer *renderer;

  if (InitScreen(window, renderer) < 0)
    std::cout << "Error - Unable to initialize SDL screen\n";
  
  DrawDelay(renderer, 3000);

  std::cout << "Test\n";
  Shape shape(4,4), dShape;
  Rectangle rect(4,8), dRect;
  std::cout << dShape.PrintInfo() << std::endl;
  std::cout << shape.PrintInfo() << std::endl;
  std::cout << dRect.PrintInfo() << std::endl;
  std::cout << rect.PrintInfo() << std::endl;

  return 0;
}
