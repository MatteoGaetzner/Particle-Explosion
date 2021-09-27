#ifndef SWARM_H_
#define SWARM_H_ value

#include <memory>

#include "Particle.h"

namespace matteo {

  class Swarm {
    private:
      Particle* m_pParticles;
      unsigned int lastTime;

    public:
      Swarm();
      ~Swarm();
      const static unsigned int N_PARTICLES = 5000 / 2;
      const Particle* getParticles();
      void update(const int& elapsed, const bool& colorful);
  };

}
#endif /* ifndef SWARM_H_ */
