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
  explicit GigaPlace(PlaceDB &pl_db, float &ref_width, float T) : pl_db_(pl_db), ref_width_(ref_width), SA_T_(T) {};
  float SAPlace(uint16_t pair_num,PlaceDB &temp_pl_db);
  void GPlace(uint16_t pair_num);
  void MLASPlace(uint16_t pair_num);
  static float computeDeltaC(float &new_cost, float &old_cost);
  static bool accept(float &delta_c, float T);
  static std::pair<uint16_t ,uint16_t > selectPairMos(PlaceDB &pl_db,std::vector<PlaceDB::Configuration> &v_config);
  static std::pair<uint16_t, uint16_t> generate2Num(uint16_t pair_num);
  float &get_score() { return score_; }
 private:
  PlaceDB &pl_db_;
  float &ref_width_;
  float SA_T_;
  float score_{};
  float G_T_ = 200;
  float MLASS_T_ = 0.5;
  float MLASS_accept_rate_ = 0.5;
  double MLASS_lam_rate_=0;
};
}
#endif //GIGACELL_GIGACELL_MAIN_GIGAPLACE_H_
