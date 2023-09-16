//
// Created by zy on 23-9-16.
//
#include <limits>
#include "net.h"
void Net::addMos(const std::string &name, Mos &mos) {
  net_.emplace(name, mos);
}

int32_t Net::netLength() {
  int32_t minLoc_ = -std::numeric_limits<int32_t>::max();
  int32_t maxLoc_ = std::numeric_limits<int32_t>::max();
  for (auto &kMos : net_) {
    auto current_loc = kMos.second.getLoc();
    minLoc_ = std::min(current_loc, minLoc_);
    maxLoc_ = std::max(current_loc, maxLoc_);
  }
  return maxLoc_ - minLoc_;
}