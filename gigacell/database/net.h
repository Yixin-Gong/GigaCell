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

  std::unordered_map<std::string, Mos> &net() { return net_; }
  const std::unordered_map<std::string, Mos> &net() const { return net_; }

  void addMos(const std::string &name, Mos &mos);
  int32_t netLength();

 private:
  std::unordered_map<std::string, Mos> net_;

};

#endif //GIGACELL_NET_H
