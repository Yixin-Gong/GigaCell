//
// Created by zy on 23-11-3.
//

#include "notch.h"
int32_t gigaplace::Notch::notchNum() {
  int32_t notchNum = 0;
  for(auto &kconfig : pl_db_.l_config()){
    if(kconfig.num_finger < 2)
      continue;
    for(int32_t i = 0; i < kconfig.num_finger - 1 ; i++){
      auto nmos1 = pl_db_.mos_list().at(kconfig.pair_list[i].nmos_idx);
      auto nmos2 = pl_db_.mos_list().at(kconfig.pair_list[i+1].nmos_idx);
      auto nmos3 = pl_db_.mos_list().at(kconfig.pair_list[i+2].nmos_idx);
      if(nmos1.getDummyFlag() || nmos2.getDummyFlag() || nmos3.getDummyFlag())
        continue;
      if(nmos1.getWidth() > nmos2.getWidth() && nmos3.getWidth() > nmos2.getWidth())
        notchNum++;
    }
    for(int32_t i = 0; i < kconfig.num_finger - 1 ; i++){
      auto pmos1 = pl_db_.mos_list().at(kconfig.pair_list[i].pmos_idx);
      auto pmos2 = pl_db_.mos_list().at(kconfig.pair_list[i+1].pmos_idx);
      auto pmos3 = pl_db_.mos_list().at(kconfig.pair_list[i+2].pmos_idx);
      if(pmos1.getDummyFlag() || pmos2.getDummyFlag() || pmos3.getDummyFlag())
        continue;
      if(pmos1.getWidth() > pmos2.getWidth() && pmos3.getWidth() > pmos2.getWidth())
        notchNum++;
    }
  }
  return notchNum;
}
