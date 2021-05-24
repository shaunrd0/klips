/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2019 Shaun Reed, all rights reserved               ##
## Requires SDL: `sudo apt-get install libsdl2-dev`                          ##
## To build: `mkdir build && cd build && cmake .. cmake --build .`           ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## apps/inherited.cpp
*/

#include <lib-sdl-test.h>
#include <iostream>

int main (int argc, char const * argv[]) {
  // Cast cli arguments to void since they are unused in this exe
  (void)argc;
  (void)argv;

  // Ensure SDL is initialized before continuing
  if (SDL_Init(SDL_INIT_EVERYTHING) < 0) exit(2);

  SDL_Window *window;
  SDL_Renderer *renderer;

  if (InitScreen(window, renderer) < 0) {
    std::cout << "Error - Unable to initialize SDL screen\n";
  }

  // Draw a window for 3000ms
  DrawDelay(renderer, 3000);
  // Destroy the window after 3 seconds
  SDL_DestroyWindow(window);
  // Destroy the renderer, since we won't be using it anymore
  SDL_DestroyRenderer(renderer);

  std::cout << "Testing creation of Shape, Rectangle...\n";
  // Create a custom shape, and a default shape
  Shape shape(4,4), dShape;
  // Create a custom rectangle, and a default rectangle
  Rectangle rect(4,8), dRect;
  std::cout << dShape.PrintInfo() << std::endl;
  std::cout << shape.PrintInfo() << std::endl;
  std::cout << dRect.PrintInfo() << std::endl;
  std::cout << rect.PrintInfo() << std::endl;

  return 0;
}
