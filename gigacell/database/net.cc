//
// Created by zy on 23-9-16.
//
#include "net.h"
void Net::addMos(const std::string &name, Mos &mos) {
  net_.emplace(name, mos);
}
