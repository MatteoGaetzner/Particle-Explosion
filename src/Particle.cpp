#include <stdlib.h>
#include <math.h>
#include "../inc/Particle.h"

void matteo::Particle::update() {
  m_x += m_xspeed;
  m_y += m_yspeed;

  if (m_x < -1 || m_x > 1) {
    m_xspeed *= -1;
  }
  if (m_y < -1 || m_y > 1) {
    m_yspeed *= -1;
  }
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

  m_x += m_xspeed;
  m_y += m_yspeed;

  if (m_x < -1 || m_x > 1) {
    m_xspeed *= -1;
  }
  if (m_y < -1 || m_y > 1) {
    m_yspeed *= -1;
  }
}

