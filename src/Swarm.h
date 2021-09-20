#ifndef SWARM_H_
#define SWARM_H_ value

#include <memory>

#include "Particle.h"

namespace matteo {

  class Swarm {
    private:
      Particle* m_pParticles;

    public:
      Swarm();
      ~Swarm();
      const static unsigned int N_PARTICLES = 5000;
      const Particle* getParticles();
  };

}
#endif /* ifndef SWARM_H_ */
