#include <stdlib.h>
#include <math.h>
#include "../inc/Particle.h"

/* Conversion from polar coordinates to cartesian coordinates, see:
 * https://en.wikipedia.org/wiki/Polar_coordinate_system */
void polarToCartesian(const float& speed, const float& direction, float& x, float& y) {
  x += speed * cos(direction); // x = r * cos(phi)
  y += speed * sin(direction); // y = r * sin(phi)
}

/* Conversion from cartesian coordinates to polar coordinates, see:
 * https://en.wikipedia.org/wiki/Polar_coordinate_system */
void cartesianToPolar(const float &x, const float &y, float& speed, float& direction) {
  speed = sqrt(pow(x, 2) + pow(y, 2));
  direction = atan2(y,x);
}

void matteo::Particle::update() {
  polarToCartesian(m_speed, m_direction, m_x, m_y);
}

void matteo::Particle::update(const int& elapsed) {
  // If elapsed == 0, we set the particles color to white
  if (not elapsed) {
    m_red = 0xFF; m_blue = 0xFF; m_green = 0xFF;
  } else {
    m_red = (int) floor(128 + 128 * sin(0.005 * elapsed * colorprimer));
    m_green = (int) floor(128 + 128 * sin(0.007 * elapsed * colorprimer));
    m_blue = (int) floor(128 + 128 * sin(0.009 * elapsed * colorprimer));
  }

  polarToCartesian(m_speed, m_direction, m_x, m_y);

  if (m_x > 1 || m_x < -1) {
    cartesianToPolar(m_x, m_y, m_speed, m_direction);
  }
}

