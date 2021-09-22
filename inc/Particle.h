#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <stdlib.h>
#include <math.h>

#define RANDOM_0_TO_1 ((2.0 * rand())/RAND_MAX) - 1
#define SPEED_CONSTANT 0.01

namespace matteo {

  class Particle {
    private:
      float m_speed = (SPEED_CONSTANT * rand())/RAND_MAX; // math symbol: r
      float m_direction = (2.0 * M_PI * rand()) / RAND_MAX; // math symbol: phi

    public:
      float m_x = 0;
      float m_y = 0;
      unsigned char m_red = 0xFF;
      unsigned char m_green = 0xFF;
      unsigned char m_blue = 0xFF;
      float colorprimer = 1;

      Particle() {};
      void update();
      void update(const int& colorseed);
  };

}
#endif /* ifndef PARTICLE_H_ */
