//
// Created by eric on 23-9-21.
//

#include "place_obj.h"

float gigaplace::PlaceObj::computeCost() {
  return 50 * area_.computeArea() + 10 * net_length_.netLength();
}


