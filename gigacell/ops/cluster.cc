//
// Created by zy on 23-10-2.
//

#include "cluster.h"

void gigaplace::Cluster::creatConfigList() {
//    std::vector<index> block1=block_;

    for(auto mos1_idx=0;mos1_idx<block_.size();mos1_idx++) {
        for (auto mos2_idx = mos1_idx+1;mos2_idx<block_.size();mos2_idx++){
            gigaplace::Operator::creatConfig(block_.at(mos1_idx),block_.at(mos2_idx),config_list_,pl_db_);
        }
    }
    for(auto mos_idx : block_){
        if(!pl_db_.mos_list().at(mos_idx).getConfigFlag()){
            gigaplace::Operator::createDummy(mos_idx,pl_db_,config_list_);

        }

    }
}

void gigaplace::Cluster::clearConfigList() {
     std::vector<Configuration>().swap(config_list_);
}
