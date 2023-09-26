//
// Created by eric on 23-9-15.
//

#ifndef GIGACELL_GIGACELL_CONSTRAINTS_AREA_H_
#define GIGACELL_GIGACELL_CONSTRAINTS_AREA_H_
#include "placement/place_db.h"
namespace gigaplace {
class Area {
 public:
  explicit Area(PlaceDB &place_db) : place_db_(place_db) {}
  float computeArea();

 private:
  PlaceDB &place_db_;
};
}
#endif //GIGACELL_GIGACELL_CONSTRAINTS_AREA_H_
