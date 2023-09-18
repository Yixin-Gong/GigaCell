//
// Created by eric on 23-9-15.
//

#ifndef GIGACELL_GIGACELL_DATABASE_DATABASE_H_
#define GIGACELL_GIGACELL_DATABASE_DATABASE_H_

#include <iostream>
#include <unordered_map>
#include "net.h"

class DataBase {
  DataBase() = default;
 public:
  //getter&&setter
  std::unordered_map<std::string, Net> &nets() { return nets_; }
  const std::unordered_map<std::string, Net> &nets() const { return nets_; }
  void addNet(const std::string &name,Net &net2mos);
 private:
  std::unordered_map<std::string, Net> nets_{};
};

#endif //GIGACELL_GIGACELL_DATABASE_DATABASE_H_
