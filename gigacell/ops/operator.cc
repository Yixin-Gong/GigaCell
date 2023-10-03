//
// Created by eric on 23-9-21.
//


#include "operator.h"


void gigaplace::Operator::mosFlip(PlaceDB &pl_db, index &mos_idx) {
    for(auto &kMOS : pl_db.nets().find(pl_db.mos_list().at(mos_idx).getLeft())->second){
        if(kMOS.idx == mos_idx)
            kMOS.electrode_name="right";
    }
    for(auto &kMOS : pl_db.nets().find(pl_db.mos_list().at(mos_idx).getRight())->second){
        if(kMOS.idx == mos_idx)
            kMOS.electrode_name="left";
    }
    std::string temp;
    temp=pl_db.mos_list().at(mos_idx).getLeft();
    pl_db.mos_list().at(mos_idx).getLeft()=pl_db.mos_list().at(mos_idx).getRight();
    pl_db.mos_list().at(mos_idx).getRight()=temp;


}

void gigaplace::Operator::swap(PlaceDB &pl_db, index &index1, index &index2) {
    Mos mos1,mos2;
    mos1 = pl_db.mos_list().at(index1);
    mos2 = pl_db.mos_list().at(index2);
  if (mos1.getType() != mos2.getType()) {
    std::cerr << "Error" << std::endl;
    return;
  }

  float loc;
  loc = mos2.getGateLoc();
  mos2.getGateLoc() = mos1.getGateLoc();
  mos1.getGateLoc() = loc;
}

bool gigaplace::Operator::shouldShare(PlaceDB &pl_db, Configuration &c1, Configuration &c2) {
  int i = 0, j = 0;
  if(c1.left_net0 == c2.left_net0 || c1.left_net0 == c2.right_net0)
    i = 1;
  if(c1.right_net0 == c2.left_net0 || c1.right_net0 == c2.right_net0)
    i = 1;
  if(c1.left_net1 == c2.left_net1 || c1.left_net1 == c2.right_net1)
    j = 1;
  if(c1.right_net1 == c2.left_net1 || c1.right_net1 == c2.right_net1)
    j = 1;
  if (i == 1 && j == 1)
    return true;
  else
    return false;
}

void gigaplace::Operator::share(PlaceDB &pl_db, std::vector<Configuration> &config_list) {
//    for(auto config1 : config_list){
//      for(auto config2 : config_list){
//        if(shouldShare(pl_db,config1,config2)){
//          if()
//        }
//      }
//    }
}

void gigaplace::Operator::creatConfig(PlaceDB &pl_db,std::vector<Configuration> &config_list, index &mos1_idx, index &mos2_idx) {
  if (pl_db.mos_list().at(mos1_idx).getType() == pl_db.mos_list().at(mos2_idx).getType())
    return;
  if (pl_db.mos_list().at(mos1_idx).getGate() != pl_db.mos_list().at(mos2_idx).getGate())
    return;
  if(pl_db.mos_list().at(mos1_idx).getConfigFlag() || pl_db.mos_list().at(mos2_idx).getConfigFlag())
    return;
     pl_db.mos_list().at(mos1_idx).getConfigFlag() = true;
     pl_db.mos_list().at(mos2_idx).getConfigFlag() = true;

  Pair p{};
  if (pl_db.mos_list().at(mos1_idx).getType() == 0) {
    p.nmos_idx = mos1_idx;
    p.pmos_idx = mos2_idx;
  } else {
    p.nmos_idx = mos2_idx;
    p.pmos_idx = mos1_idx;
  }
  Configuration config;
  config.pair_list.push_back(p);
  config.left_net0 = pl_db.mos_list().at(p.nmos_idx).getLeft();
  config.right_net0 = pl_db.mos_list().at(p.nmos_idx).getRight();
  config.left_net1 = pl_db.mos_list().at(p.pmos_idx).getLeft();
  config.right_net1 = pl_db.mos_list().at(p.pmos_idx).getRight();
  config_list.push_back(config);
}

void gigaplace::Operator::createDummy(PlaceDB &pl_db, std::vector<Configuration> &config_list,index &single_mos_idx) {
    Mos dummy_mos;
    Mos single_mos;

    single_mos = pl_db.mos_list().at(single_mos_idx);

    if(single_mos.getType() == 0)
        dummy_mos.getType() = 1;
    else
        dummy_mos.getType() = 0;

    dummy_mos.getGate() = single_mos.getGate();
    dummy_mos.getDummyFlag() = true;
    std::string dummy;
    dummy_mos.getMosName() = dummy;

    pl_db.mos_list().push_back(dummy_mos);
    pl_db.mos_ids().push_back(pl_db.mos_list().size()-1);
    index dummy_idx = pl_db.mos_ids()[pl_db.mos_ids().size() - 1];
    gigaplace::Operator::creatConfig(pl_db,config_list,single_mos_idx,dummy_idx);
}

bool gigaplace::Operator::shouldFlip(gigaplace::Configuration &config1, gigaplace::Configuration &config2) {
    if(config1.left_net0 == config2.left_net1){

    }
}
