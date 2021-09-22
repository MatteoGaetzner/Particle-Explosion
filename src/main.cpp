#include <SDL2/SDL.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

#include "../inc/Screen.h"
#include "../inc/Swarm.h"

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
    int elapsed = SDL_GetTicks();
    // Make swarm colorful by setting the colorseed to the elapsed time so far
    swarm.update(elapsed);
    // Draw particles
    for (unsigned int i = 0; i < matteo::Swarm::N_PARTICLES; ++i) {
      matteo::Particle particle = particles[i];

      // particle.m_x ∈ [-1,1] => (particle.m_x + 1) ∈ [0,2] => x ∈ [0, 2*SCREEN_WIDTH/2 = SCREEN_WIDTH]
      unsigned int x = (particle.m_x + 1) * matteo::Screen::SCREEN_WIDTH/2;
      unsigned int y = particle.m_y * matteo::Screen::SCREEN_WIDTH/2 + matteo::Screen::SCREEN_HEIGHT/2;

      screen.setPixel(x, y, particle.m_red, particle.m_green, particle.m_blue);
    }

    // Draw the screen
    screen.update();

    // Check for messages / events
    quit = not screen.processEvents();
  }

  return 0;
}
