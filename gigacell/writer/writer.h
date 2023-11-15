//
// Created by eric on 23-9-15.
//

#ifndef GIGACELL_GIGACELL_WRITER_WRITER_H_
#define GIGACELL_GIGACELL_WRITER_WRITER_H_
#include "placement/place_db.h"
namespace gigaplace {
class Writer {
 public:
  Writer(PlaceDB &place_db, std::string &cell) : pl_db(place_db), cell_name_(cell) {};
  void output();
 private:
  PlaceDB &pl_db;
  std::string cell_name_{};
};
}

#endif //GIGACELL_GIGACELL_WRITER_WRITER_H_
