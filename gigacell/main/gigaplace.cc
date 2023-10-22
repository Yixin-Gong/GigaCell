//
// Created by eric on 23-9-15.
//

#include "gigaplace.h"

float gigaplace::GigaPlace::computeDeltaC(float &new_cost, float &old_cost) {
  return new_cost - old_cost;
}

bool gigaplace::GigaPlace::accept(int &delta_c, float &T) {
  float prob;
  float r;
  prob = std::exp((float) (-delta_c) / (float) T);

  r = static_cast <float> (random()) / static_cast <float> (RAND_MAX);
  if (r < std::min(prob, (float) 1.0))
    return true;
  else
    return false;
}
void gigaplace::GigaPlace::SAPlace() {

}
