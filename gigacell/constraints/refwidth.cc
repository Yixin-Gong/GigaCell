//
// Created by zy on 23-11-3.
//
#include "refwidth.h"

float gigaplace::RefWidth::getRefWidth() {
  //use before placeDB
  float ref_width = 0;
  for (auto mos : db_.nmos_list()) {
    if (mos.getDummyFlag())
      break;
    if (mos.getWidth() > 220)
      ref_width += floor((double) mos.getWidth() / 200);
    else
      ref_width += 1;
  }
  for (auto mos : db_.pmos_list()) {
    if (mos.getDummyFlag())
      break;
    if (mos.getWidth() > 220)
      ref_width += floor((double) mos.getWidth() / 200);
    else
      ref_width += 1;
  }
  return ref_width;

}
