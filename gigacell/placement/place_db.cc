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
    v_pin_list().push_back(pin);

}

void gigaplace::PlaceDB::fold(gigaplace::DataBase &db) {
  DataBase db1 = db;
  index new_idx = 0;

  //find nmos_mode pmos_mode
  std::unordered_map<float, float> count_map;
  std::unordered_map<float, float> count_map2;
  float nmos_mode = 0;
  float pmos_mode = 0;
  float max_count = 0;
  std::vector<float> width;
  for (auto &nmos : db1.nmos_list()) {
    if(nmos.getWidth() > 220)
      continue;
    width.push_back(nmos.getWidth());
  }
  for (auto num : width) {
    count_map[num]++;
    if (count_map[num] > max_count) {
      max_count = count_map[num];
      nmos_mode = num;
    }
  }
  max_count = 0;
  std::vector<float>().swap(width);
  for (auto &pmos : db1.pmos_list()) {
    if(pmos.getWidth() > 220)
      continue;
    width.push_back(pmos.getWidth());
  }
  for (auto num : width) {
    count_map2[num]++;
    if (count_map2[num] > max_count) {
      max_count = count_map2[num];
      pmos_mode = num;
    }
  }

  int32_t idx = -1;
  for (auto &nmos : db1.nmos_list()) {
    idx++;
    if (nmos.getWidth() < 220 || nmos.getWidth() == 120) {
      continue;
    }

    index num_of_finger;
    num_of_finger = std::floor(nmos.getWidth() / nmos_mode);
    float last_width = nmos.getWidth() - (float) num_of_finger * nmos_mode;

    //direct assignment
    if (last_width > 120) {
      db.nmos_list().at(idx).getWidth() = last_width;
      for (index i = 1; i < (num_of_finger + 1); i++) {
        Mos new_mos = createNewMos(nmos);
        new_mos.getWidth() = nmos_mode;
        std::string name;
        std::string mos_name = nmos.getMosName();
        name.append(mos_name + "_finger_" + std::to_string(i));
        new_mos.getMosName() = name;
        new_idx = db.nmos_ids().size();
        db.nmos_list().push_back(new_mos);
        db.nmos_ids().push_back(new_idx);
      }
    }

    //assign value after rounding up and down
    if (last_width < 120) {
      if (num_of_finger == 1) {
        db.nmos_list().at(idx).getWidth() = 120;
        Mos new_mos = createNewMos(nmos);
        std::string name;
        std::string mos_name = nmos.getMosName();
        name.append(mos_name + "_finger_" + std::to_string(1));
        new_mos.getMosName() = name;
        new_mos.getWidth() = nmos.getWidth() - 120;
        new_idx = db.nmos_ids().size();
        db.nmos_list().push_back(new_mos);
        db.nmos_ids().push_back(new_idx);
      }

      if (num_of_finger > 1) {
        if ((last_width + nmos_mode) < 220) {
          db.nmos_list().at(idx).getWidth() = nmos_mode;
          Mos new_mos = createNewMos(nmos);
          std::string name;
          std::string mos_name = nmos.getMosName();
          name.append(mos_name + "_finger_" + std::to_string(1));
          new_mos.getMosName() = name;
          new_mos.getWidth() = nmos_mode + last_width;
          new_idx = db.nmos_ids().size();
          db.nmos_list().push_back(new_mos);
          db.nmos_ids().push_back(new_idx);
/////////////////////
          for (index i = 2; i < num_of_finger; i++) {
            new_mos.getWidth() = nmos_mode;
            std::string name;
            std::string mos_name = nmos.getMosName();
            name.append(mos_name + "_finger_" + std::to_string(i));
            new_mos.getMosName() = name;
            new_idx = db.nmos_ids().size();
            db.nmos_list().push_back(new_mos);
            db.nmos_ids().push_back(new_idx);
          }
        }

        if ((last_width + nmos_mode) > 220) {
          db.nmos_list().at(idx).getWidth() = 120;
          Mos new_mos = createNewMos(nmos);
          std::string name;
          std::string mos_name = nmos.getMosName();
          name.append(mos_name + "_finger_" + std::to_string(1));
          new_mos.getMosName() = name;
          new_mos.getWidth() = nmos_mode + last_width - 120;
          new_idx = db.nmos_ids().size();
          db.nmos_list().push_back(new_mos);
          db.nmos_ids().push_back(new_idx);
          for (index i = 2; i < (num_of_finger + 1); i++) {
            new_mos.getWidth() = nmos_mode;
            std::string name;
            std::string mos_name = nmos.getMosName();
            name.append(mos_name + "_finger_" + std::to_string(i));
            new_mos.getMosName() = name;
            new_idx = db.nmos_ids().size();
            db.nmos_list().push_back(new_mos);
            db.nmos_ids().push_back(new_idx);
          }
        }
      }
    }
  }

  idx = -1;
  for (auto &pmos : db1.pmos_list()) {
    idx++;
    if (pmos.getWidth() < 220 || pmos.getWidth() == 120) {
      continue;
    }

    index num_of_finger;
    num_of_finger = std::floor(pmos.getWidth() / pmos_mode);
    float last_width = pmos.getWidth() - (float) num_of_finger * pmos_mode;

    //direct assignment
    if (last_width > 120) {
      db.pmos_list().at(idx).getWidth() = last_width;
      for (index i = 1; i < (num_of_finger + 1); i++) {
        Mos new_mos = createNewMos(pmos);
        new_mos.getWidth() = pmos_mode;
        std::string name;
        std::string mos_name = pmos.getMosName();
        name.append(mos_name + "_finger_" + std::to_string(i));
        new_mos.getMosName() = name;
        new_idx = db.pmos_ids().size();
        db.pmos_list().push_back(new_mos);
        db.pmos_ids().push_back(new_idx);
      }
    }

    //assign value after rounding up and down
    if (last_width < 120) {
      if (num_of_finger == 1) {
        db.pmos_list().at(idx).getWidth() = 120;
        Mos new_mos = createNewMos(pmos);
        std::string name;
        std::string mos_name = pmos.getMosName();
        name.append(mos_name + "_finger_" + std::to_string(1));
        new_mos.getMosName() = name;
        new_mos.getWidth() = pmos.getWidth() - 120;
        new_idx = db.pmos_ids().size();
        db.pmos_list().push_back(new_mos);
        db.pmos_ids().push_back(new_idx);
      }

      if (num_of_finger > 1) {
        if ((last_width + pmos_mode) < 220) {
          db.pmos_list().at(idx).getWidth() = pmos_mode;
          Mos new_mos = createNewMos(pmos);
          std::string name;
          std::string mos_name = pmos.getMosName();
          name.append(mos_name + "_finger_" + std::to_string(1));
          new_mos.getMosName() = name;
          new_mos.getWidth() = pmos_mode + last_width;
          new_idx = db.pmos_ids().size();
          db.pmos_list().push_back(new_mos);
          db.pmos_ids().push_back(new_idx);
/////////////////////
          for (index i = 2; i < num_of_finger; i++) {
            new_mos.getWidth() = pmos_mode;
            std::string name;
            std::string mos_name = pmos.getMosName();
            name.append(mos_name + "_finger_" + std::to_string(i));
            new_mos.getMosName() = name;
            new_idx = db.pmos_ids().size();
            db.pmos_list().push_back(new_mos);
            db.pmos_ids().push_back(new_idx);
          }
        }

        if ((last_width + pmos_mode) > 220) {
          db.pmos_list().at(idx).getWidth() = 120;
          Mos new_mos = createNewMos(pmos);
          std::string name;
          std::string mos_name = pmos.getMosName();
          name.append(mos_name + "_finger_" + std::to_string(1));
          new_mos.getMosName() = name;
          new_mos.getWidth() = pmos_mode + last_width - 120;
          new_idx = db.nmos_ids().size();
          db.pmos_list().push_back(new_mos);
          db.pmos_ids().push_back(new_idx);
          for (index i = 2; i < (num_of_finger + 1); i++) {
            new_mos.getWidth() = pmos_mode;
            std::string name;
            std::string mos_name = pmos.getMosName();
            name.append(mos_name + "_finger_" + std::to_string(i));
            new_mos.getMosName() = name;
            new_idx = db.pmos_ids().size();
            db.pmos_list().push_back(new_mos);
            db.pmos_ids().push_back(new_idx);
          }
        }
      }
    }
  }
}

Mos gigaplace::PlaceDB::createNewMos(Mos &mos) {
  Mos new_mos{};
  new_mos.getType() = mos.getType();
  new_mos.getLeft() = mos.getLeft();
  new_mos.getGate() = mos.getGate();
  new_mos.getRight() = mos.getRight();
  return new_mos;
}
