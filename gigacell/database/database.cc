//
// Created by eric on 23-9-15.
//

#include "database.h"

float gigaplace::DataBase::getRefWidth() {
  //use before placeDB
  float ref_width = 0;
  for (auto mos : nmos_list()) {
    if (mos.getDummyFlag())
      break;
    if (mos.getWidth() > 220)
      ref_width += floor((double) mos.getWidth() / 200);
    else
      ref_width += 1;
  }
  for (auto mos : pmos_list()) {
    if (mos.getDummyFlag())
      break;
    if (mos.getWidth() > 220)
      ref_width += floor((double) mos.getWidth() / 200);
    else
      ref_width += 1;
  }
  return ref_width;

}
