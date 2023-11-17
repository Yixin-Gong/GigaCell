//
// Created by eric on 23-9-21.
//


#ifndef GIGACELL_GIGACELL_PLACEMENT_PLACE_OBJ_H_
#define GIGACELL_GIGACELL_PLACEMENT_PLACE_OBJ_H_
#include "constraints/area.h"
#include "constraints/netlength.h"
#include "constraints/pindensity.h"
#include "constraints/notch.h"
#include <cmath>
#include <random>
#include "placement/place_db.h"
#include <limits>

namespace gigaplace {
class PlaceObj {
 public:
  explicit PlaceObj(PlaceDB &pl_db, float &ref_width)
      : pl_db_(pl_db), ref_width_(ref_width) {
    init();

  }
  float getMinGap();
  void getCellRefWidth();
  void getWidthScore();
  void getNetScore();
  void getPinScore();
  void getNotchScore();
  void getSymmetric();
  float &get_score() { return score_; };

  float &get_ss() { return ss_; }
  float &get_bs() { return bs_; }
  float &get_ws() { return ws_; }
  float &get_ps() { return ps_; }

  void init();

 private:
  PlaceDB &pl_db_;
  float &ref_width_;

  float cell_ref_width_{};

  float ws_{};
  float bs_{};
  float ps_{};
  float ss_{};
  float ns_{};

  float score_{};
};
}
#endif //GIGACELL_GIGACELL_PLACEMENT_PLACE_OBJ_H_
