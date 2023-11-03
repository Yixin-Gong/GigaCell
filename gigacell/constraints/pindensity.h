//
// Created by zy on 23-10-28.
//

#ifndef GIGACELL_GIGACELL_CONSTRAINTS_PINDENSITY_H_
#define GIGACELL_GIGACELL_CONSTRAINTS_PINDENSITY_H_

#include "placement/place_db.h"
#include <algorithm>
#include <cmath>
#include <limits>
#include "area.h"
namespace gigaplace {

class PinDensity {
 public:
  explicit PinDensity(PlaceDB &pl_db) : pl_db_(pl_db) {}

  static float calStandardDeviation(const std::vector<float> &pin_spacing);
  static bool isPinNet(const std::string &netName, const std::vector<std::string> &v_pin_name);
  float getPinAccess();
 private:
  PlaceDB &pl_db_;

};
}
#endif //GIGACELL_GIGACELL_CONSTRAINTS_PINDENSITY_H_
