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
    net2mos.type = 0;

    if (nets_.find(kNMOS.getDrain()) == nets_.end() && kNMOS.getDrain() != "VSS" && kNMOS.getDrain() != "VDD") {
      nets_.emplace(kNMOS.getDrain(), net);
      net2mos.electrode_name = "drain";
      nets_.find(kNMOS.getDrain())->second.emplace_back(net2mos);
    } else if (nets_.find(kNMOS.getDrain()) != nets_.end() && kNMOS.getDrain() != "VSS" && kNMOS.getDrain() != "VDD") {
      net2mos.electrode_name = "drain";
      nets_.find(kNMOS.getDrain())->second.emplace_back(net2mos);
    }
    if (nets_.find(kNMOS.getGate()) == nets_.end() && kNMOS.getGate() != "VSS" && kNMOS.getGate() != "VDD") {
      nets_.emplace(kNMOS.getGate(), net);
      net2mos.electrode_name = "gate";
      nets_.find(kNMOS.getGate())->second.emplace_back(net2mos);
    } else if (nets_.find(kNMOS.getGate()) != nets_.end() && kNMOS.getGate() != "VSS" && kNMOS.getGate() != "VDD") {
      net2mos.electrode_name = "gate";
      nets_.find(kNMOS.getGate())->second.emplace_back(net2mos);
    }
    if (nets_.find(kNMOS.getSource()) == nets_.end() && kNMOS.getSource() != "VSS" && kNMOS.getSource() != "VDD") {
      nets_.emplace(kNMOS.getSource(), net);
      net2mos.electrode_name = "source";
      nets_.find(kNMOS.getSource())->second.emplace_back(net2mos);
    } else if (nets_.find(kNMOS.getSource()) != nets_.end() && kNMOS.getSource() != "VSS"
        && kNMOS.getSource() != "VDD") {
      net2mos.electrode_name = "source";
      nets_.find(kNMOS.getSource())->second.emplace_back(net2mos);
    }
    idx++;
  }
  idx = 0;
  for (auto &kPMOS : db_.pmos_list()) {
    net2mos.idx = idx;
    net2mos.type = 1;
    if (nets_.find(kPMOS.getDrain()) == nets_.end() && kPMOS.getDrain() != "VSS" && kPMOS.getDrain() != "VDD") {
      nets_.emplace(kPMOS.getDrain(), net);
      net2mos.electrode_name = "drain";
      nets_.find(kPMOS.getDrain())->second.emplace_back(net2mos);
    } else if (nets_.find(kPMOS.getDrain()) != nets_.end() && kPMOS.getDrain() != "VSS" && kPMOS.getDrain() != "VDD") {
      net2mos.electrode_name = "drain";
      nets_.find(kPMOS.getDrain())->second.emplace_back(net2mos);
    }
    if (nets_.find(kPMOS.getGate()) == nets_.end() && kPMOS.getGate() != "VSS" && kPMOS.getGate() != "VDD") {
      nets_.emplace(kPMOS.getGate(), net);
      net2mos.electrode_name = "gate";
      nets_.find(kPMOS.getGate())->second.emplace_back(net2mos);
    } else if (nets_.find(kPMOS.getGate()) != nets_.end() && kPMOS.getGate() != "VSS" && kPMOS.getGate() != "VDD") {
      net2mos.electrode_name = "gate";
      nets_.find(kPMOS.getGate())->second.emplace_back(net2mos);
    }
    if (nets_.find(kPMOS.getSource()) == nets_.end() && kPMOS.getSource() != "VSS" && kPMOS.getSource() != "VDD") {
      nets_.emplace(kPMOS.getSource(), net);
      net2mos.electrode_name = "source";
      nets_.find(kPMOS.getSource())->second.emplace_back(net2mos);
    } else if (nets_.find(kPMOS.getSource()) != nets_.end() && kPMOS.getSource() != "VSS"
        && kPMOS.getSource() != "VDD") {
      net2mos.electrode_name = "source";
      nets_.find(kPMOS.getSource())->second.emplace_back(net2mos);
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



