#include <math.h>
#include <thread>
#include <functional>
#include "../inc/Swarm.h"

const unsigned int PROCESSOR_COUNT = std::thread::hardware_concurrency();

matteo::Swarm::Swarm(): lastTime(0) {
  m_pParticles = new Particle[N_PARTICLES];
}

matteo::Swarm::~Swarm() {
  delete [] m_pParticles;
}

const matteo::Particle* matteo::Swarm::getParticles() {
  return m_pParticles;
}

void matteo::Swarm::updateBatch(const int& elapsed, const int& interval, const bool& colorful, unsigned int batchStartIdx, unsigned int batchEndIdx) {
  for (unsigned int i = batchStartIdx; i < batchEndIdx; ++i) {
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
}

void matteo::Swarm::update(const int& elapsed, const bool& colorful) {
  const int interval = elapsed - lastTime;

  // Create threads array
  std::thread workers[PROCESSOR_COUNT+1];
  int batchsize = N_PARTICLES / PROCESSOR_COUNT;
  int workerIdx = 0;

  // Iterate over all particles in batches
  for (unsigned int batchStartIdx = 0; batchStartIdx < N_PARTICLES; batchStartIdx += batchsize) {

    int batchEndIdx = N_PARTICLES <= batchStartIdx + batchsize
      ? N_PARTICLES
      : batchStartIdx + batchsize;

    workers[workerIdx++] = std::thread(&Swarm::updateBatch, this, elapsed, interval, colorful, batchStartIdx, batchEndIdx);
  }

  for (std::thread& worker : workers) {
    if (worker.joinable()) {
      worker.join();
    }
  }

  lastTime = elapsed;
}
