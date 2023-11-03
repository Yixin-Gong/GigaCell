//
// Created by zy on 23-10-28.
//

#ifndef GIGACELL_GIGACELL_CONSTRAINTS_PINDENSITY_H_
#define GIGACELL_GIGACELL_CONSTRAINTS_PINDENSITY_H_

#include "placement/place_db.h"
#include <algorithm>
#include <cmath>
#include <limits>
namespace  gigaplace {

class PinDensity{
 public:
  explicit  PinDensity(PlaceDB &pl_db,float &width) : pl_db_(pl_db),width_(width){}

  float &width(){return width_;}

  static float calStandardDeviation(const std::vector<float> &pin_spacing);
  float getPinScore();
  static bool isPinNet(const std::string &netName,const std::vector<std::string> &v_pin_name);



 private:
  PlaceDB &pl_db_;
  float &width_;
};
}
#endif //GIGACELL_GIGACELL_CONSTRAINTS_PINDENSITY_H_
