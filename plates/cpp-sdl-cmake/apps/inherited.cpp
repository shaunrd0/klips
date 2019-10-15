/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2019 Shaun Reed, all rights reserved               ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## apps/inherited.cpp
*/

#include <src/lib-inherit.h>
#include <iostream>
//#include <string>

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
