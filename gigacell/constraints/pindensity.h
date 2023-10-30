//
// Created by zy on 23-10-28.
//

#ifndef GIGACELL_GIGACELL_CONSTRAINTS_PINDENSITY_H_
#define GIGACELL_GIGACELL_CONSTRAINTS_PINDENSITY_H_

#include "database/database.h"
namespace  gigaplace {

class PinDensity{
 public:
  explicit  PinDensity(DataBase &db) : db_(db){}

  float pinDensity();
 private:
  DataBase &db_;
};
}
#endif //GIGACELL_GIGACELL_CONSTRAINTS_PINDENSITY_H_
