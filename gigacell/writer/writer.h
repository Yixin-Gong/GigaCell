//
// Created by eric on 23-9-15.
//

#ifndef GIGACELL_GIGACELL_WRITER_WRITER_H_
#define GIGACELL_GIGACELL_WRITER_WRITER_H_
#include "placement/place_db.h"
namespace gigaplace {
class Writer {
 public:
  Writer(PlaceDB &place_db, std::string &cell, std::string &output_path)
      : pl_db_(place_db), cell_name_(cell), output_path_(output_path) {};
  void output();
 private:
  PlaceDB &pl_db_;
  std::string cell_name_{};
  std::string output_path_{};
};
}

#endif //GIGACELL_GIGACELL_WRITER_WRITER_H_
