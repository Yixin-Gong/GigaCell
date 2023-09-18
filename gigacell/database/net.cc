//
// Created by zy on 23-9-16.
//
#include "net.h"
void Net::addMos(const std::string &mos_name,const std::string &electrode_name, Mos &mos) {
  net2mos_.emplace(mos_name,std::pair<std::string,Mos>(electrode_name,mos));
}
