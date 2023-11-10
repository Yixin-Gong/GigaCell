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

void gigaplace::Operator::swap(PlaceDB &pl_db, index &pair1, index &pair2) {
  int32_t find_pair_idx1 = -1;
  int32_t find_pair_idx2 = -1;
  for (auto &config : pl_db.l_config()) {
    find_pair_idx1++;
    if (config.pair_list.at(0).pair_idx == pair1)
      break;
  }

  for (auto &config : pl_db.l_config()) {
    find_pair_idx2++;
    if (config.pair_list.at(0).pair_idx == pair2)
      break;
  }

  auto it1 = pl_db.l_config().begin();
  std::advance(it1, find_pair_idx1);
  auto it2 = pl_db.l_config().begin();
  std::advance(it2, find_pair_idx2);
  std::swap(*it1, *it2);
}

int32_t gigaplace::Operator::shouldShare(PlaceDB &pl_db, PlaceDB::Configuration &c1, PlaceDB::Configuration &c2) {
  auto c1_r0_dummy = c1.right_net0 == "dummy";
  auto c1_r1_dummy = c1.right_net1 == "dummy";
  auto c1_l0_dummy = c1.left_net0 == "dummy";
  auto c1_l1_dummy = c1.left_net1 == "dummy";

  auto c2_r0_dummy = c2.right_net0 == "dummy";
  auto c2_r1_dummy = c2.right_net1 == "dummy";
  auto c2_l0_dummy = c2.left_net0 == "dummy";
  auto c2_l1_dummy = c2.left_net1 == "dummy";

  auto or_c1l0_c2l0_dummy = c1_l0_dummy || c2_l0_dummy;
  auto or_c1l0_c2r0_dummy = c1_l0_dummy || c2_r0_dummy;
  auto or_c1r0_c2l0_dummy = c1_r0_dummy || c2_l0_dummy;
  auto or_c1r0_c2r0_dummy = c1_r0_dummy || c2_r0_dummy;

  auto or_c1l1_c2l1_dummy = c1_l1_dummy || c2_l1_dummy;
  auto or_c1l1_c2r1_dummy = c1_l1_dummy || c2_r1_dummy;
  auto or_c1r1_c2l1_dummy = c1_r1_dummy || c2_l1_dummy;
  auto or_c1r1_c2r1_dummy = c1_r1_dummy || c2_r1_dummy;

  auto eq_c1l0_c2l0 = c1.left_net0 == c2.left_net0;
  auto eq_c1l0_c2r0 = c1.left_net0 == c2.right_net0;
  auto eq_c1r0_c2l0 = c1.right_net0 == c2.left_net0;
  auto eq_c1r0_c2r0 = c1.right_net0 == c2.right_net0;

  auto eq_c1l1_c2l1 = c1.left_net1 == c2.left_net1;
  auto eq_c1l1_c2r1 = c1.left_net1 == c2.right_net1;
  auto eq_c1r1_c2l1 = c1.right_net1 == c2.left_net1;
  auto eq_c1r1_c2r1 = c1.right_net1 == c2.right_net1;

  if (c1.share_flag || c2.share_flag)
////    return "1/2 config had been used";
    return CONFIG_HAD_BEEN_USED;
  //two pair
  if (c1.num_finger == 0 && c2.num_finger == 0) {
    //flip 0
    if ((eq_c1r0_c2l0 || or_c1r0_c2l0_dummy) && (eq_c1r1_c2l1 || or_c1r1_c2l1_dummy))
////      return "do without Flip";
      return NO_FLIP;
    //flip 4
    if ((eq_c1l0_c2r0 || or_c1l0_c2r0_dummy) && (eq_c1l1_c2r1 || or_c1l1_c2r1_dummy))
////      return "mosFlip c1_0_1 c2_0_1";
      return CONFIGFLIP_C1_C2;
    //flip 1
    if ((eq_c1l1_c2l1 || or_c1l1_c2l1_dummy) && (eq_c1r0_c2l0 || or_c1r0_c2l0_dummy))
////      return "mosFlip c1_1";
      return MOSFLIP_C1P;
    if ((eq_c1r1_c2l1 || or_c1r1_c2l1_dummy) && (eq_c1l0_c2l0 || or_c1l0_c2l0_dummy))
////      return "mosFlip c1_0";
      return MOSFLIP_C1N;
    if ((eq_c1r1_c2r1 || or_c1r1_c2r1_dummy) && (eq_c1r0_c2l0 || or_c1r0_c2l0_dummy))
////      return "mosFlip c2_1";
      return MOSFLIP_C2P;
    if ((eq_c1r1_c2l1 || or_c1r1_c2l1_dummy) && (eq_c1r0_c2r0 || or_c1r0_c2r0_dummy))
////      return "mosFlip c2_0";
      return MOSFLIP_C2N;
    //flip 3
    if ((eq_c1r1_c2r1 || or_c1r1_c2r1_dummy) && (eq_c1l0_c2r0 || or_c1l0_c2r0_dummy))
////      return "mosFlip c1_0 configFlip c2";
      return MOSFLIP_C1N_CONFIGFLIP_C2;
    if ((eq_c1l1_c2r1 || or_c1l1_c2r1_dummy) && (eq_c1r0_c2r0 || or_c1r0_c2r0_dummy))
////      return "mosFlip c1_1 configFlip c2";
      return MOSFLIP_C1P_CONFIGFLIP_C2;
    if ((eq_c1l1_c2l1 || or_c1l1_c2l1_dummy) && (eq_c1l0_c2r0 || or_c1l0_c2r0_dummy))
////      return "mosFlip c2_0 configFlip c1";
      return MOSFLIP_C2N_CONFIGFLIP_C1;
    if ((eq_c1l1_c2r1 || or_c1l1_c2r1_dummy) && (eq_c1l0_c2l0 || or_c1l0_c2l0_dummy))
////      return "mosFlip c2_1 configFlip c1";
      return MOSFLIP_C2P_CONFIGFLIP_C1;
    //flip 2
    if ((eq_c1l1_c2r1 || or_c1l1_c2r1_dummy) && (eq_c1r0_c2l0 || or_c1r0_c2l0_dummy))
////      return "mosFlip c1_1 c2_1";
      return MOSFLIP_C1P_C2P;
    if ((eq_c1r1_c2r1 || or_c1r1_c2r1_dummy) && (eq_c1r0_c2r0 || or_c1r0_c2r0_dummy))
////      return "configFlip c2";
      return CONFIGFLIP_C2;
    if ((eq_c1r1_c2l1 || or_c1r1_c2l1_dummy) && (eq_c1l0_c2r0 || or_c1l0_c2r0_dummy))
////      return "mosFlip c1_0 c2_0";
      return MOSFLIP_C1N_C2N;
    if ((eq_c1l1_c2l1 || or_c1l1_c2l1_dummy) && (eq_c1l0_c2l0 || or_c1l0_c2l0_dummy))
////      return "configFlip c1";
      return CONFIGFLIP_C1;
    if ((eq_c1l1_c2l1 || or_c1l1_c2l1_dummy) && (eq_c1l0_c2l0 || or_c1l0_c2l0_dummy))
////      return "mosFlip c1_1 c2_0";
      return MOSFLIP_C1P_C2N;
    if ((eq_c1r1_c2r1 || or_c1r1_c2r1_dummy) && (eq_c1l0_c2l0 || or_c1l0_c2l0_dummy))
////      return "mosFlip c1_0 c2_1";
      return MOSFLIP_C1N_C2P;
  }

  //one pair one config
  if (c1.num_finger == 0 && c2.num_finger != 0) {
    if ((eq_c1r1_c2l1 || or_c1r1_c2l1_dummy) && (eq_c1r0_c2l0 || or_c1r0_c2l0_dummy))
////      return "do without Flip";
      return NO_FLIP;
    if ((eq_c1l1_c2l1 || or_c1l1_c2l1_dummy) && (eq_c1r0_c2l0 || or_c1r0_c2l0_dummy))
////      return "mosFlip c1_1";
      return MOSFLIP_C1P;
    if ((eq_c1r1_c2l1 || or_c1r1_c2l1_dummy) && (eq_c1l0_c2l0 || or_c1l0_c2l0_dummy))
////      return "mosFlip c1_0";
      return MOSFLIP_C1N;
    if ((eq_c1l1_c2l1 || or_c1l1_c2l1_dummy) && (eq_c1l0_c2l0 || or_c1l0_c2l0_dummy))
////      return "configFlip c1";
      return CONFIGFLIP_C1;
    if ((eq_c1r1_c2r1 || or_c1r1_c2r1_dummy) && (eq_c1r0_c2r0 || or_c1r0_c2r0_dummy))
////      return "configFlip c2";
      return CONFIGFLIP_C2;
    if ((eq_c1l1_c2r1 || or_c1l1_c2r1_dummy) && (eq_c1r0_c2r0 || or_c1r0_c2r0_dummy))
////      return "mosFlip c1_1 configFlip c2";
      return MOSFLIP_C1P_CONFIGFLIP_C2;
    if ((eq_c1r1_c2r1 || or_c1r1_c2r1_dummy) && (eq_c1l0_c2r0 || or_c1l0_c2r0_dummy))
////      return "mosFlip c1_0 configFlip c2";
      return MOSFLIP_C1N_CONFIGFLIP_C2;
    if ((eq_c1l1_c2r1 || or_c1l1_c2r1_dummy) && (eq_c1l0_c2r0 || or_c1l0_c2r0_dummy))
////      return "configFlip c1 c2";
      return CONFIGFLIP_C1_C2;
  }
  if (c1.num_finger != 0 && c2.num_finger == 0) {
    if ((eq_c1r1_c2l1 || or_c1r1_c2l1_dummy) && (eq_c1r0_c2l0 || or_c1r0_c2l0_dummy))
////      return "do without Flip";
      return NO_FLIP;
    if ((eq_c1r1_c2r1 || or_c1r1_c2r1_dummy) && (eq_c1r0_c2l0 || or_c1r0_c2l0_dummy))
////      return "mosFlip c2_1";
      return MOSFLIP_C2P;
    if ((eq_c1r1_c2l1 || or_c1r1_c2l1_dummy) && (eq_c1r0_c2r0 || or_c1r0_c2r0_dummy))
////      return "mosFlip c2_0";
      return MOSFLIP_C2N;
    if ((eq_c1r1_c2r1 || or_c1r1_c2r1_dummy) && (eq_c1r0_c2r0 || or_c1r0_c2r0_dummy))
////      return "configFlip c2";
      return CONFIGFLIP_C2;
    if ((eq_c1l1_c2l1 || or_c1l1_c2l1_dummy) && (eq_c1l0_c2l0 || or_c1l0_c2l0_dummy))
////      return "configFlip c1";
      return CONFIGFLIP_C1;
    if ((eq_c1l1_c2r1 || or_c1l1_c2r1_dummy) && (eq_c1l0_c2l0 || or_c1l0_c2l0_dummy))
////      return "mosFlip c2_1 configFlip c1";
      return MOSFLIP_C2P_CONFIGFLIP_C1;
    if ((eq_c1l1_c2l1 || or_c1l1_c2l1_dummy) && (eq_c1l0_c2r0 || or_c1l0_c2r0_dummy))
////      return "mosFlip c2_0 configFlip c1";
      return MOSFLIP_C2N_CONFIGFLIP_C1;
    if ((eq_c1l1_c2r1 || or_c1l1_c2r1_dummy) && (eq_c1l0_c2r0 || or_c1l0_c2r0_dummy))
////      return "configFlip c1 c2";
      return CONFIGFLIP_C1_C2;
  }
  //two config
  if (c1.num_finger != 0 && c2.num_finger != 0) {
    if ((eq_c1l0_c2l0 || or_c1l0_c2l0_dummy) && (eq_c1l1_c2l1 || or_c1l1_c2l1_dummy))
////      return "configFlip c1";
      return CONFIGFLIP_C1;
    if ((eq_c1l0_c2r0 || or_c1l0_c2r0_dummy) && (eq_c1l1_c2r1 || or_c1l1_c2r1_dummy))
////      return "configFlip c1 c2";
      return CONFIGFLIP_C1_C2;
    if ((eq_c1r0_c2l0 || or_c1r0_c2l0_dummy) && (eq_c1r1_c2l1 || or_c1r1_c2l1_dummy))
////      return "do without Flip";
      return NO_FLIP;
    if ((eq_c1r0_c2r0 || or_c1r0_c2r0_dummy) && (eq_c1r1_c2r1 || or_c1r1_c2r1_dummy))
////      return "configFlip c2";
      return CONFIGFLIP_C2;
  }
////  return "could not share";
  return COULD_NOT_SHARE;
}

void gigaplace::Operator::share(PlaceDB &pl_db, std::vector<PlaceDB::Configuration> &config_list) {
  index primary_config_list_size, current_config_list_size;
  primary_config_list_size = config_list.size();
  current_config_list_size = config_list.size();

  for (auto i = 0; i < primary_config_list_size; i++) {
    for (auto j = i + 1; j < current_config_list_size; j++) {
//
//      std::vector<index> v_special_mos_idx{};
//      if (config_list.at(i).num_finger > 0) {
//        if (pl_db.mos_list().at(config_list.at(i).pair_list.at(1).pmos_idx).getDummyFlag())
//          v_special_mos_idx.push_back(config_list.at(i).pair_list.at(0).pmos_idx);
//        else if (pl_db.mos_list().at(config_list.at(i).pair_list.at(1).nmos_idx).getDummyFlag())
//          v_special_mos_idx.push_back(config_list.at(i).pair_list.at(0).nmos_idx);
//        if (pl_db.mos_list().at(config_list.at(i).pair_list.at(
//            config_list.at(i).num_finger - 1).pmos_idx).getDummyFlag())
//          v_special_mos_idx.push_back(config_list.at(i).pair_list.at(config_list.at(i).num_finger).pmos_idx);
//        else if (pl_db.mos_list().at(config_list.at(i).pair_list.at(
//            config_list.at(i).num_finger - 1).nmos_idx).getDummyFlag())
//          v_special_mos_idx.push_back(config_list.at(i).pair_list.at(config_list.at(i).num_finger).nmos_idx);
//      }
//      if (config_list.at(j).num_finger > 0) {
//        if (pl_db.mos_list().at(config_list.at(j).pair_list.at(1).pmos_idx).getDummyFlag())
//          v_special_mos_idx.push_back(config_list.at(j).pair_list.at(0).pmos_idx);
//        else if (pl_db.mos_list().at(config_list.at(j).pair_list.at(1).nmos_idx).getDummyFlag())
//          v_special_mos_idx.push_back(config_list.at(j).pair_list.at(0).nmos_idx);
//        if (pl_db.mos_list().at(config_list.at(j).pair_list.at(
//            config_list.at(j).num_finger - 1).pmos_idx).getDummyFlag())
//          v_special_mos_idx.push_back(config_list.at(j).pair_list.at(config_list.at(j).num_finger).pmos_idx);
//        else if (pl_db.mos_list().at(config_list.at(j).pair_list.at(
//            config_list.at(j).num_finger - 1).nmos_idx).getDummyFlag())
//          v_special_mos_idx.push_back(config_list.at(j).pair_list.at(config_list.at(j).num_finger).nmos_idx);
//      }
//
//      auto should_do = gigaplace::Operator::getShouldDo(pl_db, config_list.at(i), config_list.at(j), v_special_mos_idx);
      auto should_do = gigaplace::Operator::shouldShare(pl_db,config_list.at(i),config_list.at(j));
      switch (should_do) {
        case COULD_NOT_SHARE:
        case CONFIG_HAD_BEEN_USED:break;
        case NO_FLIP: {
          PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                             config_list.at(j));
          config_list.push_back(temp);
          current_config_list_size = current_config_list_size + 1;
          break;
        }
        case CONFIGFLIP_C1_C2: {
          gigaplace::Operator::configFlip(pl_db, config_list.at(i));
          gigaplace::Operator::configFlip(pl_db, config_list.at(j));

          PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                             config_list.at(j));
          config_list.push_back(temp);
          current_config_list_size = current_config_list_size + 1;
          break;
        }
        case MOSFLIP_C1P: {
          gigaplace::Operator::mosFlip(pl_db, config_list.at(i).pair_list.at(0).pmos_idx);
          PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                             config_list.at(j));
          config_list.push_back(temp);
          current_config_list_size = current_config_list_size + 1;
          break;
        }
        case MOSFLIP_C1N: {
          gigaplace::Operator::mosFlip(pl_db, config_list.at(i).pair_list.at(0).nmos_idx);
          PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                             config_list.at(j));
          config_list.push_back(temp);
          current_config_list_size = current_config_list_size + 1;
          break;
        }
        case MOSFLIP_C2P: {
          gigaplace::Operator::mosFlip(pl_db, config_list.at(j).pair_list.at(0).pmos_idx);
          PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                             config_list.at(j));
          config_list.push_back(temp);
          current_config_list_size = current_config_list_size + 1;
          break;
        }
        case MOSFLIP_C2N: {
          gigaplace::Operator::mosFlip(pl_db, config_list.at(j).pair_list.at(0).nmos_idx);
          PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                             config_list.at(j));
          config_list.push_back(temp);
          current_config_list_size = current_config_list_size + 1;
          break;
        }
        case MOSFLIP_C1N_CONFIGFLIP_C2: {
          gigaplace::Operator::mosFlip(pl_db, config_list.at(i).pair_list.at(0).nmos_idx);
          gigaplace::Operator::configFlip(pl_db, config_list.at(j));
          PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                             config_list.at(j));
          config_list.push_back(temp);
          current_config_list_size = current_config_list_size + 1;
          break;
        }
        case MOSFLIP_C1P_CONFIGFLIP_C2: {
          gigaplace::Operator::mosFlip(pl_db, config_list.at(i).pair_list.at(0).pmos_idx);
          gigaplace::Operator::configFlip(pl_db, config_list.at(j));
          PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                             config_list.at(j));
          config_list.push_back(temp);
          current_config_list_size = current_config_list_size + 1;
          break;
        }
        case MOSFLIP_C2N_CONFIGFLIP_C1: {
          gigaplace::Operator::mosFlip(pl_db, config_list.at(j).pair_list.at(0).nmos_idx);
          gigaplace::Operator::configFlip(pl_db, config_list.at(i));
          PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                             config_list.at(j));
          config_list.push_back(temp);
          current_config_list_size = current_config_list_size + 1;
          break;
        }
        case MOSFLIP_C2P_CONFIGFLIP_C1: {
          gigaplace::Operator::mosFlip(pl_db, config_list.at(j).pair_list.at(0).pmos_idx);
          gigaplace::Operator::configFlip(pl_db, config_list.at(i));
          PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                             config_list.at(j));
          config_list.push_back(temp);
          current_config_list_size = current_config_list_size + 1;
          break;
        }
        case MOSFLIP_C1P_C2P: {
          gigaplace::Operator::mosFlip(pl_db, config_list.at(i).pair_list.at(0).pmos_idx);
          gigaplace::Operator::mosFlip(pl_db, config_list.at(j).pair_list.at(0).pmos_idx);
          PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                             config_list.at(j));
          config_list.push_back(temp);
          current_config_list_size = current_config_list_size + 1;
          break;
        }
        case CONFIGFLIP_C2: {
          gigaplace::Operator::configFlip(pl_db, config_list.at(j));
          PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                             config_list.at(j));
          config_list.push_back(temp);
          current_config_list_size = current_config_list_size + 1;
          break;
        }
        case MOSFLIP_C1N_C2N: {
          gigaplace::Operator::mosFlip(pl_db, config_list.at(i).pair_list.at(0).nmos_idx);
          gigaplace::Operator::mosFlip(pl_db, config_list.at(j).pair_list.at(0).nmos_idx);
          PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                             config_list.at(j));
          config_list.push_back(temp);
          current_config_list_size = current_config_list_size + 1;
          break;
        }
        case CONFIGFLIP_C1: {
          gigaplace::Operator::configFlip(pl_db, config_list.at(i));
          PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                             config_list.at(j));
          config_list.push_back(temp);
          current_config_list_size = current_config_list_size + 1;
          break;
        }
        case MOSFLIP_C1P_C2N: {
          gigaplace::Operator::mosFlip(pl_db, config_list.at(i).pair_list.at(0).pmos_idx);
          gigaplace::Operator::mosFlip(pl_db, config_list.at(j).pair_list.at(0).nmos_idx);
          PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                             config_list.at(j));
          config_list.push_back(temp);
          current_config_list_size = current_config_list_size + 1;
          break;
        }
        case MOSFLIP_C1N_C2P: {
          gigaplace::Operator::mosFlip(pl_db, config_list.at(i).pair_list.at(0).nmos_idx);
          gigaplace::Operator::mosFlip(pl_db, config_list.at(j).pair_list.at(0).pmos_idx);
          PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                             config_list.at(j));
          config_list.push_back(temp);
          current_config_list_size = current_config_list_size + 1;
          break;
        }
        default:break;
      }
      /*
//not all share_flag equal false
            if (should_do == CONFIG_HAD_BEEN_USED || should_do == COULD_NOT_SHARE)
                continue;
//flip 0
            else if (should_do == NO_FLIP) {
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;

            }
//flip 4
            else if (should_do == CONFIGFLIP_C1_C2) {
                gigaplace::Operator::configFlip(pl_db, config_list.at(i));
                gigaplace::Operator::configFlip(pl_db, config_list.at(j));

                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            }
//flip 1
            else if (should_do == MOSFLIP_C1P) {
                gigaplace::Operator::mosFlip(pl_db, config_list.at(i).pair_list.at(0).pmos_idx);
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            } else if (should_do == MOSFLIP_C1N) {
                gigaplace::Operator::mosFlip(pl_db, config_list.at(i).pair_list.at(0).nmos_idx);
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            } else if (should_do == MOSFLIP_C2P) {
                gigaplace::Operator::mosFlip(pl_db, config_list.at(j).pair_list.at(0).pmos_idx);
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            } else if (should_do == MOSFLIP_C2N) {
                gigaplace::Operator::mosFlip(pl_db, config_list.at(j).pair_list.at(0).nmos_idx);
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            }
//flip 3
            else if (should_do == MOSFLIP_C1N_CONFIGFLIP_C2) {
                gigaplace::Operator::mosFlip(pl_db, config_list.at(i).pair_list.at(0).nmos_idx);
                gigaplace::Operator::configFlip(pl_db, config_list.at(j));
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            } else if (should_do == MOSFLIP_C1P_CONFIGFLIP_C2) {
                gigaplace::Operator::mosFlip(pl_db, config_list.at(i).pair_list.at(0).pmos_idx);
                gigaplace::Operator::configFlip(pl_db, config_list.at(j));
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            } else if (should_do == MOSFLIP_C2N_CONFIGFLIP_C1) {
                gigaplace::Operator::mosFlip(pl_db, config_list.at(j).pair_list.at(0).nmos_idx);
                gigaplace::Operator::configFlip(pl_db, config_list.at(i));
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            } else if (should_do == MOSFLIP_C2P_CONFIGFLIP_C1) {
                gigaplace::Operator::mosFlip(pl_db, config_list.at(j).pair_list.at(0).pmos_idx);
                gigaplace::Operator::configFlip(pl_db, config_list.at(i));
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            }
//flip 2
            else if (should_do == MOSFLIP_C1P_C2P) {
                gigaplace::Operator::mosFlip(pl_db, config_list.at(i).pair_list.at(0).pmos_idx);
                gigaplace::Operator::mosFlip(pl_db, config_list.at(j).pair_list.at(0).pmos_idx);
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            } else if (should_do == CONFIGFLIP_C2) {
                gigaplace::Operator::configFlip(pl_db, config_list.at(j));
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            } else if (should_do == MOSFLIP_C1N_C2N) {
                gigaplace::Operator::mosFlip(pl_db, config_list.at(i).pair_list.at(0).nmos_idx);
                gigaplace::Operator::mosFlip(pl_db, config_list.at(j).pair_list.at(0).nmos_idx);
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            } else if (should_do == CONFIGFLIP_C1) {
                gigaplace::Operator::configFlip(pl_db, config_list.at(i));
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            } else if (should_do == MOSFLIP_C1P_C2N) {
                gigaplace::Operator::mosFlip(pl_db, config_list.at(i).pair_list.at(0).pmos_idx);
                gigaplace::Operator::mosFlip(pl_db, config_list.at(j).pair_list.at(0).nmos_idx);
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            } else if (should_do == MOSFLIP_C1N_C2P) {
                gigaplace::Operator::mosFlip(pl_db, config_list.at(i).pair_list.at(0).nmos_idx);
                gigaplace::Operator::mosFlip(pl_db, config_list.at(j).pair_list.at(0).pmos_idx);
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            }
            //pair and config

            //config and pair

            //two config
*/
    }
    if (!config_list.at(i).share_flag) {
      PlaceDB::Configuration temp = config_list.at(i);
      config_list.push_back(temp);
      config_list.at(i).share_flag = true;
      current_config_list_size = current_config_list_size + 1;
    }
  }
}

void gigaplace::Operator::addConfig(PlaceDB &pl_db,
                                    std::vector<PlaceDB::Configuration> &config_list,
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

  PlaceDB::Pair pair{};
  if (pl_db.mos_list().at(mos1_idx).getType() == 0) {
    pair.nmos_idx = mos1_idx;
    pair.pmos_idx = mos2_idx;
  } else {
    pair.nmos_idx = mos2_idx;
    pair.pmos_idx = mos1_idx;
  }
  PlaceDB::Configuration config{};
  config.pair_list.push_back(pair);
  config.left_net0 = pl_db.mos_list().at(pair.nmos_idx).getLeft();
  config.right_net0 = pl_db.mos_list().at(pair.nmos_idx).getRight();
  config.left_net1 = pl_db.mos_list().at(pair.pmos_idx).getLeft();
  config.right_net1 = pl_db.mos_list().at(pair.pmos_idx).getRight();
  config_list.push_back(config);
}

void gigaplace::Operator::configFlip(gigaplace::PlaceDB &pl_db, gigaplace::PlaceDB::Configuration &config) {
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

gigaplace::PlaceDB::Configuration gigaplace::Operator::creatTempConfig(gigaplace::PlaceDB &pl_db,
                                                                       gigaplace::PlaceDB::Configuration &c1,
                                                                       gigaplace::PlaceDB::Configuration &c2) {
  PlaceDB::Configuration temp{};
  for (auto &pair : c1.pair_list)
    temp.pair_list.push_back(pair);
  for (auto &pair : c2.pair_list)
    temp.pair_list.push_back(pair);
  temp.left_net0 = pl_db.mos_list().at(temp.pair_list.at(0).nmos_idx).getLeft();
  temp.left_net1 = pl_db.mos_list().at(temp.pair_list.at(0).pmos_idx).getLeft();
  temp.right_net0 = pl_db.mos_list().at(temp.pair_list.at(temp.pair_list.size() - 1).nmos_idx).getRight();
  temp.right_net1 = pl_db.mos_list().at(temp.pair_list.at(temp.pair_list.size() - 1).pmos_idx).getRight();
  temp.num_finger = c1.num_finger + c2.num_finger + 1;
  c1.share_flag = true;
  c2.share_flag = true;

  return temp;
}

void gigaplace::Operator::pairSingleMos(gigaplace::PlaceDB &pl_db) {
  for (auto &single_mos_idx : pl_db.single_mos_ids()) {
    Mos dummy{};
    Mos single{};
    PlaceDB::Pair pair{};
    single = pl_db.mos_list().at(single_mos_idx);
    PlaceDB::Configuration config{};
    if (single.getType() == 0)
      dummy.getType() = 1;
    else
      dummy.getType() = 0;

    dummy.getGate() = single.getGate();
    dummy.getDummyFlag() = true;
    dummy.getLeft() = "dummy";
    dummy.getRight() = "dummy";

    pl_db.mos_list().push_back(dummy);
    pl_db.mos_ids().push_back(pl_db.mos_list().size() - 1);
    auto dummy_idx = pl_db.mos_ids().at(pl_db.mos_ids().size() - 1);

    if (single.getType() == 0) {
      pair.nmos_idx = single_mos_idx;
      pair.pmos_idx = dummy_idx;
      config.pair_list.push_back(pair);
      config.left_net0 = pl_db.mos_list().at(single_mos_idx).getLeft();
      config.right_net0 = pl_db.mos_list().at(single_mos_idx).getRight();
      config.left_net1 = dummy.getLeft();
      config.right_net1 = dummy.getRight();
    } else {
      pair.nmos_idx = dummy_idx;
      pair.pmos_idx = single_mos_idx;
      config.pair_list.push_back(pair);
      config.left_net1 = pl_db.mos_list().at(single_mos_idx).getLeft();
      config.right_net1 = pl_db.mos_list().at(single_mos_idx).getRight();
      config.left_net0 = dummy.getLeft();
      config.right_net0 = dummy.getRight();
    }
    pl_db.v_config().push_back(config);
  }
}

void gigaplace::Operator::v_configTol_config(gigaplace::PlaceDB &pl_db) {
  for (auto &config : pl_db.v_config())
    pl_db.l_config().push_back(config);
}

void gigaplace::Operator::setCoordinates(gigaplace::PlaceDB &pl_db,
                                         std::list<PlaceDB::Configuration> &l_config) {
  float current_loc = 0;
  float half_unit = 0.5;
  for (auto &config : l_config) {
    config.config_loc = current_loc;
    for (auto &pair : config.pair_list) {
      pl_db.mos_list().at(pair.nmos_idx).getGateLoc() = current_loc;
      pl_db.mos_list().at(pair.pmos_idx).getGateLoc() = current_loc;
      pl_db.mos_list().at(pair.nmos_idx).getLeftLoc() = current_loc - half_unit;
      pl_db.mos_list().at(pair.pmos_idx).getLeftLoc() = current_loc - half_unit;
      pl_db.mos_list().at(pair.nmos_idx).getRightLoc() = current_loc + half_unit;
      pl_db.mos_list().at(pair.pmos_idx).getRightLoc() = current_loc + half_unit;

      current_loc += 1;
    }
    current_loc += 1;
  }
}

void gigaplace::Operator::createNewLayout(gigaplace::PlaceDB &pl_db, gigaplace::index &pair1, gigaplace::index &pair2) {
  gigaplace::Operator::splitConfig(pl_db, pair1);
  gigaplace::Operator::splitConfig(pl_db, pair2);
  gigaplace::Operator::swap(pl_db, pair1, pair2);
  int32_t find_config_idx = -1;
  for (auto &config : pl_db.l_config()) {
    find_config_idx++;
    if (config.pair_list.at(0).pair_idx == pair1)
      break;
  }
  auto left_of_begin = std::prev(pl_db.l_config().begin());
  auto it = pl_db.l_config().begin();
  std::advance(it, find_config_idx);
  auto leftIt = std::prev(it);
  auto rightIt = std::next(it);
//  if((leftIt != left_of_begin && (*leftIt).pair_list.at(0).pair_idx == pair2) || (rightIt != pl_db.l_config.end() && (*rightIt).pair_list.at(0).pair_idx == pair2)
  if (leftIt != left_of_begin) {
    if ((*leftIt).pair_list.at(0).pair_idx == pair2) {
      gigaplace::Operator::adjacentShareTwoSelectedPair(pl_db, pair1, pair2);
      return;
    }
  }
  if (rightIt != pl_db.l_config().end()) {
    if ((*rightIt).pair_list.at(0).pair_idx == pair2) {
      gigaplace::Operator::adjacentShareTwoSelectedPair(pl_db, pair1, pair2);
      return;
    }
  }
  gigaplace::Operator::adjacentShare(pl_db, pair1);
  gigaplace::Operator::adjacentShare(pl_db, pair2);//


}

void gigaplace::Operator::splitConfig(gigaplace::PlaceDB &pl_db, index &split_pair) {
  int32_t find_config_idx = -1;//in l_config
  int32_t find_pair_idx = -1;//in config--pair_list
  PlaceDB::Configuration find_config;
  bool find_flag = false;
  for (auto &config : pl_db.l_config()) {
    find_config_idx++;
    for (auto &pair : config.pair_list) {
      find_pair_idx++;
      if (pair.pair_idx == split_pair) {
        find_flag = true;
        find_config = config;
        break;
      }
    }

    if (find_flag)
      break;
    find_pair_idx = -1;
  }

  auto it = pl_db.l_config().begin();
  std::advance(it, find_config_idx + 1);
  if (find_config.num_finger == 0)
    return;
  if (find_pair_idx == 0) {
    PlaceDB::Configuration select_pair{};
    PlaceDB::Configuration select_right{};
    select_pair.pair_list.push_back(find_config.pair_list.at(find_pair_idx));
    select_pair.left_net0 = pl_db.mos_list().at(find_config.pair_list.at(find_pair_idx).nmos_idx).getLeft();
    select_pair.right_net0 = pl_db.mos_list().at(find_config.pair_list.at(find_pair_idx).nmos_idx).getRight();
    select_pair.left_net1 = pl_db.mos_list().at(find_config.pair_list.at(find_pair_idx).pmos_idx).getLeft();
    select_pair.right_net1 = pl_db.mos_list().at(find_config.pair_list.at(find_pair_idx).pmos_idx).getRight();
    for (auto i = find_pair_idx + 1; i < find_config.pair_list.size(); i++) {
      select_right.pair_list.push_back(find_config.pair_list.at(i));
      if (i == find_pair_idx + 1) {
        select_right.left_net0 = pl_db.mos_list().at(find_config.pair_list.at(i).nmos_idx).getLeft();
        select_right.left_net1 = pl_db.mos_list().at(find_config.pair_list.at(i).pmos_idx).getLeft();
      }
      if (i == find_config.pair_list.size() - 1) {
        select_right.right_net0 = pl_db.mos_list().at(find_config.pair_list.at(i).nmos_idx).getRight();
        select_right.right_net1 = pl_db.mos_list().at(find_config.pair_list.at(i).pmos_idx).getRight();
      }
      select_right.num_finger += 1;
    }
    select_right.num_finger = select_right.num_finger - 1;

    pl_db.l_config().insert(it, {select_pair, select_right});
    it = pl_db.l_config().begin();
    std::advance(it, find_config_idx);
    pl_db.l_config().erase(it);

  } else if (find_pair_idx == find_config.pair_list.size() - 1) {
    PlaceDB::Configuration select_pair{};
    PlaceDB::Configuration select_left{};
    select_pair.pair_list.push_back(find_config.pair_list.at(find_pair_idx));
    select_pair.left_net0 = pl_db.mos_list().at(find_config.pair_list.at(find_pair_idx).nmos_idx).getLeft();
    select_pair.right_net0 = pl_db.mos_list().at(find_config.pair_list.at(find_pair_idx).nmos_idx).getRight();
    select_pair.left_net1 = pl_db.mos_list().at(find_config.pair_list.at(find_pair_idx).pmos_idx).getLeft();
    select_pair.right_net1 = pl_db.mos_list().at(find_config.pair_list.at(find_pair_idx).pmos_idx).getRight();

    for (auto i = 0; i < find_config.pair_list.size() - 1; i++) {
      select_left.pair_list.push_back(find_config.pair_list.at(i));
      if (i == 0) {
        select_left.left_net0 = pl_db.mos_list().at(find_config.pair_list.at(i).nmos_idx).getLeft();
        select_left.left_net1 = pl_db.mos_list().at(find_config.pair_list.at(i).pmos_idx).getLeft();
      }
      if (i == find_config.pair_list.size() - 2) {
        select_left.right_net0 = pl_db.mos_list().at(find_config.pair_list.at(i).nmos_idx).getRight();
        select_left.right_net1 = pl_db.mos_list().at(find_config.pair_list.at(i).pmos_idx).getRight();
      }
      select_left.num_finger += 1;
    }
    select_left.num_finger = select_left.num_finger - 1;

    pl_db.l_config().insert(it, {select_left, select_pair});
    it = pl_db.l_config().begin();
    std::advance(it, find_config_idx);
    pl_db.l_config().erase(it);

  } else {
    PlaceDB::Configuration select_pair{};
    PlaceDB::Configuration select_left{};
    PlaceDB::Configuration select_right{};

    select_pair.pair_list.push_back(find_config.pair_list.at(find_pair_idx));
    select_pair.left_net0 = pl_db.mos_list().at(find_config.pair_list.at(find_pair_idx).nmos_idx).getLeft();
    select_pair.right_net0 = pl_db.mos_list().at(find_config.pair_list.at(find_pair_idx).nmos_idx).getRight();
    select_pair.left_net1 = pl_db.mos_list().at(find_config.pair_list.at(find_pair_idx).pmos_idx).getLeft();
    select_pair.right_net1 = pl_db.mos_list().at(find_config.pair_list.at(find_pair_idx).pmos_idx).getRight();

    for (auto i = find_pair_idx + 1; i < find_config.pair_list.size(); i++) {
      select_right.pair_list.push_back(find_config.pair_list.at(i));
      if (i == find_pair_idx + 1) {
        select_right.left_net0 = pl_db.mos_list().at(find_config.pair_list.at(i).nmos_idx).getLeft();
        select_right.left_net1 = pl_db.mos_list().at(find_config.pair_list.at(i).pmos_idx).getLeft();
      }
      if (i == find_config.pair_list.size() - 1) {
        select_right.right_net0 = pl_db.mos_list().at(find_config.pair_list.at(i).nmos_idx).getRight();
        select_right.right_net1 = pl_db.mos_list().at(find_config.pair_list.at(i).pmos_idx).getRight();
      }
      select_right.num_finger += 1;
    }
    select_right.num_finger = select_right.num_finger - 1;

    for (auto i = 0; i < find_pair_idx; i++) {
      select_left.pair_list.push_back(find_config.pair_list.at(i));
      if (i == 0) {
        select_left.left_net0 = pl_db.mos_list().at(find_config.pair_list.at(i).nmos_idx).getLeft();
        select_left.left_net1 = pl_db.mos_list().at(find_config.pair_list.at(i).pmos_idx).getLeft();
      }
      if (i == find_pair_idx - 1) {
        select_left.right_net0 = pl_db.mos_list().at(find_config.pair_list.at(i).nmos_idx).getRight();
        select_left.right_net1 = pl_db.mos_list().at(find_config.pair_list.at(i).pmos_idx).getRight();
      }
      select_left.num_finger += 1;
    }
    select_left.num_finger = select_left.num_finger - 1;

    pl_db.l_config().insert(it, {select_left, select_pair, select_right});
    it = pl_db.l_config().begin();
    std::advance(it, find_config_idx);
    pl_db.l_config().erase(it);
  }
}

void gigaplace::Operator::adjacentShare(gigaplace::PlaceDB &pl_db, gigaplace::index &pair) {
  std::vector<PlaceDB::Configuration> neighbors{};
  int32_t find_config_idx = -1;
  for (auto &config : pl_db.l_config()) {
    find_config_idx++;
    if (config.pair_list.at(0).pair_idx == pair)
      break;
  }
  auto left_of_begin = std::prev(pl_db.l_config().begin());
  auto it = pl_db.l_config().begin();
  std::advance(it, find_config_idx);

  //get left and right
  auto leftIt = std::prev(it);
  auto rightIt = std::next(it);

  if (leftIt != left_of_begin)
    neighbors.push_back(*leftIt);
  neighbors.push_back(*it);
  if (rightIt != pl_db.l_config().end())
    neighbors.push_back(*rightIt);
  gigaplace::Operator::share(pl_db, neighbors);
  if (rightIt != pl_db.l_config().end()) {
    auto insertHere = pl_db.l_config().begin();
    std::advance(insertHere, find_config_idx + 2);
    for (auto &config : neighbors) {
      if (!config.share_flag)
        pl_db.l_config().insert(insertHere, config);
    }
    pl_db.l_config().erase(rightIt);
    pl_db.l_config().erase(it);
    if (leftIt != left_of_begin)
      pl_db.l_config().erase(leftIt);

  } else {
    auto insertHere = pl_db.l_config().begin();
    std::advance(insertHere, find_config_idx + 1);
    for (auto &config : neighbors) {
      if (!config.share_flag)
        pl_db.l_config().insert(insertHere, config);
    }
    pl_db.l_config().erase(it);
    if (leftIt != left_of_begin)
      pl_db.l_config().erase(leftIt);
  }
}

void gigaplace::Operator::adjacentShareTwoSelectedPair(gigaplace::PlaceDB &pl_db, gigaplace::index &pair1,
                                                       gigaplace::index &pair2) {
  std::vector<PlaceDB::Configuration> neighbors{};
  int32_t find_config_idx1 = -1;
  int32_t find_config_idx2 = -1;
  for (auto &config : pl_db.l_config()) {
    find_config_idx1++;
    if (config.pair_list.at(0).pair_idx == pair1)
      break;
  }
  for (auto &config : pl_db.l_config()) {
    find_config_idx2++;
    if (config.pair_list.at(0).pair_idx == pair2)
      break;
  }
  auto it1 = pl_db.l_config().begin();
  auto it2 = pl_db.l_config().begin();
  std::advance(it1, find_config_idx1);
  std::advance(it2, find_config_idx2);
  auto leftIt1 = std::prev(it1);  //get left and right
  auto rightIt1 = std::next(it1);
  auto leftIt2 = std::prev(it2);
  auto rightIt2 = std::next(it2);

  auto left_of_begin = std::prev(pl_db.l_config().begin());

  if (leftIt1 != left_of_begin) {
    if ((*leftIt1).pair_list.at(0).pair_idx == pair2) { //p2 p1
      if (leftIt2 != left_of_begin)
        neighbors.push_back(*leftIt2);
      neighbors.push_back(*it2);
      neighbors.push_back(*it1);
      if (rightIt1 != pl_db.l_config().end())
        neighbors.push_back(*rightIt1);
      gigaplace::Operator::share(pl_db, neighbors);
      if (rightIt1 != pl_db.l_config().end()) {
        auto insertHere = pl_db.l_config().begin();
        std::advance(insertHere, find_config_idx1 + 2);
        for (auto &config : neighbors) {
          if (!config.share_flag)
            pl_db.l_config().insert(insertHere, config);
        }
        pl_db.l_config().erase(rightIt1);
        pl_db.l_config().erase(it1);
        pl_db.l_config().erase(it2);
        if (leftIt2 != left_of_begin)
          pl_db.l_config().erase(leftIt2);

      } else {
        auto insertHere = pl_db.l_config().begin();
        std::advance(insertHere, find_config_idx1 + 1);
        for (auto &config : neighbors) {
          if (!config.share_flag)
            pl_db.l_config().insert(insertHere, config);
        }
        pl_db.l_config().erase(it1);
        pl_db.l_config().erase(it2);
        if (leftIt2 != left_of_begin)
          pl_db.l_config().erase(leftIt2);
      }

      return;
    }
  }
  if (rightIt1 != pl_db.l_config().end()) {//p1 p2
    if ((*rightIt1).pair_list.at(0).pair_idx == pair2) {
      if (leftIt1 != left_of_begin)
        neighbors.push_back(*leftIt1);
      neighbors.push_back(*it1);
      neighbors.push_back(*it2);
      if (rightIt2 != pl_db.l_config().end())
        neighbors.push_back(*rightIt2);
      gigaplace::Operator::share(pl_db, neighbors);
      if (rightIt2 != pl_db.l_config().end()) {
        auto insertHere = pl_db.l_config().begin();
        std::advance(insertHere, find_config_idx2 + 2);
        for (auto &config : neighbors) {
          if (!config.share_flag)
            pl_db.l_config().insert(insertHere, config);
        }
        pl_db.l_config().erase(rightIt2);
        pl_db.l_config().erase(it2);
        pl_db.l_config().erase(it1);
        if (leftIt1 != left_of_begin)
          pl_db.l_config().erase(leftIt1);

      } else {
        auto insertHere = pl_db.l_config().begin();
        std::advance(insertHere, find_config_idx2 + 1);
        for (auto &config : neighbors) {
          if (!config.share_flag)
            pl_db.l_config().insert(insertHere, config);
        }
        pl_db.l_config().erase(it2);
        pl_db.l_config().erase(it1);
        if (leftIt1 != left_of_begin)
          pl_db.l_config().erase(leftIt1);
      }

    }
    return;
  }

}
int32_t gigaplace::Operator::getShouldDo(gigaplace::PlaceDB &pl_db,
                                         gigaplace::PlaceDB::Configuration &c1,
                                         gigaplace::PlaceDB::Configuration &c2,
                                         std::vector<index> &v_special_mos_ids) {
  auto should_do = gigaplace::Operator::shouldShare(pl_db, c1, c2);
  if (should_do == CONFIG_HAD_BEEN_USED)
    return should_do;
  if (should_do != COULD_NOT_SHARE)
    return should_do;
  auto status = v_special_mos_ids.size();

  if (status == 1) {
    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(0));
    should_do = gigaplace::Operator::shouldShare(pl_db, c1, c2);
    return should_do;
  }
  if (status == 2) {
    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(0));
    should_do = gigaplace::Operator::shouldShare(pl_db, c1, c2);
    if (should_do != COULD_NOT_SHARE)
      return should_do;
    else
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(0));//rollback

    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(1));
    should_do = gigaplace::Operator::shouldShare(pl_db, c1, c2);
    if (should_do != COULD_NOT_SHARE)
      return should_do;
    else
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(1));

    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(0));
    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(1));
    should_do = gigaplace::Operator::shouldShare(pl_db, c1, c2);
    return should_do;
  }
  if (status == 3) {
    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(0));
    should_do = gigaplace::Operator::shouldShare(pl_db, c1, c2);
    if (should_do != COULD_NOT_SHARE)
      return should_do;
    else
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(0));

    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(1));
    should_do = gigaplace::Operator::shouldShare(pl_db, c1, c2);
    if (should_do != COULD_NOT_SHARE)
      return should_do;
    else
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(1));

    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(2));
    should_do = gigaplace::Operator::shouldShare(pl_db, c1, c2);
    if (should_do != COULD_NOT_SHARE)
      return should_do;
    else
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(2));

    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(0));
    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(1));
    should_do = gigaplace::Operator::shouldShare(pl_db, c1, c2);
    if (should_do != COULD_NOT_SHARE)
      return should_do;
    else {
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(0));
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(1));
    }

    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(0));
    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(2));
    should_do = gigaplace::Operator::shouldShare(pl_db, c1, c2);
    if (should_do != COULD_NOT_SHARE)
      return should_do;
    else {
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(0));
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(2));
    }

    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(1));
    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(2));
    should_do = gigaplace::Operator::shouldShare(pl_db, c1, c2);
    if (should_do != COULD_NOT_SHARE)
      return should_do;
    else {
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(1));
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(2));
    }

    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(0));
    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(1));
    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(2));
    should_do = gigaplace::Operator::shouldShare(pl_db, c1, c2);
    return should_do;
  }

  if (status == 4) {
    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(0));
    should_do = gigaplace::Operator::shouldShare(pl_db, c1, c2);
    if (should_do != COULD_NOT_SHARE)
      return should_do;
    else
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(0));

    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(1));
    should_do = gigaplace::Operator::shouldShare(pl_db, c1, c2);
    if (should_do != COULD_NOT_SHARE)
      return should_do;
    else
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(1));

    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(2));
    should_do = gigaplace::Operator::shouldShare(pl_db, c1, c2);
    if (should_do != COULD_NOT_SHARE)
      return should_do;
    else
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(2));

    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(3));
    should_do = gigaplace::Operator::shouldShare(pl_db, c1, c2);
    if (should_do != COULD_NOT_SHARE)
      return should_do;
    else
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(3));

    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(0));
    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(1));
    should_do = gigaplace::Operator::shouldShare(pl_db, c1, c2);
    if (should_do != COULD_NOT_SHARE)
      return should_do;
    else {
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(0));
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(1));
    }

    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(0));
    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(2));
    should_do = gigaplace::Operator::shouldShare(pl_db, c1, c2);
    if (should_do != COULD_NOT_SHARE)
      return should_do;
    else {
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(0));
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(2));
    }

    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(0));
    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(3));
    should_do = gigaplace::Operator::shouldShare(pl_db, c1, c2);
    if (should_do != COULD_NOT_SHARE)
      return should_do;
    else {
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(0));
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(3));
    }

    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(1));
    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(2));
    should_do = gigaplace::Operator::shouldShare(pl_db, c1, c2);
    if (should_do != COULD_NOT_SHARE)
      return should_do;
    else {
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(1));
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(2));
    }

    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(1));
    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(3));
    should_do = gigaplace::Operator::shouldShare(pl_db, c1, c2);
    if (should_do != COULD_NOT_SHARE)
      return should_do;
    else {
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(1));
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(3));
    }

    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(2));
    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(3));
    should_do = gigaplace::Operator::shouldShare(pl_db, c1, c2);
    if (should_do != COULD_NOT_SHARE)
      return should_do;
    else {
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(2));
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(3));
    }

    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(0));
    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(1));
    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(2));
    should_do = gigaplace::Operator::shouldShare(pl_db, c1, c2);
    if (should_do != COULD_NOT_SHARE)
      return should_do;
    else {
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(0));
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(1));
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(2));
    }

    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(0));
    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(1));
    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(3));
    should_do = gigaplace::Operator::shouldShare(pl_db, c1, c2);
    if (should_do != COULD_NOT_SHARE)
      return should_do;
    else {
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(0));
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(1));
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(3));
    }

    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(0));
    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(2));
    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(3));
    should_do = gigaplace::Operator::shouldShare(pl_db, c1, c2);
    if (should_do != COULD_NOT_SHARE)
      return should_do;
    else {
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(0));
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(2));
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(3));
    }

    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(1));
    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(2));
    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(3));
    should_do = gigaplace::Operator::shouldShare(pl_db, c1, c2);
    if (should_do != COULD_NOT_SHARE)
      return should_do;
    else {
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(1));
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(2));
      gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(3));
    }

    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(0));
    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(1));
    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(2));
    gigaplace::Operator::mosFlip(pl_db, v_special_mos_ids.at(3));
    should_do = gigaplace::Operator::shouldShare(pl_db, c1, c2);
    return should_do;
  }

  return should_do;
}
