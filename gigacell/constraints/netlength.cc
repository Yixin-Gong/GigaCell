//
// Created by zy on 23-9-25.
//

#include "netlength.h"
#include <limits>

float gigaplace::NetLength::netLength() {

  float total_length = 0;

  for (auto &kNet : pl_db_.nets()) {

    if (kNet.first == "VDD" || kNet.first == "VSS")
      continue;

    float x_max = -std::numeric_limits<float>::max();
    float x_min = std::numeric_limits<float>::max();

    for (auto &kMos : kNet.second) {
      float x = 0;

      if (kMos.type == 0) {
        //if( ==pl_db_.nmos_list().at(kMos.idx).getSource())
        if (kMos.electrode_name == "source") {
          x = pl_db_.nmos_list().at(kMos.idx).getSourceLoc();
        } else if (kMos.electrode_name == "gate") {
          x = pl_db_.nmos_list().at(kMos.idx).getGateLoc();
        } else {
          x = pl_db_.nmos_list().at(kMos.idx).getDrainLoc();
        }
      } else {
        if (kMos.electrode_name == "source") {
          x = pl_db_.pmos_list().at(kMos.idx).getSourceLoc();
        } else if (kMos.electrode_name == "gate") {
          x = pl_db_.pmos_list().at(kMos.idx).getGateLoc();
        } else {
          x = pl_db_.pmos_list().at(kMos.idx).getDrainLoc();
        }
      }

      x_max = std::max(x_max, x);
      x_min = std::min(x_min, x);

    }
    auto length = x_max - x_min;
    total_length += length;
  }

  return total_length;
}
