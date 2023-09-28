//
// Created by eric on 23-9-15.
//
#ifndef GIGACELL_GIGACELL_PLACEMENT_PLACE_DB_H_
#define GIGACELL_GIGACELL_PLACEMENT_PLACE_DB_H_

#include <vector>
#include <unordered_map>
#include "database/database.h"
#include <cmath>
#include <iomanip>
#include <sstream>

namespace gigaplace {
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
  std::unordered_map<std::string, std::vector<Net2Mos>> &nets() { return nets_; }
  const std::unordered_map<std::string, std::vector<Net2Mos>> &nets() const { return nets_; }
  std::vector<index> &nmos_ids() { return nmos_ids_; }
  std::vector<index> &pmos_ids() { return pmos_ids_; }
  std::vector<Mos> &nmos_list() { return nmos_list_; }
  std::vector<Mos> &pmos_list() { return pmos_list_; }

 private:
  DataBase &db_;
  std::unordered_map<std::string, std::vector<Net2Mos>> nets_{};
  std::vector<index> nmos_ids_{};
  std::vector<Mos> nmos_list_{};
  std::vector<index> pmos_ids_{};
  std::vector<Mos> pmos_list_{};
};
}
#endif //GIGACELL_GIGACELL_PLACEMENT_PLACE_DB_H_
