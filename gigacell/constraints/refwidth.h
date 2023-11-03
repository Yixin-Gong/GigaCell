//
// Created by zy on 23-11-3.
//

#ifndef GIGACELL_GIGACELL_CONSTRAINTS_REFWIDTH_H_
#define GIGACELL_GIGACELL_CONSTRAINTS_REFWIDTH_H_
#include "database/database.h"
namespace gigaplace {
class RefWidth {
 public:
  explicit RefWidth(DataBase &db) : db_(db) {}

  float getRefWidth();
 private:
  DataBase &db_;
};

}
#endif //GIGACELL_GIGACELL_CONSTRAINTS_REFWIDTH_H_
