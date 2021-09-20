#include "Swarm.h"

const matteo::Particle* matteo::Swarm::getParticles() {
  return m_pParticles;
}

matteo::Swarm::Swarm() {
  m_pParticles = new Particle[N_PARTICLES];
}

matteo::Swarm::~Swarm() {
  delete [] m_pParticles;
}
