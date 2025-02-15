//
// Created by zy on 23-9-25.
//

#include "netlength.h"
#include <limits>

float gigaplace::NetLength::calNetLength() {

  float total_length = 0;

  for (auto &kNet : pl_db_.nets()) {

    if (kNet.first == "VDD" || kNet.first == "VSS")
      continue;

    float x_max = -std::numeric_limits<float>::max();
    float x_min = std::numeric_limits<float>::max();

    for (auto &kMos : kNet.second) {
      float x = 0;
      if (kMos.electrode_name == "left") {
        x = pl_db_.mos_list().at(kMos.idx).getLeftLoc();
      } else if (kMos.electrode_name == "gate") {
        x = pl_db_.mos_list().at(kMos.idx).getGateLoc();
      } else {
        x = pl_db_.mos_list().at(kMos.idx).getRightLoc();
      }

      x_max = std::max(x_max, x);
      x_min = std::min(x_min, x);

    }
    auto length = x_max - x_min;
    total_length += length;
  }

  return
      total_length;
}
