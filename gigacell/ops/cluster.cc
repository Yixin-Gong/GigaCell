//
// Created by zy on 23-10-2.
//

#include "cluster.h"

void gigaplace::Cluster::creatConfigList() {

  for (auto mos1_idx = 0; mos1_idx < block_.size(); mos1_idx++) {
    for (auto mos2_idx = mos1_idx + 1; mos2_idx < block_.size(); mos2_idx++) {
      gigaplace::Operator::creatConfig(pl_db_, config_list_,block_.at(mos1_idx), block_.at(mos2_idx));
    }
  }

  for (auto mos_idx : block_) {
    if (!pl_db_.mos_list().at(mos_idx).getConfigFlag()) {
      gigaplace::Operator::createDummy( pl_db_, config_list_,mos_idx);
    }
  }
}

void gigaplace::Cluster::clearConfigList() {
  std::vector<Configuration>().swap(config_list_);
}
