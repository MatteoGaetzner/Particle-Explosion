#include <stdlib.h>
#include <math.h>
#include "../inc/Particle.h"

/* Conversion from polar coordinates to cartesian coordinates, see:
 * https://en.wikipedia.org/wiki/Polar_coordinate_system */
void polarToCartesian(const float& speed, const float& direction, float& x, float& y) {
  x = speed * cos(direction); // x = r * cos(phi)
  y = speed * sin(direction); // y = r * sin(phi)
}

/* Updates the direction, based on given cartesian coordinates
 * https://en.wikipedia.org/wiki/Polar_coordinate_system */
void updateDirection(const float &x, const float &y, float& direction) {
  direction = atan2(y,x);
}

/* Updates the position of the particle,
 * and changes the direction in which the particle is moving if it hits a window border */
void updatePositionReflect(float& x, float& y, float& dx, float& dy) {
  if (x > 1) {
    x = 1;
    dx *= -1;
  } else if (x < -1) {
    x = -1;
    dx *= -1;
  } else if (y > 1) {
    y = 1;
    dy *= -1;
  } else if (y < -1) {
    y = -1;
    dy *= -1;
  } else {
    updatePosition(x, y, dx, dy);
  }
}

void updatePosition(float& x, float& y, const float& dx, const float& dy) {
  x += dx;
  y += dy;
}

void updatePositionReinit(float& x, float& y, const float& dx, const float& dy) {
  if (x >= 1 or x <= -1 or y >= 1 or y <= -1) {
    x = 0;
    y = 0;
  } else {
    updatePosition(x, y, dx, dy);
  }
}

void matteo::Particle::update(const int& elapsed, const int& interval, const bool& colorful) {

  // Make particles curl
  m_direction += interval * 0.0003;

  // If we colorful == true, we set the particles color to white
  if (not colorful) {
    m_red = 0xFF; m_blue = 0xFF; m_green = 0xFF;
  } else {
    m_red = (int) floor(128 + 128 * sin(0.0005 * elapsed * colorprimer));
    m_green = (int) floor(128 + 128 * sin(0.0007 * elapsed * colorprimer));
    m_blue = (int) floor(128 + 128 * sin(0.0009 * elapsed * colorprimer));
  }

  // m_speed*interval: ensures consistent speed of particles across devices
  float dx, dy;
  polarToCartesian(m_speed * interval, m_direction, dx, dy);

  // update particle position, and (optionally) reflect or reinitialize it, if the particle hits a border (dx, dy)
  /* updatePositionReflect(m_x, m_y, dx, dy); */
  updatePositionReinit(m_x, m_y, dx, dy);
  /* updatePosition(m_x, m_y, dx, dy); */

  // update direction in which the particle is moving
  updateDirection(dx, dy, m_direction);
}

