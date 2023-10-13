//
// Created by zy on 23-10-2.
//

#include "cluster.h"

void gigaplace::Cluster::creatConfigList() {

  for (auto mos1_idx = 0; mos1_idx < block_.size(); mos1_idx++) {
    for (auto mos2_idx = mos1_idx + 1; mos2_idx < block_.size(); mos2_idx++) {
      gigaplace::Operator::addConfig(pl_db_, config_list_, block_.at(mos1_idx), block_.at(mos2_idx));
    }
  }
  for(auto &config : config_list_){
      pl_db_.pair_list().push_back(config);
  }

  for (auto &mos_idx : block_) {
    if (!pl_db_.mos_list().at(mos_idx).getConfigFlag()) {
//      gigaplace::Operator::createDummy( pl_db_, config_list_,mos_idx);
        pl_db_.single_mos_ids().push_back(mos_idx);
    }
  }
}

void gigaplace::Cluster::clearConfigList() {
  std::vector<PlaceDB::Configuration>().swap(config_list_);
  std::vector<index>().swap(block_);
}

void gigaplace::Cluster::getBlock(std::vector<index> &block) {
    block_=block;

}
