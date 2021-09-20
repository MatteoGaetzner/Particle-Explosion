#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

#include "Screen.h"
#include "Swarm.h"

int main()
{
  // Seed random number generator rand()
  srand(time(NULL));

  matteo::Screen screen;

  if (not screen.init()) {
    std::cout << "Error initializing SDL." << std::endl;
  }

  matteo::Swarm swarm;

  const matteo::Particle* const particles = swarm.getParticles();

  bool quit = false;

  while(not quit) {
    // Update particles
    // Draw particles
    int elapsed = SDL_GetTicks();
    unsigned char red = (int) floor(128 + 128 * sin(0.0005 * elapsed));
    unsigned char green = (int) floor(128 + 128 * cos(0.0007 * elapsed));
    unsigned char blue = (int) floor(128 + 128 * cos(0.0009 * elapsed));
    for (unsigned int i = 0; i < matteo::Swarm::N_PARTICLES; ++i) {
      matteo::Particle particle = particles[i];

      // particle.m_x ∈ [-1,1] => (particle.m_x + 1) ∈ [0,2] => x ∈ [0, 2*SCREEN_WIDTH/2 = SCREEN_WIDTH]
      unsigned int x = (particle.m_x + 1) * matteo::Screen::SCREEN_WIDTH/2;
      unsigned int y = (particle.m_y + 1) * matteo::Screen::SCREEN_HEIGHT/2;

      screen.setPixel(x, y, red, green, blue);
    }

    /* for (int y = 0; y < matteo::Screen::SCREEN_HEIGHT; ++y) { */
    /*   for (int x = 0; x < matteo::Screen::SCREEN_WIDTH; ++x) { */
    /*     // Trippy :D */
    /*     /1* screen.setPixel(x,y, (x*red) % 256, (y * green) % 256, (x * y * blue) % 256); *1/ */
    /*     screen.setPixel(x,y, red, green, blue); */
    /*   } */
    /* } */

    // Draw the screen
    screen.update();

    // Check for messages / events
    quit = not screen.processEvents();
  }

  return 0;
}
