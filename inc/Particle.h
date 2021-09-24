#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <stdlib.h>
#include <math.h>

#define RANDOM_0_TO_1 ((2.0 * rand())/RAND_MAX) - 1
#define SPEED_CONSTANT 0.001

namespace matteo {

  class Particle {
    private:
      // math symbol: r
      float m_speed = (SPEED_CONSTANT * rand())/RAND_MAX;
      // math symbol: phi
      float m_direction = (2.0 * M_PI * rand()) / RAND_MAX;

    public:
      float m_x = 0;
      float m_y = 0;
      unsigned char m_red = 0xFF;
      unsigned char m_green = 0xFF;
      unsigned char m_blue = 0xFF;
      float colorprimer = 1;

      Particle() {};
      // interval: time that has passed between last update and current update
      // colorful: whether to make that particle colorful
      void update(const int& elapsed, const int& interval, const bool& colorful);
  };

}
#endif /* ifndef PARTICLE_H_ */
