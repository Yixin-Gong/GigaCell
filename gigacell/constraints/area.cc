//
// Created by eric on 23-9-15.
//

#include "area.h"
#include <limits>
float gigaplace::Area::calWidth() {
//  float x_max = -std::numeric_limits<float>::max();
//  for (Mos &nmos : pl_db_.nmos_list()) {
//    x_max = std::max(x_max, nmos.getGateLoc());
//  }
//
//  for (Mos &pmos : pl_db_.pmos_list()) {
//    x_max = std::max(x_max, pmos.getGateLoc());
//  }
//  return x_max + 1;
//
    float x_max = -std::numeric_limits<float>::max();
    for(Mos &mos : pl_db_.mos_list()){
      x_max = std::max(x_max ,mos.getGateLoc());
    }
    return x_max + 1;
}