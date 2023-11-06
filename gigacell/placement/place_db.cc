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
  int32_t idx = -1;
  DataBase db1 = db;

  //find nmos_mode
  std::unordered_map<float, float> count_map;
  std::unordered_map<float, float> count_map2;
  float nmos_mode = 0;
  float pmos_mode = 0;
  float max_count = 0;
  std::vector<float> width;
  for (auto &nmos : db1.nmos_list()) {
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
    width.push_back(pmos.getWidth());
  }
  for (auto num : width) {
    count_map2[num]++;
    if (count_map2[num] > max_count) {
      max_count = count_map2[num];
      pmos_mode = num;
    }
  }

  for (auto &nmos : db1.nmos_list()) {
    idx++;
    if (nmos.getWidth() < 220) {
      continue;
    }

    index n;
    n = std::ceil(nmos.getWidth() / nmos_mode);
    float last_width = nmos.getWidth() - (n - 1) * nmos_mode;

    //last width < 120 n == 3 --> /2
    if (last_width < 120 && n == 3) {
      float num = 0;
      num = nmos.getWidth() / (float) n;
      double fractpart = 0, intpart = 0;
      fractpart = modf(num, &intpart);

      Mos new_mos;
      new_mos.getType() = 0;
      std::string name;
      std::string mos_name = nmos.getMosName();

      name.append(mos_name + "_finger_" + std::to_string(1));

      new_mos.getMosName() = name;
      new_mos.getLeft() = nmos.getLeft();
      new_mos.getGate() = nmos.getGate();
      new_mos.getRight() = nmos.getRight();

      index new_index = db.nmos_ids().size();
      db.nmos_ids().push_back(new_index);

      if (fractpart == 0) {
        nmos.getWidth() = nmos_mode;
        db.nmos_list().at(idx).getWidth() = nmos.getWidth();
        new_mos.getWidth() = nmos_mode;
        db.nmos_list().push_back(new_mos);
      } else {
        nmos.getWidth() = (float) intpart;
        db.nmos_list().at(idx).getWidth() = nmos.getWidth();
        new_mos.getWidth() = (float) intpart + 1;
        db.nmos_list().push_back(new_mos);
      }
    } else {
      //last width > 120
      Mos new_mos;
      new_mos.getType() = 0;
      std::string name;
      std::string mos_name = nmos.getMosName();

      name.append(mos_name + "_finger_" + std::to_string(1));

      new_mos.getMosName() = name;
      new_mos.getLeft() = nmos.getLeft();
      new_mos.getGate() = nmos.getGate();
      new_mos.getRight() = nmos.getRight();

      index new_index = db.nmos_ids().size();
      db.nmos_ids().push_back(new_index);
      nmos.getWidth() = nmos_mode;
      db.nmos_list().at(idx).getWidth() = nmos.getWidth();
      new_mos.getWidth() = last_width;
      db.nmos_list().push_back(new_mos);
    }

    //last width < 120   --> /2
    if (last_width < 120 && n > 3) {
      float num = 0;
      num = (nmos_mode + last_width) / 2;
      double fractpart = 0, intpart = 0;
      fractpart = modf(num, &intpart);

      Mos new_mos;
      new_mos.getType() = 0;
      std::string name;
      std::string mos_name = nmos.getMosName();

      new_mos.getLeft() = nmos.getLeft();
      new_mos.getGate() = nmos.getGate();
      new_mos.getRight() = nmos.getRight();

      if (fractpart == 0) {
        name.append(mos_name + "_finger_" + std::to_string(1));
        new_mos.getMosName() = name;

        nmos.getWidth() = num;
        db.nmos_list().at(idx).getWidth() = nmos.getWidth();
        new_mos.getWidth() = num;
        db.nmos_list().push_back(new_mos);

        index new_index = db.nmos_ids().size();
        db.nmos_ids().push_back(new_index);
      } else {
        name.append(mos_name + "_finger_" + std::to_string(1));
        new_mos.getMosName() = name;

        nmos.getWidth() = (float) intpart;
        db.nmos_list().at(idx).getWidth() = nmos.getWidth();
        new_mos.getWidth() = (float) intpart + 1;
        db.nmos_list().push_back(new_mos);

        index new_index = db.nmos_ids().size();
        db.nmos_ids().push_back(new_index);

      }

      for (index i = 2; i < n - 2; i++) {
        name.append(mos_name + "_finger_" + std::to_string(i));
        new_mos.getMosName() = name;

        new_mos.getWidth() = nmos_mode;
        db.nmos_list().push_back(new_mos);

        index new_index = db.nmos_ids().size();//+i-1
        db.nmos_ids().push_back(new_index);
      }
    } else {
      //last width > 120
      Mos new_mos;
      new_mos.getType() = 0;
      std::string name;
      std::string mos_name = nmos.getMosName();

      name.append(mos_name + "_finger_" + std::to_string(1));

      new_mos.getMosName() = name;
      new_mos.getLeft() = nmos.getLeft();
      new_mos.getGate() = nmos.getGate();
      new_mos.getRight() = nmos.getRight();

      index new_index = db.nmos_ids().size();
      db.nmos_ids().push_back(new_index);
      nmos.getWidth() = nmos_mode;
      db.nmos_list().at(idx).getWidth() = nmos.getWidth();
      new_mos.getWidth() = last_width;
      db.nmos_list().push_back(new_mos);

      for (index i = 2; i < n - 2; i++) {
        name.append(mos_name + "_finger_" + std::to_string(i));
        new_mos.getMosName() = name;

        new_mos.getWidth() = nmos_mode;
        db.nmos_list().push_back(new_mos);

        index new_index = db.nmos_ids().size();//+i-1
        db.nmos_ids().push_back(new_index);
      }
    }
  }

  idx = -1;
  for (auto &pmos : db1.pmos_list()) {
    idx++;
    if (pmos.getWidth() < 220) {
      continue;
    }

    index n;
    n = std::ceil(pmos.getWidth() / pmos_mode);
    float last_width = pmos.getWidth() - (n - 1) * pmos_mode;

    //last width < 120 n == 3 --> /2
    if (last_width < 120 && n == 3) {
      float num = 0;
      num = pmos.getWidth() / (float) n;
      double fractpart = 0, intpart = 0;
      fractpart = modf(num, &intpart);

      Mos new_mos;
      new_mos.getType() = 1;
      std::string name;
      std::string mos_name = pmos.getMosName();

      name.append(mos_name + "_finger_" + std::to_string(1));

      new_mos.getMosName() = name;
      new_mos.getLeft() = pmos.getLeft();
      new_mos.getGate() = pmos.getGate();
      new_mos.getRight() = pmos.getRight();

      index new_index = db.pmos_ids().size();
      db.pmos_ids().push_back(new_index);

      if (fractpart == 0) {
        pmos.getWidth() = pmos_mode;
        db.pmos_list().at(idx).getWidth() = pmos.getWidth();
        new_mos.getWidth() = pmos_mode;
        db.pmos_list().push_back(new_mos);
      } else {
        pmos.getWidth() = (float) intpart;
        db.pmos_list().at(idx).getWidth() = pmos.getWidth();
        new_mos.getWidth() = (float) intpart + 1;
        db.pmos_list().push_back(new_mos);
      }
    } else {
      //last width > 120
      Mos new_mos;
      new_mos.getType() = 0;
      std::string name;
      std::string mos_name = pmos.getMosName();

      name.append(mos_name + "_finger_" + std::to_string(1));

      new_mos.getMosName() = name;
      new_mos.getLeft() = pmos.getLeft();
      new_mos.getGate() = pmos.getGate();
      new_mos.getRight() = pmos.getRight();

      index new_index = db.pmos_ids().size();
      db.pmos_ids().push_back(new_index);
      pmos.getWidth() = pmos_mode;
      db.pmos_list().at(idx).getWidth() = pmos.getWidth();
      new_mos.getWidth() = last_width;
      db.pmos_list().push_back(new_mos);
    }

    //last width < 120   --> /2
    if (last_width < 120 && n > 3) {
      float num = 0;
      num = (pmos_mode + last_width) / 2;
      double fractpart = 0, intpart = 0;
      fractpart = modf(num, &intpart);

      Mos new_mos;
      new_mos.getType() = 1;
      std::string name;
      std::string mos_name = pmos.getMosName();

      new_mos.getLeft() = pmos.getLeft();
      new_mos.getGate() = pmos.getGate();
      new_mos.getRight() = pmos.getRight();

      if (fractpart == 0) {
        name.append(mos_name + "_finger_" + std::to_string(1));
        new_mos.getMosName() = name;

        pmos.getWidth() = num;
        db.pmos_list().at(idx).getWidth() = pmos.getWidth();
        new_mos.getWidth() = num;
        db.pmos_list().push_back(new_mos);

        index new_index = db.pmos_ids().size();
        db.pmos_ids().push_back(new_index);
      } else {
        name.append(mos_name + "_finger_" + std::to_string(1));
        new_mos.getMosName() = name;

        pmos.getWidth() = (float) intpart;
        db.pmos_list().at(idx).getWidth() = pmos.getWidth();
        new_mos.getWidth() = (float) intpart + 1;
        db.pmos_list().push_back(new_mos);

        index new_index = db.pmos_ids().size();
        db.pmos_ids().push_back(new_index);

      }

      for (index i = 2; i < n - 2; i++) {
        name.append(mos_name + "_finger_" + std::to_string(i));
        new_mos.getMosName() = name;

        new_mos.getWidth() = pmos_mode;
        db.pmos_list().push_back(new_mos);

        index new_index = db.pmos_ids().size();//+i-1
        db.pmos_ids().push_back(new_index);
      }
    } else {
      //last width > 120
      Mos new_mos;
      new_mos.getType() = 1;
      std::string name;
      std::string mos_name = pmos.getMosName();

      name.append(mos_name + "_finger_" + std::to_string(1));

      new_mos.getMosName() = name;
      new_mos.getLeft() = pmos.getLeft();
      new_mos.getGate() = pmos.getGate();
      new_mos.getRight() = pmos.getRight();

      index new_index = db.pmos_ids().size();
      db.pmos_ids().push_back(new_index);
      pmos.getWidth() = pmos_mode;
      db.pmos_list().at(idx).getWidth() = pmos.getWidth();
      new_mos.getWidth() = last_width;
      db.pmos_list().push_back(new_mos);

      for (index i = 2; i < n - 2; i++) {
        name.append(mos_name + "_finger_" + std::to_string(i));
        new_mos.getMosName() = name;

        new_mos.getWidth() = nmos_mode;
        db.pmos_list().push_back(new_mos);

        index new_index = db.pmos_ids().size();//+i-1
        db.pmos_ids().push_back(new_index);
      }
    }
  }
}