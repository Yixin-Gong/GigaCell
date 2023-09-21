//
// Created by eric on 23-9-15.
//
#ifndef GIGACELL_GIGACELL_PLACEMENT_PLACE_DB_H_
#define GIGACELL_GIGACELL_PLACEMENT_PLACE_DB_H_
#include <vector>
#include <unordered_map>
#include "database/database.h"

typedef uint16_t index;

struct Net2Mos {
  std::string electrode_name;
  uint16_t type;
  index idx;
};

class PlaceDB {
 public:
  //constructor
  explicit PlaceDB(DataBase &db) : db_(db) {
    init();
  }
  //setter
  void init();
  //getter


 private:
  DataBase &db_;
  std::unordered_map<std::string, std::vector<Net2Mos>> nets_{};
};

#endif //GIGACELL_GIGACELL_PLACEMENT_PLACE_DB_H_
