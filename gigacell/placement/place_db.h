//
// Created by eric on 23-9-15.
//
#ifndef GIGACELL_GIGACELL_PLACEMENT_PLACE_DB_H_
#define GIGACELL_GIGACELL_PLACEMENT_PLACE_DB_H_
#include <vector>
#include "database/database.h"

typedef uint32_t index;

class PlaceDB {
 public:
  //constructor
  explicit PlaceDB(DataBase &db) : db_(db) {
    init();
  }
  //setter
  void init();

  //getter
  std::vector<index> &v_mos_ids() { return v_mos_ids_; }
  const std::vector<index> &v_mos_ids() const { return v_mos_ids_; }
  std::vector<index> &v_net2mos_ids() { return v_net2mos_ids_; }
  const std::vector<index> &v_net2mos_ids() const { return v_net2mos_ids_; }
  std::vector<Mos> &v_mos_list() { return v_mos_list_; }
  const std::vector<Mos> &v_mos_list() const { return v_mos_list_; }
  std::vector<std::pair<std::string, Mos>> &v_net2mos() { return v_net2mos_; }
  const std::vector<std::pair<std::string, Mos>> &v_net2mos() const { return v_net2mos_; }
  std::unordered_map<std::string, Mos> &nets() { return nets_; };
  const std::unordered_map<std::string, Mos> &nets() const { return nets_; };

 private:
  DataBase &db_;
  std::vector<index> v_mos_ids_{};
  std::vector<Mos> v_mos_list_{};
  std::vector<index> v_net2mos_ids_{};
  std::vector<std::pair<std::string, Mos>> v_net2mos_{};
  std::unordered_map<std::string, Mos> nets_{};

};

#endif //GIGACELL_GIGACELL_PLACEMENT_PLACE_DB_H_
