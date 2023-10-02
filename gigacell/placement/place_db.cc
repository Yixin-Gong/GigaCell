//
// Created by eric on 23-9-15.
//

#include "place_db.h"

void gigaplace::PlaceDB::init() {
  Net2Mos net2mos{};
  std::vector<Net2Mos> net{};
  index idx = 0;
  gigaplace::Operator::fold(db_);
  for (auto &kNMOS : db_.nmos_list()) {
    net2mos.idx = idx;
  //  net2mos.type = 0;

    if (nets_.find(kNMOS.getRight()) == nets_.end() && kNMOS.getRight() != "VSS" && kNMOS.getRight() != "VDD") {
      nets_.emplace(kNMOS.getRight(), net);
      net2mos.electrode_name = "right";
      nets_.find(kNMOS.getRight())->second.emplace_back(net2mos);
    } else if (nets_.find(kNMOS.getRight()) != nets_.end() && kNMOS.getRight() != "VSS" && kNMOS.getRight() != "VDD") {
      net2mos.electrode_name = "right";
      nets_.find(kNMOS.getRight())->second.emplace_back(net2mos);
    }
    if (nets_.find(kNMOS.getGate()) == nets_.end() && kNMOS.getGate() != "VSS" && kNMOS.getGate() != "VDD") {
      nets_.emplace(kNMOS.getGate(), net);
      net2mos.electrode_name = "gate";
      nets_.find(kNMOS.getGate())->second.emplace_back(net2mos);
    } else if (nets_.find(kNMOS.getGate()) != nets_.end() && kNMOS.getGate() != "VSS" && kNMOS.getGate() != "VDD") {
      net2mos.electrode_name = "gate";
      nets_.find(kNMOS.getGate())->second.emplace_back(net2mos);
    }
    if (nets_.find(kNMOS.getLeft()) == nets_.end() && kNMOS.getLeft() != "VSS" && kNMOS.getLeft() != "VDD") {
      nets_.emplace(kNMOS.getLeft(), net);
      net2mos.electrode_name = "left";
      nets_.find(kNMOS.getLeft())->second.emplace_back(net2mos);
    } else if (nets_.find(kNMOS.getLeft()) != nets_.end() && kNMOS.getLeft() != "VSS"
        && kNMOS.getLeft() != "VDD") {
      net2mos.electrode_name = "left";
      nets_.find(kNMOS.getLeft())->second.emplace_back(net2mos);
    }
    idx++;
  }
  idx = nmos_list().size();
  for (auto &kPMOS : db_.pmos_list()) {
    net2mos.idx = idx;
   // net2mos.type = 1;
    if (nets_.find(kPMOS.getRight()) == nets_.end() && kPMOS.getRight() != "VSS" && kPMOS.getRight() != "VDD") {
      nets_.emplace(kPMOS.getRight(), net);
      net2mos.electrode_name = "right";
      nets_.find(kPMOS.getRight())->second.emplace_back(net2mos);
    } else if (nets_.find(kPMOS.getRight()) != nets_.end() && kPMOS.getRight() != "VSS" && kPMOS.getRight() != "VDD") {
      net2mos.electrode_name = "right";
      nets_.find(kPMOS.getRight())->second.emplace_back(net2mos);
    }
    if (nets_.find(kPMOS.getGate()) == nets_.end() && kPMOS.getGate() != "VSS" && kPMOS.getGate() != "VDD") {
      nets_.emplace(kPMOS.getGate(), net);
      net2mos.electrode_name = "gate";
      nets_.find(kPMOS.getGate())->second.emplace_back(net2mos);
    } else if (nets_.find(kPMOS.getGate()) != nets_.end() && kPMOS.getGate() != "VSS" && kPMOS.getGate() != "VDD") {
      net2mos.electrode_name = "gate";
      nets_.find(kPMOS.getGate())->second.emplace_back(net2mos);
    }
    if (nets_.find(kPMOS.getLeft()) == nets_.end() && kPMOS.getLeft() != "VSS" && kPMOS.getLeft() != "VDD") {
      nets_.emplace(kPMOS.getLeft(), net);
      net2mos.electrode_name = "left";
      nets_.find(kPMOS.getLeft())->second.emplace_back(net2mos);
    } else if (nets_.find(kPMOS.getLeft()) != nets_.end() && kPMOS.getLeft() != "VSS"
        && kPMOS.getLeft() != "VDD") {
      net2mos.electrode_name = "left";
      nets_.find(kPMOS.getLeft())->second.emplace_back(net2mos);
    }
    idx++;
  }
  idx = 0;
  for (Mos &kNMOS : db_.nmos_list()) {
    nmos_list().push_back(kNMOS);
    nmos_ids().push_back(idx);

    mos_list().push_back(kNMOS);
    mos_ids().push_back(idx);
    idx++;
  }
  idx = 0;
  for (Mos &kPMOS : db_.pmos_list()) {
    pmos_list().push_back(kPMOS);
    pmos_ids().push_back(idx);

    mos_list().push_back(kPMOS);
    mos_ids().push_back(idx + nmos_list().size());
    idx++;
  }
}



