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
  explicit GigaPlace(PlaceDB &pl_db, PlaceObj &pl_obj, float T) : pl_db_(pl_db), pl_obj_(pl_obj),T(10000) {};
  void SAPlace(uint16_t pair_num);
  static float computeDeltaC(float &new_cost, float &old_cost);
  static bool accept(float &delta_c, float T);
  static std::pair<uint16_t, uint16_t> generate2Num(PlaceDB &place_db, uint16_t pair_num);
 private:
  PlaceDB &pl_db_;
  PlaceObj &pl_obj_;
  float T;
};

}
#endif //GIGACELL_GIGACELL_MAIN_GIGAPLACE_H_
