/*##############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2019 Shaun Reed, all rights reserved               ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
##
*/

#include <lib-sdl-test.h>


/******************************************************************************/
// Shape base class definitions
std::string Shape::PrintInfo() {
  return name + " HxW: " + std::to_string(height) + "x" + std::to_string(width);
};


/******************************************************************************/
// SDL helper function definitions

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
