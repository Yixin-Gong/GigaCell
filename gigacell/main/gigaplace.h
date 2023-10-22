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
  explicit GigaPlace(PlaceDB &pl_db, PlaceObj &pl_obj) : pl_db_(pl_db), pl_obj_(pl_obj) {};
  void SAPlace();
  static float computeDeltaC(float &new_cost, float &old_cost);
  static bool accept(int &delta_c, float &T);
 private:
  PlaceDB &pl_db_;
  PlaceObj &pl_obj_;
};

}
#endif //GIGACELL_GIGACELL_MAIN_GIGAPLACE_H_
