//
// Created by zy on 23-9-16.
//

#ifndef GIGACELL_NET_H
#define GIGACELL_NET_H

#include <unordered_map>
#include "mos.h"

class Net {
 public:
  Net() = default;

  std::unordered_map<std::string, std::pair<std::string,Mos>> &net2mos() { return net2mos_; }
  const std::unordered_map<std::string,std::pair<std::string,Mos>> &net2mos() const { return net2mos_; }

  void addMos(const std::string &mos_name,const std::string &electrode_name, Mos &mos);


 private:
  std::unordered_map<std::string, std::pair<std::string,Mos>> net2mos_;
};

#endif //GIGACELL_NET_H
