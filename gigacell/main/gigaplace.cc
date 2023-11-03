//
// Created by eric on 23-9-15.
//

#include "gigaplace.h"
#include <random>
float gigaplace::GigaPlace::computeDeltaC(float &new_cost, float &old_cost) {
  return new_cost - old_cost;
}

bool gigaplace::GigaPlace::accept(float &delta_c, float T) {
  float prob;
  float r;
  prob = std::exp(-delta_c / T);

  r = static_cast <float> (random()) / static_cast <float> (RAND_MAX);
  if (r < std::min(prob, (float) 1.0))
    return true;
  else
    return false;
}

std::pair<uint16_t, uint16_t> gigaplace::GigaPlace::generate2Num(PlaceDB &place_db, uint16_t pair_num) {
  std::pair<uint16_t, uint16_t> pair{};
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_int_distribution<> distrib(0, pair_num);

  pair.first = distrib(gen);
  pair.second = distrib(gen);
  while (pair.first == pair.second)
    pair.second = distrib(gen);
  return pair;
}

void gigaplace::GigaPlace::SAPlace(uint16_t pair_num) {
  while (T > 0.001) {
    Operator::setCoordinates(pl_db_, pl_db_.l_config());
    auto config_list = pl_db_.l_config();
    auto old_cost = pl_obj_.get_score();
    auto pair = generate2Num(pl_db_, pair_num);

    Operator::createNewLayout(pl_db_, pair.first, pair.second);
    Operator::setCoordinates(pl_db_, pl_db_.l_config());
    auto new_cost = pl_obj_.get_score();

    auto delta_C = computeDeltaC(new_cost, old_cost);
    if (!accept(delta_C, T)) {
      pl_db_.l_config() = config_list;
    }
  }
  T *= 0.9;
}
