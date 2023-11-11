//
// Created by eric on 23-9-15.
//
#include "place_db.h"

void gigaplace::PlaceDB::init() {
  Net2Mos net2mos{};
  std::vector<Net2Mos> net{};
  index idx = 0;
  fold(db_);
  for (auto &kNMOS : db_.nmos_list()) {
    net2mos.idx = idx;

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
  for (auto &kPMOS : db_.pmos_list()) {
    net2mos.idx = idx;
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
  for (auto &pin : db_.v_pin_list())
    v_pin().push_back(pin);

}
void gigaplace::PlaceDB::fold(gigaplace::DataBase &db) {
  int32_t idx = -1;
  DataBase db1 = db;
  for (auto &nmos : db1.nmos_list()) {
    idx++;
    if (nmos.getWidth() < 220) {
      continue;
    }
    index n;
    n = std::ceil(nmos.getWidth() / 220);
    nmos.getWidth() = (float) std::round((nmos.getWidth() / (float) n) * 100) / 100;
    if ((int) nmos.getWidth() == nmos.getWidth())
      db.nmos_list().at(idx).getWidth() = nmos.getWidth();
    else {
      if (idx == 0)
        db.nmos_list().at(idx).getWidth() = nmos.getWidth() + (float) 0.5;
      else
        db.nmos_list().at(idx).getWidth() = nmos.getWidth() - (float) 0.5;
    }
    for (index i = 1; i < n; i++) {
      Mos new_mos;
      new_mos.getType() = 0;

      std::string name;
      std::string mos_name = nmos.getMosName();

      name.append(mos_name + "_finger_" + std::to_string(i));

      new_mos.getMosName() = name;
      new_mos.getLeft() = nmos.getLeft();
      new_mos.getGate() = nmos.getGate();
      new_mos.getRight() = nmos.getRight();
      //width is even num
      if ((int) nmos.getWidth() == nmos.getWidth())
        new_mos.getWidth() = nmos.getWidth();
      else {
        if (i == 1)
          new_mos.getWidth() = nmos.getWidth() + (float) 0.5;
        else
          new_mos.getWidth() = nmos.getWidth() - (float) 0.5;
      }
//      new_mos.getWidth() = nmos.getWidth();
      db.nmos_list().push_back(new_mos);

      index new_index = i + db.nmos_ids().size() - 1;
      db.nmos_ids().push_back(new_index);
    }

  }
  idx = -1;
  for (auto &pmos : db1.pmos_list()) {
    idx++;
    if (pmos.getWidth() < 220) {
      continue;
    }
    index n;
    n = std::ceil(pmos.getWidth() / 220);
    pmos.getWidth() = (float) std::round((pmos.getWidth() / (float) n) * 100) / 100;
    if ((int) pmos.getWidth() == pmos.getWidth())
      db.pmos_list().at(idx).getWidth() = pmos.getWidth();
    else {
      if (idx == 0)
        db.pmos_list().at(idx).getWidth() = pmos.getWidth() + (float) 0.5;
      else
        db.pmos_list().at(idx).getWidth() = pmos.getWidth() - (float) 0.5;
    }
    for (index i = 1; i < n; i++) {
      Mos new_mos;
      new_mos.getType() = 1;
      std::string mos_name;
      mos_name.append(pmos.getMosName() + "_finger_" + std::to_string(i));
      new_mos.getMosName() = mos_name;
      new_mos.getLeft() = pmos.getLeft();
      new_mos.getGate() = pmos.getGate();
      new_mos.getRight() = pmos.getRight();
      if ((int) pmos.getWidth() == pmos.getWidth())
        new_mos.getWidth() = pmos.getWidth();
      else {
        if (i == 1)
          new_mos.getWidth() = pmos.getWidth() + (float) 0.5;
        else
          new_mos.getWidth() = pmos.getWidth() - (float) 0.5;
      }
      db.pmos_list().push_back(new_mos);
      index new_index = i + db.pmos_ids().size();
      db.pmos_ids().push_back(new_index);
    }
  }
}