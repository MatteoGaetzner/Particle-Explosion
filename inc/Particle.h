#ifndef PARTICLE_H_
#define PARTICLE_H_

#include <stdlib.h>
#include <math.h>

#define RANDOM_0_TO_1 ((2.0 * rand())/RAND_MAX) - 1
#define SPEED_CONSTANT 0.0006

namespace matteo {

  class Particle {
    private:
      // math symbol: r
      /* float m_speed = pow((SPEED_CONSTANT * rand())/RAND_MAX, 2); */
      float m_speed = 0.0004 * pow((rand())/(float) RAND_MAX, 2);
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


void polarToCartesian(const float& speed, const float& direction, float& x, float& y);
void updateDirection(const float &x, const float &y, float& direction);
void updatePositionFixDirection(float& x, float& y, float& dx, float& dy);
void updatePosition(float& x, float& y, const float& dx, const float& dy);

#endif /* ifndef PARTICLE_H_ */
