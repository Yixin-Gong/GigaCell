//
// Created by eric on 23-9-15.
//

#include "database.h"
void DataBase::addNet(const std::string &name, Net &net) {
  nets_.emplace(name, net);
}
int32_t DataBase::netsLength() {
  int32_t nets_length;
  for(auto &kNet:nets_){
    nets_length += kNet.second.netLength();
  }
  return nets_length;
}
