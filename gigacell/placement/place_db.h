//
// Created by eric on 23-9-15.
//
#ifndef GIGACELL_GIGACELL_PLACEMENT_PLACE_DB_H_
#define GIGACELL_GIGACELL_PLACEMENT_PLACE_DB_H_

#include <vector>
#include <unordered_map>
#include "database/database.h"
#include "ops/operator.h"
#include <cmath>
#include <iomanip>


namespace gigaplace {
typedef uint16_t index;

struct Net2Mos {
  std::string electrode_name;
  uint16_t type;
  index idx;
};
//TODO:Implement Pair and Configuration structure@zy and lky
struct Pair {

};

struct Configuration {

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
  std::vector<index> &mos_ids() { return mos_ids_; }
  std::vector<Mos> &mos_list() { return mos_list_; }
  std::vector<index> &pair_ids() { return pair_ids_; }
  std::vector<Pair> &pair_list() { return pair_list_; }
  std::vector<index> &config_ids() { return config_ids_; }
  std::vector<Configuration> &config_list() { return config_list_; }

 private:
  DataBase &db_;
  std::unordered_map<std::string, std::vector<Net2Mos>> nets_{};
  std::vector<index> nmos_ids_{};
  std::vector<Mos> nmos_list_{};
  std::vector<index> pmos_ids_{};
  std::vector<Mos> pmos_list_{};
  std::vector<index> mos_ids_{};
  std::vector<Mos> mos_list_{};
  std::vector<index> pair_ids_{};
  std::vector<Pair> pair_list_{};
  std::vector<index> config_ids_{};
  std::vector<Configuration> config_list_{};

};
}
#endif //GIGACELL_GIGACELL_PLACEMENT_PLACE_DB_H_
