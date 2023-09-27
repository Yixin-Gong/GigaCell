//
// Created by eric on 23-9-15.
//

#include "place_db.h"

#include <cmath>

void gigaplace::PlaceDB::init() {
  Net2Mos net2mos{};
  std::vector<Net2Mos> net{};
  index idx = 0;

  for (auto &nmos : db_.nmos_list()) {
    net2mos.idx = idx;
    net2mos.type = 0;
    if (nets_.find(nmos.getDrain()) == nets_.end()) {
      nets_.emplace(nmos.getDrain(), net);
      net2mos.electrode_name = "drain";
      nets_.find(nmos.getDrain())->second.emplace_back(net2mos);
    } else if (nets_.find(nmos.getDrain()) != nets_.end()) {
      net2mos.electrode_name = "drain";
      nets_.find(nmos.getDrain())->second.emplace_back(net2mos);
    }
    if (nets_.find(nmos.getGate()) == nets_.end()) {
      nets_.emplace(nmos.getGate(), net);
      net2mos.electrode_name = "gate";
      nets_.find(nmos.getGate())->second.emplace_back(net2mos);
    } else if (nets_.find(nmos.getGate()) != nets_.end()) {
      net2mos.electrode_name = "gate";
      nets_.find(nmos.getGate())->second.emplace_back(net2mos);
    }
    if (nets_.find(nmos.getSource()) == nets_.end()) {
      nets_.emplace(nmos.getSource(), net);
      net2mos.electrode_name = "source";
      nets_.find(nmos.getSource())->second.emplace_back(net2mos);
    } else if (nets_.find(nmos.getSource()) != nets_.end()) {
      net2mos.electrode_name = "source";
      nets_.find(nmos.getSource())->second.emplace_back(net2mos);
    }
    idx++;
  }
  idx = 0;
  for (auto &pmos : db_.pmos_list()) {
    net2mos.idx = idx;
    net2mos.type = 1;
    if (nets_.find(pmos.getDrain()) == nets_.end()) {
      nets_.emplace(pmos.getDrain(), net);
      net2mos.electrode_name = "drain";
      nets_.find(pmos.getDrain())->second.emplace_back(net2mos);
    } else if (nets_.find(pmos.getDrain()) != nets_.end()) {
      net2mos.electrode_name = "drain";
      nets_.find(pmos.getDrain())->second.emplace_back(net2mos);
    }
    if (nets_.find(pmos.getGate()) == nets_.end()) {
      nets_.emplace(pmos.getGate(), net);
      net2mos.electrode_name = "gate";
      nets_.find(pmos.getGate())->second.emplace_back(net2mos);
    } else if (nets_.find(pmos.getGate()) != nets_.end()) {
      net2mos.electrode_name = "gate";
      nets_.find(pmos.getGate())->second.emplace_back(net2mos);
    }
    if (nets_.find(pmos.getSource()) == nets_.end()) {
      nets_.emplace(pmos.getSource(), net);
      net2mos.electrode_name = "source";
      nets_.find(pmos.getSource())->second.emplace_back(net2mos);
    } else if (nets_.find(pmos.getSource()) != nets_.end()) {
      net2mos.electrode_name = "source";
      nets_.find(pmos.getSource())->second.emplace_back(net2mos);
    }
    idx++;
  }
  idx = 0;
  for (Mos &nmos : db_.nmos_list()) {
    nmos_list().push_back(nmos);
    nmos_ids().push_back(idx);
    idx++;
  }
  idx = 0;
  for (Mos &pmos : db_.pmos_list()) {
    pmos_list().push_back(pmos);
    pmos_ids().push_back(idx);
    idx++;
  }

}

void gigaplace::PlaceDB::fold() {
  std::stringstream ss;

  for (auto &nmos : nmos_list()) {
    if (nmos.getWidth() < 220) {
      continue;
    }

    index n;
    n = std::ceil(nmos.getWidth() / 220);
    nmos.getWidth() = (float )std::round((nmos.getWidth() / (float )n) * 100) / 100;

    for (index i = 1; i < n; i++) {
      Mos new_mos;
      new_mos.getType() = 0;
      ss << i;
      std::string str = ss.str();
      //   new_mos.getMosName()= a;
      ss << nmos.getMosName() << "_finger" << str;

      new_mos.getMosName() = ss.str();
      new_mos.getSource() = nmos.getSource();
      new_mos.getGate() = nmos.getGate();
      new_mos.getDrain() = nmos.getDrain();
      new_mos.getWidth() = nmos.getWidth();
      nmos_list().push_back(new_mos);

      index new_index = i + nmos_ids().size();
      nmos_ids().push_back(new_index);
    }
  }

  for (auto &pmos : pmos_list()) {
    if (pmos.getWidth() < 220) {
      continue;
    }

    index n;
    n = std::ceil(pmos.getWidth() / 220);
    pmos.getWidth() = (float )std::round((pmos.getWidth() / (float )n) * 100) / 100;

    for (index i = 1; i < n; i++) {
      Mos new_mos;
      new_mos.getType() = 1;
      ss << i;
      std::string str = ss.str();
      //   new_mos.getMosName()= a;
      ss << pmos.getMosName() << "_finger" << str;

      new_mos.getMosName() = ss.str();
      new_mos.getSource() = pmos.getSource();
      new_mos.getGate() = pmos.getGate();
      new_mos.getDrain() = pmos.getDrain();
      new_mos.getWidth() = pmos.getWidth();
      pmos_list().push_back(new_mos);

      index new_index = i + pmos_ids().size();
      pmos_ids().push_back(new_index);
    }
  }

}


