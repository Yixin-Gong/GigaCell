//
// Created by eric on 23-9-15.
//

#ifndef GIGACELL_GIGACELL_MAIN_GIGAPLACE_H_
#define GIGACELL_GIGACELL_MAIN_GIGAPLACE_H_

#include "ops/operator.h"
#include "placement/place_obj.h"
namespace gigaplace {
class GigaPlace {
 public:
  explicit GigaPlace(PlaceDB &pl_db, float &ref_width, float T) : pl_db_(pl_db), ref_width_(ref_width), T_(10000) {};
  void SAPlace(uint16_t pair_num);
  static float computeDeltaC(float &new_cost, float &old_cost);
  static bool accept(float &delta_c, float T);
  static std::pair<uint16_t, uint16_t> generate2Num(uint16_t pair_num);
  float &get_score() { return score_; }
 private:
  PlaceDB &pl_db_;
  float &ref_width_;
  float T_;
  float score_;
};
}
#endif //GIGACELL_GIGACELL_MAIN_GIGAPLACE_H_
