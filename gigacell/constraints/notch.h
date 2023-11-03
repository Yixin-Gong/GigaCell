//
// Created by zy on 23-11-3.
//

#ifndef GIGACELL_GIGACELL_CONSTRAINTS_NOTCH_H_
#define GIGACELL_GIGACELL_CONSTRAINTS_NOTCH_H_
#include "placement/place_db.h"

namespace gigaplace{
class notch{
  explicit notch(PlaceDB &pl_db , DataBase &db) : pl_db_(pl_db) , db_(db){}
  int32_t notchNum();

 private:
  PlaceDB &pl_db_;
  DataBase &db_;
};
}
#endif //GIGACELL_GIGACELL_CONSTRAINTS_NOTCH_H_
