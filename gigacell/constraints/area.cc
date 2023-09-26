//
// Created by eric on 23-9-15.
//

#include "area.h"
#include <limits>
float gigaplace::Area::computeArea() {
  float x_max = -std::numeric_limits<float>::max();
  for (Mos &nmos : place_db_.nmos_list()) {
    x_max = std::max(x_max, nmos.getGateLoc());
  }

  for (Mos &pmos : place_db_.pmos_list()) {
    x_max = std::max(x_max, pmos.getGateLoc());
  }
  return x_max;
}