//
// Created by zy on 23-9-25.
//

#ifndef GIGACELL_NETLENGTH_H
#define GIGACELL_NETLENGTH_H

#include "placement/place_db.h"

namespace gigaplace {

class NetLength {
 public:
  NetLength(PlaceDB &pl_db, float length) : pl_db_(pl_db), length_(length) {}

  float netLength();
 private:
  PlaceDB &pl_db_;
  float length_;

};
}
#endif //GIGACELL_NETLENGTH_H
