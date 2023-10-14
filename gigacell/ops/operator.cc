//
// Created by eric on 23-9-21.
//


#include "operator.h"

void gigaplace::Operator::mosFlip(PlaceDB &pl_db, index &mos_idx) {
    if (pl_db.mos_list().at(mos_idx).getDummyFlag())
        return;

    if (pl_db.mos_list().at(mos_idx).getLeft() != "VDD" && pl_db.mos_list().at(mos_idx).getLeft() != "VSS") {
        for (auto &kMOS: pl_db.nets().find(pl_db.mos_list().at(mos_idx).getLeft())->second) {
            if (kMOS.idx == mos_idx)
                kMOS.electrode_name = "right";
        }
    }
    if (pl_db.mos_list().at(mos_idx).getRight() != "VDD" && pl_db.mos_list().at(mos_idx).getRight() != "VSS") {
        for (auto &kMOS: pl_db.nets().find(pl_db.mos_list().at(mos_idx).getRight())->second) {
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

std::string gigaplace::Operator::shouldShare(PlaceDB &pl_db, PlaceDB::Configuration &c1, PlaceDB::Configuration &c2) {
    if (c1.share_flag || c2.share_flag)
        return "1/2 config had been used";
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
        if (c1.left_net1 == c2.right_net1 && c1.right_net0 == c2.left_net0)
            return "mosFlip c1_1 c2_1";
        if (c1.right_net1 == c2.right_net1 && c1.right_net0 == c2.right_net1)
            return "configFlip c2";
        if (c1.right_net1 == c2.left_net1 && c1.left_net0 == c2.right_net0)
            return " mosFlip c1_0 c2_0";
        if (c1.left_net1 == c2.left_net1 && c1.left_net0 == c2.left_net0)
            return "configFlip c1";
        if (c1.left_net1 == c2.left_net1 && c1.right_net0 == c2.right_net0)
            return "mosFlip c1_1 c2_0";
        if (c1.right_net1 == c2.right_net1 && c1.left_net0 == c2.left_net0)
            return "mosFlip c1_0 c2_1";
    }

    //one pair one config
    if (c1.num_finger == 0 && c2.num_finger != 0) {
        if (c1.right_net1 == c2.left_net1 && c1.right_net0 == c2.left_net0)
            return "do without Flip";
        if (c1.left_net1 == c2.left_net1 && c1.right_net0 == c2.left_net0)
            return "mosFlip c1_1";
        if (c1.right_net1 == c2.left_net1 && c1.left_net0 == c2.left_net0)
            return "mosFlip c1_0";
        if (c1.left_net1 == c2.left_net1 && c1.left_net0 == c2.left_net0)
            return "configFlip c1";
        if (c1.right_net1 == c2.right_net1 && c1.right_net0 == c2.right_net0)
            return "configFlip c2";
        if (c1.left_net1 == c2.right_net1 && c1.right_net0 == c2.right_net0)
            return "mosFlip c1_1 configFlip c2";
        if (c1.right_net1 == c2.right_net1 && c1.left_net0 == c2.right_net0)
            return "mosFlip c1_0 configFlip c2";
        if (c1.left_net1 == c2.right_net1 && c1.left_net0 == c2.right_net0)
            return "configFlip c1 c2";
    }
    if (c1.num_finger != 0 && c2.num_finger == 0) {
        if (c1.right_net1 == c2.left_net1 && c1.right_net0 == c2.left_net0)
            return "do without Flip";
        if (c1.right_net1 == c2.right_net1 && c1.right_net0 == c2.left_net0)
            return "mosFlip c2_1";
        if (c1.right_net1 == c2.left_net1 && c1.right_net0 == c2.right_net0)
            return "mosFlip c2_0";
        if (c1.right_net1 == c2.right_net1 && c1.right_net0 == c2.right_net0)
            return "configFlip c2";
        if (c1.left_net1 == c2.left_net1 && c1.left_net0 == c2.left_net0)
            return "configFlip c1";
        if (c1.left_net1 == c2.right_net1 && c1.left_net0 == c2.left_net0)
            return "mosFlip c2_1 configFlip c1";
        if (c1.left_net1 == c2.left_net1 && c1.left_net0 == c2.right_net0)
            return "mosFlip c2_0 configFlip c1";
        if (c1.left_net1 == c2.right_net1 && c1.left_net0 == c2.right_net0)
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

void gigaplace::Operator::share(PlaceDB &pl_db, std::vector<PlaceDB::Configuration> &config_list) {
    index primary_config_list_size, current_config_list_size;
    primary_config_list_size = config_list.size();
    current_config_list_size = config_list.size();

    for (auto i = 0; i < primary_config_list_size; i++) {
        for (auto j = i + 1; j < current_config_list_size; j++) {
            auto should_do = gigaplace::Operator::shouldShare(pl_db, config_list.at(i), config_list.at(j));
//not all share_flag equal false
            if (should_do == "1/2 config had been used" || should_do == "could not share")
                continue;
//flip 0
            if (should_do == "do without Flip") {
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            }
//flip 4
            if (should_do == "mosFlip c1_0_1 c2_0_1") {
                gigaplace::Operator::mosFlip(pl_db, config_list.at(i).pair_list.at(0).nmos_idx);
                gigaplace::Operator::mosFlip(pl_db, config_list.at(i).pair_list.at(0).pmos_idx);
                gigaplace::Operator::mosFlip(pl_db, config_list.at(j).pair_list.at(0).nmos_idx);
                gigaplace::Operator::mosFlip(pl_db, config_list.at(j).pair_list.at(0).pmos_idx);
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            }
//flip 1
            if (should_do == "mosFlip c1_1") {
                gigaplace::Operator::mosFlip(pl_db, config_list.at(i).pair_list.at(0).pmos_idx);
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            }
            if (should_do == "mosFlip c1_0") {
                gigaplace::Operator::mosFlip(pl_db, config_list.at(i).pair_list.at(0).nmos_idx);
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            }
            if (should_do == "mosFlip c2_1") {
                gigaplace::Operator::mosFlip(pl_db, config_list.at(j).pair_list.at(0).pmos_idx);
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            }
            if (should_do == "mosFlip c2_0") {
                gigaplace::Operator::mosFlip(pl_db, config_list.at(j).pair_list.at(0).nmos_idx);
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            }
//flip 3
            if (should_do == "mosFlip c1_0 configFlip c2") {
                gigaplace::Operator::mosFlip(pl_db, config_list.at(i).pair_list.at(0).nmos_idx);
                gigaplace::Operator::configFlip(pl_db, config_list.at(j));
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            }
            if (should_do == "mosFlip c1_1 configFlip c2") {
                gigaplace::Operator::mosFlip(pl_db, config_list.at(i).pair_list.at(0).pmos_idx);
                gigaplace::Operator::configFlip(pl_db, config_list.at(j));
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            }
            if (should_do == "mosFlip c2_0 configFlip c1") {
                gigaplace::Operator::mosFlip(pl_db, config_list.at(j).pair_list.at(0).nmos_idx);
                gigaplace::Operator::configFlip(pl_db, config_list.at(i));
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            }
            if (should_do == "mosFlip c2_1 configFlip c1") {
                gigaplace::Operator::mosFlip(pl_db, config_list.at(j).pair_list.at(0).pmos_idx);
                gigaplace::Operator::configFlip(pl_db, config_list.at(i));
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            }
//flip 2
            if (should_do == "mosFlip c1_1 c2_1") {
                gigaplace::Operator::mosFlip(pl_db, config_list.at(i).pair_list.at(0).pmos_idx);
                gigaplace::Operator::mosFlip(pl_db, config_list.at(j).pair_list.at(0).pmos_idx);
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            }
            if (should_do == "configFlip c2") {
                gigaplace::Operator::configFlip(pl_db, config_list.at(j));
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            }
            if (should_do == "mosFlip c1_0 c2_0") {
                gigaplace::Operator::mosFlip(pl_db, config_list.at(i).pair_list.at(0).nmos_idx);
                gigaplace::Operator::mosFlip(pl_db, config_list.at(j).pair_list.at(0).nmos_idx);
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            }
            if (should_do == "configFlip c1") {
                gigaplace::Operator::configFlip(pl_db, config_list.at(i));
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            }
            if (should_do == "mosFlip c1_1 c2_0") {
                gigaplace::Operator::mosFlip(pl_db, config_list.at(i).pair_list.at(0).pmos_idx);
                gigaplace::Operator::mosFlip(pl_db, config_list.at(j).pair_list.at(0).nmos_idx);
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            }
            if (should_do == "mosFLip c1_0 c2_1") {
                gigaplace::Operator::mosFlip(pl_db, config_list.at(i).pair_list.at(0).nmos_idx);
                gigaplace::Operator::mosFlip(pl_db, config_list.at(j).pair_list.at(0).pmos_idx);
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            }
            //pair and config
            if (should_do == "configFlip c1 c2") {
                gigaplace::Operator::configFlip(pl_db, config_list.at(i));
                gigaplace::Operator::configFlip(pl_db, config_list.at(j));
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            }
            //config and pair
            if (should_do == "configFlip c1") {
                gigaplace::Operator::configFlip(pl_db, config_list.at(i));
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            }
            //two config
            if (should_do == "configFlip c1 ") {
                gigaplace::Operator::configFlip(pl_db, config_list.at(i));
                PlaceDB::Configuration temp = gigaplace::Operator::creatTempConfig(pl_db, config_list.at(i),
                                                                                   config_list.at(j));
                config_list.push_back(temp);
                current_config_list_size = current_config_list_size + 1;
            }
        }
        if (!config_list.at(i).share_flag) {
            PlaceDB::Configuration temp = config_list.at(i);
            config_list.push_back(temp);
            config_list.at(i).share_flag = true;
            current_config_list_size = current_config_list_size + 1;
        }
    }

    for (auto &config: config_list) {
        if (!config.share_flag)
            pl_db.v_config().push_back(config);
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

void gigaplace::Operator::createDummy(PlaceDB &pl_db, PlaceDB::Configuration &config_pair, index &single_idx) {
    Mos dummy{};
    Mos single{};
    PlaceDB::Configuration config{};
    single = pl_db.mos_list().at(single_idx);
    PlaceDB::Pair pair{};

    if (single.getType() == 0) {
        dummy.getType() = 1;
        dummy.getLeft() = pl_db.mos_list().at(config_pair.pair_list.at(0).pmos_idx).getLeft();
        dummy.getRight() = pl_db.mos_list().at(config_pair.pair_list.at(0).pmos_idx).getRight();
    } else {
        dummy.getType() = 0;
        dummy.getLeft() = pl_db.mos_list().at(config_pair.pair_list.at(0).nmos_idx).getLeft();
        dummy.getRight() = pl_db.mos_list().at(config_pair.pair_list.at(0).nmos_idx).getRight();
    }

    //create dummy
    dummy.getGate() = single.getGate();
    dummy.getDummyFlag() = true;
    std::string dummy_name;
    dummy.getMosName() = dummy_name;
    pl_db.mos_list().push_back(dummy);
    pl_db.mos_ids().push_back(pl_db.mos_list().size() - 1);
    auto dummy_idx = pl_db.mos_ids().at(pl_db.mos_ids().size() - 1);
//auto dummy_idx = pl_db.mos_list().size()-1;

    //create config
    if (single.getType() == 0) {
        pair.nmos_idx=single_idx;
        pair.pmos_idx=dummy_idx;
        config.pair_list.push_back(pair);
        config.left_net0 = pl_db.mos_list().at(single_idx).getLeft();
        config.right_net0 = pl_db.mos_list().at(single_idx).getRight();
        config.left_net1 = pl_db.mos_list().at(config_pair.pair_list.at(0).pmos_idx).getLeft();
        config.right_net1 = pl_db.mos_list().at(config_pair.pair_list.at(0).pmos_idx).getRight();
    } else {
        pair.nmos_idx=dummy_idx;
        pair.pmos_idx=single_idx;
        config.pair_list.push_back(pair);
        config.left_net0 = pl_db.mos_list().at(config_pair.pair_list.at(0).nmos_idx).getLeft();
        config.right_net0 = pl_db.mos_list().at(config_pair.pair_list.at(0).nmos_idx).getRight();
        config.left_net1 = pl_db.mos_list().at(single_idx).getLeft();
        config.right_net1 = pl_db.mos_list().at(single_idx).getRight();
    }
    pl_db.v_config().push_back(config);
}
void gigaplace::Operator::configFlip(gigaplace::PlaceDB &pl_db, gigaplace::PlaceDB::Configuration &config) {
    std::reverse(config.pair_list.begin(), config.pair_list.end());
    for (auto &pair: config.pair_list) {
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
    for (auto &pair: c1.pair_list)
        temp.pair_list.push_back(pair);
    for (auto &pair: c2.pair_list)
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
    auto pair_flag = false;
    for (auto &single_mos_idx: pl_db.single_mos_ids()) {
        if (!pl_db.mos_list().at(single_mos_idx).getType()) {
            for (auto &pair: pl_db.pair_list()) {
                auto same_gate = pl_db.mos_list().at(single_mos_idx).getGate() ==
                                 pl_db.mos_list().at(pair.pair_list.at(0).nmos_idx).getGate();
                auto can_share = pl_db.mos_list().at(single_mos_idx).getLeft() == pair.left_net0 ||
                                 pl_db.mos_list().at(single_mos_idx).getLeft() == pair.right_net0 ||
                                 pl_db.mos_list().at(single_mos_idx).getRight() == pair.left_net0 ||
                                 pl_db.mos_list().at(single_mos_idx).getRight() == pair.right_net0;
                if (same_gate && can_share) {
                    gigaplace::Operator::createDummy(pl_db, pair, single_mos_idx);
                    pair_flag = true;
                    break;
                }
            }

            for (auto &pair: pl_db.pair_list()) {
                if (pair_flag)
                    break;
                auto can_share = pl_db.mos_list().at(single_mos_idx).getLeft() == pair.left_net0 ||
                                 pl_db.mos_list().at(single_mos_idx).getLeft() == pair.right_net0 ||
                                 pl_db.mos_list().at(single_mos_idx).getRight() == pair.left_net0 ||
                                 pl_db.mos_list().at(single_mos_idx).getRight() == pair.right_net0;
                if (can_share) {
                    gigaplace::Operator::createDummy(pl_db,pair,single_mos_idx);
                    pair_flag = true;
                    break;
                }

            }
            for (auto &pair: pl_db.pair_list()) {
                if (pair_flag)
                    break;
                auto same_gate =pl_db.mos_list().at(single_mos_idx).getGate() ==
                                pl_db.mos_list().at(pair.pair_list.at(0).nmos_idx).getGate();
                if (same_gate) {
                    gigaplace::Operator::createDummy(pl_db,pair,single_mos_idx);
                    pair_flag = true;
                    break;
                }


            }
        } else {
            for (auto &pair: pl_db.pair_list()) {
                auto same_gate = pl_db.mos_list().at(single_mos_idx).getGate() ==
                                 pl_db.mos_list().at(pair.pair_list.at(0).pmos_idx).getGate();
                auto can_share = pl_db.mos_list().at(single_mos_idx).getLeft() == pair.left_net1 ||
                                     pl_db.mos_list().at(single_mos_idx).getLeft() == pair.right_net1 ||
                                     pl_db.mos_list().at(single_mos_idx).getRight() == pair.left_net1 ||
                                     pl_db.mos_list().at(single_mos_idx).getRight() == pair.right_net1;
                if (same_gate && can_share) {
                    gigaplace::Operator::createDummy(pl_db,pair,single_mos_idx);
                    pair_flag = true;
                    break;
                }
            }
            for (auto &pair: pl_db.pair_list()) {
                if (pair_flag)
                    break;
                auto can_share = pl_db.mos_list().at(single_mos_idx).getLeft() == pair.left_net1 ||
                                 pl_db.mos_list().at(single_mos_idx).getLeft() == pair.right_net1 ||
                                 pl_db.mos_list().at(single_mos_idx).getRight() == pair.left_net1 ||
                                 pl_db.mos_list().at(single_mos_idx).getRight() == pair.right_net1;
                if (can_share) {
                    gigaplace::Operator::createDummy(pl_db,pair,single_mos_idx);
                    pair_flag = true;
                    break;
                }

            }
            for (auto &pair: pl_db.pair_list()) {
                if (pair_flag)
                    break;
                auto same_gate = pl_db.mos_list().at(single_mos_idx).getGate() ==
                                 pl_db.mos_list().at(pair.pair_list.at(0).pmos_idx).getGate();
                if (same_gate) {
                    gigaplace::Operator::createDummy(pl_db,pair,single_mos_idx);
                    pair_flag = true;
                    break;
                }
            }
        }
        pair_flag = false;
    }
}
