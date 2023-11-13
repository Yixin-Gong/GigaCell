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

std::pair<uint16_t, uint16_t> gigaplace::GigaPlace::generate2Num(uint16_t pair_num) {
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

float gigaplace::GigaPlace::SAPlace(uint16_t pair_num, PlaceDB &temp_pl_db) {
  float old_cost = 0;
  float new_cost = 0;
//  auto iter = 0;
  while (SA_T_ > 0.00000001) {
    Operator::setCoordinates(temp_pl_db, temp_pl_db.l_config());
    auto place_obj = new gigaplace::PlaceObj(temp_pl_db, ref_width_);

    auto config_list = temp_pl_db.l_config();
    auto mos_list = temp_pl_db.mos_list();
    auto nets = temp_pl_db.nets();

    old_cost = -place_obj->get_score();
    score_ = old_cost;
//    std::cout << "old_cost" << old_cost << std::endl;
    auto pair = generate2Num(pair_num);
    delete place_obj;
    Operator::createNewLayout(temp_pl_db, pair.first, pair.second);
    Operator::setCoordinates(temp_pl_db, temp_pl_db.l_config());

    place_obj = new gigaplace::PlaceObj(temp_pl_db, ref_width_);

    new_cost = -place_obj->get_score();
//    std::cout << "new_cost" << new_cost << std::endl;
    delete place_obj;

    auto delta_C = computeDeltaC(new_cost, old_cost);
    if (!accept(delta_C, SA_T_)) {
      temp_pl_db.l_config() = config_list;
      temp_pl_db.mos_list() = mos_list;
      temp_pl_db.nets() = nets;
    }
    SA_T_ *= 0.99;
  }
  SA_T_ = 10000000;
  return old_cost;
}
void gigaplace::GigaPlace::GPlace(uint16_t pair_num) {
  float old_cost = 0;
  PlaceDB init_pl_db = pl_db_;
  while (G_T_ > 0.001) {
    float new_cost = 0;
    for (int i = 0; i < 1; i++) {
      PlaceDB temp_pl_db = init_pl_db;
      temp_pl_db.l_config().clear();
      gigaplace::Operator::v_configTol_config(pl_db_.v_config(), temp_pl_db.l_config());
      auto cost = SAPlace(pair_num, temp_pl_db);
      if (old_cost > cost) {
        old_cost = cost;
        pl_db_.l_config() = temp_pl_db.l_config();
        pl_db_.mos_list() = temp_pl_db.mos_list();
        pl_db_.nets() = temp_pl_db.nets();
      } else
        continue;
    }
    std::cout << "old_cost" << ' ' << old_cost << std::endl;
    auto config_vector = pl_db_.v_config();
    auto config_list = pl_db_.l_config();
    auto mos_list = pl_db_.mos_list();
    auto nets = pl_db_.nets();

    auto pair = generate2Num(pair_num);
    auto flag = gigaplace::Operator::createNewInitPair(pl_db_, pair.first, pair.second);
    if (!flag) {
      G_T_ *= 0.99;
      continue;
    }
    for (int i = 0; i < 10; i++) {
      PlaceDB temp_pl_db = init_pl_db;
      temp_pl_db.l_config().clear();
      gigaplace::Operator::v_configTol_config(pl_db_.v_config(), temp_pl_db.l_config());
      auto cost = SAPlace(pair_num, temp_pl_db);
      if (new_cost > cost) {
        new_cost = cost;
        pl_db_.l_config() = temp_pl_db.l_config();
        pl_db_.mos_list() = temp_pl_db.mos_list();
        pl_db_.nets() = temp_pl_db.nets();
      } else
        continue;
    }
    std::cout << "new_cost" << ' ' << new_cost << std::endl;
    auto delta_C = computeDeltaC(new_cost, old_cost);
    if (!accept(delta_C, G_T_)) {
      pl_db_.v_config() = config_vector;
      pl_db_.l_config() = config_list;
      pl_db_.mos_list() = mos_list;
      pl_db_.nets() = nets;
    }
    G_T_ *= 0.99;
  }

}
void gigaplace::GigaPlace::MLASPlace(uint16_t pair_num) {
  int Eval = 300000;
  for (int i = 0; i < Eval; ++i) {
    Operator::setCoordinates(pl_db_, pl_db_.l_config());
    auto place_obj = new gigaplace::PlaceObj(pl_db_, ref_width_);

    auto config_list = pl_db_.l_config();
    auto mos_list = pl_db_.mos_list();
    auto nets = pl_db_.nets();

    auto old_cost = -place_obj->get_score();
    score_ = old_cost;
    std::cout << "old_cost" << old_cost << std::endl;
    auto pair = generate2Num(pair_num);
    delete place_obj;
    Operator::createNewLayout(pl_db_, pair.first, pair.second);
    Operator::setCoordinates(pl_db_, pl_db_.l_config());

    place_obj = new gigaplace::PlaceObj(pl_db_, ref_width_);

    auto new_cost = -place_obj->get_score();
    std::cout << "new_cost" << new_cost << std::endl;
    delete place_obj;

    auto delta_C = computeDeltaC(new_cost, old_cost);
    if (delta_C < 0)
      MLASS_accept_rate_ = (float) 0.002 * (499 * MLASS_accept_rate_ + 1);
    else {
      if (accept(delta_C, MLASS_T_)) {
        MLASS_accept_rate_ = (float) 0.002 * (499 * MLASS_accept_rate_ + 1);
      } else {
        pl_db_.l_config() = config_list;
        pl_db_.mos_list() = mos_list;
        pl_db_.nets() = nets;
        MLASS_accept_rate_ = (float) 0.002 * (499 * MLASS_accept_rate_);
      }
    }
    if ((float)i/(float )Eval<0.15)
      MLASS_lam_rate_ = 0.44 + 0.56 * std::pow(560, -((float) i / (float) Eval) / 0.15);
    else if((float)i/(float )Eval<0.65&&(float)i/(float)Eval>=0.15)
      MLASS_lam_rate_ = 0.44;
    else if ((float)i/(float)Eval>=0.65)
      MLASS_lam_rate_ = 0.44*std::pow(440,-(((float)i/(float)Eval)-0.65)/0.35);
    if (MLASS_accept_rate_>MLASS_lam_rate_)
      MLASS_T_ *= 0.999;
    else
      MLASS_T_ /= 0.999;
  }
}