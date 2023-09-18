//
// Created by eric on 23-9-15.
//

#include "place_db.h"
void PlaceDB::init() {
  uint16_t loc_idx = 0;
  uint16_t mos_idx = 0;
  for (auto &kNet : db_.nets()) {
    for (auto &kMos : kNet.second.net2mos()) {
      v_mos_ids().emplace_back(loc_idx);
      v_mos_list().emplace_back(kMos.second.second);
      loc_idx++;

      v_net2mos_ids().emplace_back(mos_idx);
      v_net2mos().emplace_back(kMos.second.first, kMos.second.second);
      mos_idx++;
    }
    mos_idx = 0;
  }
}
