//
// Created by zy on 23-9-25.
//

#ifndef GIGACELL_NETLENGTH_H
#define GIGACELL_NETLENGTH_H

#include "placement/place_db.h"

namespace gigaplace {

class NetLength {
 public:
 explicit NetLength(PlaceDB &pl_db) : pl_db_(pl_db){}

  float calNetLength();
 private:
  PlaceDB &pl_db_;

};
}
#endif //GIGACELL_NETLENGTH_H
