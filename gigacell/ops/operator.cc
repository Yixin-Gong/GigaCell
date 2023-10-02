//
// Created by eric on 23-9-21.
//

#include "operator.h"

void gigaplace::Operator::flip(Mos &mos) {
  if (mos.getRightLoc() - mos.getLeftLoc() > 0) {
    mos.getRightLoc() = mos.getRightLoc() - 1;
    mos.getLeftLoc() = mos.getLeftLoc() + 1;
  } else {
    mos.getRightLoc() = mos.getRightLoc() + 1;
    mos.getLeftLoc() = mos.getLeftLoc() - 1;

  }
}

void gigaplace::Operator::swap(Mos &mos1, Mos &mos2, index &index1, index &index2) {
  if (mos1.getType() != mos2.getType()) {
    std::cerr << "Error" << std::endl;
    return;
  }

  index idx;
  idx = index2;
  index2 = index1;
  index1 = idx;

  float loc;

  loc = mos2.getGateLoc();
  mos2.getGateLoc() = mos1.getGateLoc();
  mos1.getGateLoc() = loc;

  float temp1;
  float temp2;
  temp1 = std::max(mos1.getLeftLoc(), mos1.getRightLoc());
  temp2 = std::min(mos1.getLeftLoc(), mos1.getRightLoc());
  if (mos1.getRightLoc() > mos1.getLeftLoc()) {
    mos1.getRightLoc() = std::max(mos2.getRightLoc(), mos2.getLeftLoc());
    mos1.getLeftLoc() = std::min(mos2.getRightLoc(), mos2.getLeftLoc());
  } else {
    mos1.getRightLoc() = std::min(mos2.getRightLoc(), mos2.getLeftLoc());
    mos1.getLeftLoc() = std::max(mos2.getRightLoc(), mos2.getLeftLoc());
  }
  if (mos2.getRightLoc() > mos2.getLeftLoc()) {
    mos2.getRightLoc() = temp1;
    mos2.getLeftLoc() = temp2;

  } else {
    mos2.getRightLoc() = temp2;
    mos2.getLeftLoc() = temp1;
  }

//    loc = mos2.getRightLoc();
//    mos2.getDrainLoc() = mos1.getRightLoc();
//    mos1.getRightLoc() = loc;
//
//    loc = mos2.getLeftLoc();
//    mos2.getSourceLoc() = mos1.getLeftLoc();
//    mos1.getLeftLoc() = loc;


}

void gigaplace::Operator::fold(gigaplace::DataBase &db) {

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
    db.nmos_list().at(idx).getWidth() = nmos.getWidth();

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
      new_mos.getWidth() = nmos.getWidth();
      db.nmos_list().push_back(new_mos);

      index new_index = i + db.nmos_ids().size();
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
    db.pmos_list().at(idx).getWidth() = pmos.getWidth();
    for (index i = 1; i < n; i++) {
      Mos new_mos;
      new_mos.getType() = 1;
      std::string mos_name;
      mos_name.append(pmos.getMosName() + "_finger_" + std::to_string(i));
      new_mos.getMosName() = mos_name;
      new_mos.getLeft() = pmos.getLeft();
      new_mos.getGate() = pmos.getGate();
      new_mos.getRight() = pmos.getRight();
      new_mos.getWidth() = pmos.getWidth();
      db.pmos_list().push_back(new_mos);

      index new_index = i + db.pmos_ids().size();
      db.pmos_ids().push_back(new_index);
    }
  }
}

bool gigaplace::Operator::isFold() {
  return false;
}

bool gigaplace::Operator::shouldFold() {
  return false;
}

void gigaplace::Operator::sharing_by_pair() {

}

void gigaplace::Operator::pairing() {

}

Mos gigaplace::Operator::createDummy() {
  return {};
}

bool gigaplace::Operator::isSingle() {
  return false;
}
