#include <math.h>
#include "../inc/Swarm.h"

matteo::Swarm::Swarm(): lastTime(0) {
  m_pParticles = new Particle[N_PARTICLES];
}

matteo::Swarm::~Swarm() {
  delete [] m_pParticles;
}

const matteo::Particle* matteo::Swarm::getParticles() {
  return m_pParticles;
}

void matteo::Swarm::update(const int& elapsed, const bool& colorful) {
  const int interval = elapsed - lastTime;
  for (unsigned int i = 0; i < Swarm::N_PARTICLES; ++i) {
    // if the particles color is not primed, we prime it
    if (m_pParticles[i].colorprimer == 1) {
      // use next line instead of the one after it to make particles have non-uniform colors
      /* m_pParticles[i].colorprimer = ((2.0 * rand())/RAND_MAX - 1) * M_PI / 2; */
      m_pParticles[i].colorprimer = 1;
    }
    // calculate time interval since last update
    // so that particles move with a machine independent speed
    // if colorseed == 0, we set its color to white
    m_pParticles[i].update(elapsed, interval, colorful);
  }
  lastTime = elapsed;
}
