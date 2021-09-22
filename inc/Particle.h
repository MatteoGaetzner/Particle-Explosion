#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <stdlib.h>

namespace matteo {

  class Particle {
    private:
      static float random_0_to_1() { return ((2.0 * rand())/RAND_MAX) - 1; }
      float m_xspeed = 0.001 * random_0_to_1();
      float m_yspeed = 0.001 * random_0_to_1();

    public:
      float m_x = random_0_to_1();
      float m_y = random_0_to_1();
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
