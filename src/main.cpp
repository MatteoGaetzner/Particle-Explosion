#include <SDL2/SDL.h>
#include <iostream>

#include "Screen.h"

int main()
{

  matteo::Screen screen;

  if (not screen.init()) {
    std::cout << "Error initializing SDL." << std::endl;
  }

  bool quit = false;

  while(not quit) {
    // Update particles

    // Draw particles
    for (int y = 0; y < matteo::Screen::SCREEN_HEIGHT; ++y) {
      for (int x = 0; x < matteo::Screen::SCREEN_WIDTH; ++x) {
        screen.setPixel(x,y,x % 256, y % 256, (x - y + 2 * x * y) % 256);
      }
    }

    // Draw the screen
    screen.update();

    // Check for messages / events
    quit = not screen.processEvents();
  }

  return 0;
}
