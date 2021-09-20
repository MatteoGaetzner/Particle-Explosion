#include <stdlib.h>
#include <iostream>
#include "Particle.h"

matteo::Particle::Particle() {
  m_x = ((2.0 * rand())/RAND_MAX) - 1;
  m_y = ((2.0* rand())/RAND_MAX) - 1;
}
