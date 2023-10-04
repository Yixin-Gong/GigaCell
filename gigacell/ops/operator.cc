//
// Created by eric on 23-9-21.
//


#include "operator.h"

void gigaplace::Operator::mosFlip(PlaceDB &pl_db, index &mos_idx) {
  if (pl_db.mos_list().at(mos_idx).getDummyFlag())
    return;

  if (pl_db.mos_list().at(mos_idx).getLeft() != "VDD" && pl_db.mos_list().at(mos_idx).getLeft() != "VSS") {
    for (auto &kMOS : pl_db.nets().find(pl_db.mos_list().at(mos_idx).getLeft())->second) {
      if (kMOS.idx == mos_idx)
        kMOS.electrode_name = "right";
    }
  }
  if (pl_db.mos_list().at(mos_idx).getRight() != "VDD" && pl_db.mos_list().at(mos_idx).getRight() != "VSS") {
    for (auto &kMOS : pl_db.nets().find(pl_db.mos_list().at(mos_idx).getRight())->second) {
      if (kMOS.idx == mos_idx)
        kMOS.electrode_name = "left";
    }
  }
  std::string temp;
  temp = pl_db.mos_list().at(mos_idx).getLeft();
  pl_db.mos_list().at(mos_idx).getLeft() = pl_db.mos_list().at(mos_idx).getRight();
  pl_db.mos_list().at(mos_idx).getRight() = temp;
}

void gigaplace::Operator::swap(PlaceDB &pl_db, index &index1, index &index2) {
  Mos mos1, mos2;
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

std::string gigaplace::Operator::shouldShare(PlaceDB &pl_db, Configuration &c1, Configuration &c2) {
  //two pair
  if (c1.num_finger == 0 && c2.num_finger == 0) {
    //flip 0
    if (c1.right_net0 == c2.left_net0 && c1.right_net1 == c2.left_net1)
      return "do without Flip";
    //flip 4
    if (c1.left_net0 == c2.right_net0 && c1.left_net1 == c2.right_net1)
      return "mosFlip c1_0_1 c2_0_1";
    //flip 1
    if (c1.left_net1 == c2.left_net1 && c1.right_net0 == c2.left_net0)
      return "mosFlip c1_1";
    if (c1.right_net1 == c2.left_net1 && c1.left_net0 == c2.left_net0)
      return "mosFlip c1_0";
    if (c1.right_net1 == c2.right_net1 && c1.right_net0 == c2.left_net0)
      return "mosFlip c2_1";
    if (c1.right_net1 == c2.left_net1 && c1.right_net0 == c2.right_net0)
      return "mosFlip c2_0";
    //flip 3
    if (c1.right_net1 == c2.right_net1 && c1.left_net0 == c2.right_net0)
      return "mosFlip c1_0 configFlip c2";
    if (c1.left_net1 == c2.right_net1 && c1.right_net0 == c2.right_net0)
      return "mosFlip c1_1 configFlip c2";
    if (c1.left_net1 == c2.left_net1 && c1.left_net0 == c2.right_net0)
      return "mosFlip c2_0 configFlip c1";
    if (c1.left_net1 == c2.right_net1 && c1.left_net0 == c2.left_net0)
      return "mosFlip c2_1 configFlip c1";
    //flip 2
    if(c1.left_net1 == c2.right_net1 && c1.right_net0 == c2.left_net0)
      return "mosFlip c1_1 c2_1";
    if(c1.right_net1 == c2.right_net1 && c1.right_net0 == c2.right_net1)
      return "configFlip c2";
    if(c1.right_net1 == c2.left_net1 && c1.left_net0 == c2.right_net0)
      return " mosFlip c1_0 c2_0";
    if(c1.left_net1 == c2.left_net1 && c1.left_net0 == c2.left_net0)
      return "configFlip c1";
    if(c1.left_net1 == c2.left_net1 && c1.right_net0 == c2.right_net0)
      return "mosFlip c1_1 c2_0";
    if(c1.right_net1 == c2.right_net1 && c1.left_net0 == c2.left_net0)
      return "mosFlip c1_0 c2_1";
  }

  //one pair one config
  if (c1.num_finger == 0 && c2.num_finger != 0) {
      if(c1.right_net1 == c2.left_net1 && c1.right_net0 == c2.left_net0)
        return "do without Flip";
      if(c1.left_net1 == c2.left_net1 && c1.right_net0 == c2.left_net0)
        return "mosFlip c1_1";
      if(c1.right_net1 == c2.left_net1 && c1.left_net0 == c2.left_net0)
        return "mosFlip c1_0";
      if(c1.left_net1 == c2.left_net1 && c1.left_net0 == c2.left_net0)
        return "configFlip c1";
      if(c1.right_net1 == c2.right_net1 && c1.right_net0 == c2.right_net0)
        return "configFlip c2";
      if(c1.left_net1 == c2.right_net1 && c1.right_net0 == c2.right_net0)
        return "mosFlip c1_1 configFlip c2";
      if(c1.right_net1 == c2.right_net1 && c1.left_net0 == c2.right_net0)
        return "mosFlip c1_0 configFlip c2";
      if(c1.left_net1 == c2.right_net1 && c1.left_net0 == c2.right_net0)
        return "configFlip c1 c2";
  }
  if(c1.num_finger !=0 && c2.num_finger ==0 ){
      if(c1.right_net1 == c2.left_net1 && c1.right_net0 == c2.left_net0)
        return "do without Flip";
      if(c1.right_net1 == c2.right_net1 && c1.right_net0 == c2.left_net0)
        return "mosFlip c2_1";
      if(c1.right_net1 == c2.left_net1 && c1.right_net0 == c2.right_net0)
        return "mosFlip c2_0";
      if(c1.right_net1 == c2.right_net1 && c1.right_net0 == c2.right_net0)
        return "configFlip c2";
      if(c1.left_net1 == c2.left_net1 && c1.left_net0 == c2.left_net0)
        return "configFlip c1";
      if(c1.left_net1 == c2.right_net1 && c1.left_net0 == c2.left_net0)
        return "mosFlip c2_1 configFlip c1";
      if(c1.left_net1 == c2.left_net1 && c1.left_net0 == c2.right_net0)
        return "mosFlip c2_0 configFlip c1";
      if(c1.left_net1 == c2.right_net1 && c1.left_net0 == c2.right_net0)
        return "configFlip c1 c2";
  }
  //two config
  if (c1.num_finger != 0 && c2.num_finger != 0) {
    if (c1.left_net0 == c2.left_net0 && c1.left_net1 == c2.left_net1)
      return "configFlip c1";
    if (c1.left_net0 == c2.right_net0 && c1.left_net1 == c2.right_net1)
      return "configFlip c1 c2";
    if (c1.right_net0 == c2.left_net0 && c1.right_net1 == c2.left_net1)
      return "do without Flip";
    if (c1.right_net0 == c2.right_net0 && c1.right_net1 == c2.right_net1)
      return "configFlip c2";
  }
  return "could not share";
}

void gigaplace::Operator::share(PlaceDB &pl_db, std::vector<Configuration> &config_list) {
  for (auto config1 : config_list) {
    for (auto config2 : config_list){

    }
  }
}

void gigaplace::Operator::addConfig(PlaceDB &pl_db,
                                    std::vector<Configuration> &config_list,
                                    index &mos1_idx,
                                    index &mos2_idx) {
  if (pl_db.mos_list().at(mos1_idx).getType() == pl_db.mos_list().at(mos2_idx).getType())
    return;
  if (pl_db.mos_list().at(mos1_idx).getGate() != pl_db.mos_list().at(mos2_idx).getGate())
    return;
  if (pl_db.mos_list().at(mos1_idx).getConfigFlag() || pl_db.mos_list().at(mos2_idx).getConfigFlag())
    return;
  pl_db.mos_list().at(mos1_idx).getConfigFlag() = true;
  pl_db.mos_list().at(mos2_idx).getConfigFlag() = true;

  Pair pair{};
  if (pl_db.mos_list().at(mos1_idx).getType() == 0) {
    pair.nmos_idx = mos1_idx;
    pair.pmos_idx = mos2_idx;
  } else {
    pair.nmos_idx = mos2_idx;
    pair.pmos_idx = mos1_idx;
  }
  Configuration config{};
  config.pair_list.push_back(pair);
  config.left_net0 = pl_db.mos_list().at(pair.nmos_idx).getLeft();
  config.right_net0 = pl_db.mos_list().at(pair.nmos_idx).getRight();
  config.left_net1 = pl_db.mos_list().at(pair.pmos_idx).getLeft();
  config.right_net1 = pl_db.mos_list().at(pair.pmos_idx).getRight();
  config_list.push_back(config);
}

void gigaplace::Operator::createDummy(PlaceDB &pl_db, std::vector<Configuration> &config_list, index &single_mos_idx) {
  Mos dummy_mos{};
  Mos single_mos{};

  single_mos = pl_db.mos_list().at(single_mos_idx);

  if (single_mos.getType() == 0)
    dummy_mos.getType() = 1;
  else
    dummy_mos.getType() = 0;

  dummy_mos.getGate() = single_mos.getGate();
  dummy_mos.getDummyFlag() = true;
  std::string dummy;
  dummy_mos.getMosName() = dummy;

  pl_db.mos_list().push_back(dummy_mos);
  pl_db.mos_ids().push_back(pl_db.mos_list().size() - 1);
  index dummy_idx = pl_db.mos_ids()[pl_db.mos_ids().size() - 1];
  gigaplace::Operator::addConfig(pl_db, config_list, single_mos_idx, dummy_idx);
}


void gigaplace::Operator::configFlip(gigaplace::PlaceDB &pl_db, gigaplace::Configuration &config) {
  std::reverse(config.pair_list.begin(), config.pair_list.end());
  for (auto &pair : config.pair_list) {
    gigaplace::Operator::mosFlip(pl_db, pair.pmos_idx);
    gigaplace::Operator::mosFlip(pl_db, pair.nmos_idx);
  }

  std::string temp;
  temp = config.right_net0;
  config.right_net0 = config.left_net0;
  config.left_net0 = temp;
  temp = config.right_net1;
  config.right_net1 = config.left_net1;
  config.left_net1 = temp;
}
