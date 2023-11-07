//
// Created by eric on 23-9-15.
//
#ifndef GIGACELL_GIGACELL_PLACEMENT_PLACE_DB_H_
#define GIGACELL_GIGACELL_PLACEMENT_PLACE_DB_H_

#include <vector>
#include <unordered_map>
#include "database/database.h"
#include <list>
#include <algorithm>
//#include "ops/operator.h"

namespace gigaplace {
typedef uint16_t index;

class PlaceDB {
 public:
  //constructor
  explicit PlaceDB(DataBase &db) : db_(db) {

    init();
  }

  //setter
  void init();

  static void fold(DataBase &db);
  static Mos createNewMos(Mos &mos);

  struct Net2Mos {
    std::string electrode_name;//left gate right
    index idx;//in mos_list
  };

  struct Pair {
    index pmos_idx{};
    index nmos_idx{};
    index pair_idx{};
  };

  struct Configuration {
    std::vector<Pair> pair_list;
    int32_t num_finger = 0;
    bool share_flag = false;
    float config_loc = 0;
    std::string left_net0;
    std::string left_net1;
    std::string right_net0;
    std::string right_net1;
  };
  //getter
  std::unordered_map<std::string, std::vector<Net2Mos>> &nets() { return nets_; }
  const std::unordered_map<std::string, std::vector<Net2Mos>> &nets() const { return nets_; }
  std::unordered_map<int32_t, std::vector<index>> &blocks() { return blocks_; }
  const std::unordered_map<int32_t, std::vector<index>> &blocks() const { return blocks_; }
  std::vector<index> &nmos_ids() { return nmos_ids_; }
  std::vector<index> &pmos_ids() { return pmos_ids_; }
  std::vector<Mos> &nmos_list() { return nmos_list_; }
  std::vector<Mos> &pmos_list() { return pmos_list_; }
  std::vector<index> &mos_ids() { return mos_ids_; }
  std::vector<Mos> &mos_list() { return mos_list_; }
  std::vector<Configuration> &pair_list(){return pair_list_;}//true pair(have not shared)
  std::vector<index> &single_mos_ids(){return single_mos_ids_;}
  std::vector<index> &config_ids() { return config_ids_; }
  std::vector<Configuration> &v_config() { return v_config_; }
  std::list<Configuration> &l_config() { return l_config_; }
  std::vector<DataBase::Pin> &v_pin_list(){return v_pin_list_;}
 private:
  DataBase &db_;
  std::unordered_map<std::string, std::vector<Net2Mos>> nets_{};
  std::unordered_map<int32_t, std::vector<index>> blocks_{};
  std::vector<index> nmos_ids_{};
  std::vector<Mos> nmos_list_{};
  std::vector<index> pmos_ids_{};
  std::vector<Mos> pmos_list_{};
  std::vector<index> mos_ids_{};
  std::vector<Mos> mos_list_{};
  std::vector<Configuration> pair_list_;
  std::vector<index> single_mos_ids_;
  std::vector<index> config_ids_{};
  std::vector<Configuration> v_config_{};
  std::list<Configuration> l_config_{};
  std::vector<DataBase::Pin> v_pin_list_{};
};

}
#endif //GIGACELL_GIGACELL_PLACEMENT_PLACE_DB_H_
