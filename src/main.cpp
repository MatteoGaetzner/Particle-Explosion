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
    // Check for messages / events
    quit = not screen.processEvents();
  }

  return 0;
}
