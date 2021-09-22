#include <math.h>
#include "../inc/Swarm.h"

matteo::Swarm::Swarm() {
  m_pParticles = new Particle[N_PARTICLES];
}

matteo::Swarm::~Swarm() {
  delete [] m_pParticles;
}

const matteo::Particle* matteo::Swarm::getParticles() {
  return m_pParticles;
}

void matteo::Swarm::update() {
  for (unsigned int i = 0; i < Swarm::N_PARTICLES; ++i) {
    // update its position without changing its color
    m_pParticles[i].update();
  }
}

void matteo::Swarm::update(const int& colorseed) {
  for (unsigned int i = 0; i < Swarm::N_PARTICLES; ++i) {
    // if the particles color is not primed, we prime it
    if (m_pParticles[i].colorprimer == 1) {
      m_pParticles[i].colorprimer = ((2.0 * rand())/RAND_MAX - 1) * M_PI / 2;
    }
    // if colorseed == 0, we set its color to white
    m_pParticles[i].update(colorseed);
  }
}
