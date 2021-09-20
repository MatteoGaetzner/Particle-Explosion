#include <SDL2/SDL.h>
#include <iostream>
#include <math.h>

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
    int elapsed = SDL_GetTicks();
    unsigned char red = (int) floor(128 + 128 * sin(0.0005 * elapsed));
    unsigned char green = (int) floor(128 + 128 * cos(0.0007 * elapsed));
    unsigned char blue = (int) floor(128 + 128 * cos(0.0009 * elapsed));
    for (int y = 0; y < matteo::Screen::SCREEN_HEIGHT; ++y) {
      for (int x = 0; x < matteo::Screen::SCREEN_WIDTH; ++x) {
        // Trippy :D
        /* screen.setPixel(x,y, (x*red) % 256, (y * green) % 256, (x * y * blue) % 256); */
        screen.setPixel(x,y, red, green, blue);
      }
    }

    // Draw the screen
    screen.update();

    // Check for messages / events
    quit = not screen.processEvents();
  }

  return 0;
}
