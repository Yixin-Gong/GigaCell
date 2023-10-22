//
// Created by eric on 23-9-21.
//

#ifndef GIGACELL_GIGACELL_PLACEMENT_PLACE_OBJ_H_
#define GIGACELL_GIGACELL_PLACEMENT_PLACE_OBJ_H_
#include "constraints/area.h"
#include "constraints/netlength.h"
#include <chrono>
#include <cmath>
#include <random>

namespace gigaplace {
class PlaceObj {
 public:
  explicit PlaceObj(Area &area, NetLength &net_length)
      : area_(area), net_length_(net_length) {}
  float computeCost();

 private:
  Area &area_;
  NetLength &net_length_;
};
}
#endif //GIGACELL_GIGACELL_PLACEMENT_PLACE_OBJ_H_
