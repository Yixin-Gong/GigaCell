//
// Created by eric on 23-9-15.
//

#ifndef GIGACELL_GIGACELL_DATABASE_DATABASE_H_
#define GIGACELL_GIGACELL_DATABASE_DATABASE_H_

#include <iostream>
#include <vector>
#include "mos.h"
typedef uint16_t index;
class DataBase {
  DataBase() = default;
 public:
  //getter&&setter
  std::vector<index> &nmos_ids() { return nmos_ids_; }
  std::vector<index> &pmos_ids() { return pmos_ids_; }
  std::vector<Mos> &nmos_list() { return nmos_list_; }
  std::vector<Mos> &pmos_list() { return pmos_list_; }
 private:
  std::vector<index> nmos_ids_{};
  std::vector<Mos> nmos_list_{};
  std::vector<index> pmos_ids_{};
  std::vector<Mos> pmos_list_{};
};

#endif //GIGACELL_GIGACELL_DATABASE_DATABASE_H_
