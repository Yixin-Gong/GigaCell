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
  while (G_T_ > 0.01) {

    float new_cost = 0;
    for (int i = 0; i < 1; i++) {
      PlaceDB temp_pl_db = init_pl_db;
      temp_pl_db.l_config().clear();
      gigaplace::Operator::v_configTol_config(pl_db_.v_config(), temp_pl_db.l_config());
      auto cost = MLASPlace(pair_num, temp_pl_db);
      if (old_cost > cost) {
        old_cost = cost;
        pl_db_.l_config() = temp_pl_db.l_config();
        pl_db_.mos_list() = temp_pl_db.mos_list();
        pl_db_.nets() = temp_pl_db.nets();
      } else
        continue;
    }
//    std::cout << "old_cost" << ' ' << old_cost << std::endl;
    auto config_vector = pl_db_.v_config();
    auto config_list = pl_db_.l_config();
    auto mos_list = pl_db_.mos_list();
    auto nets = pl_db_.nets();

//    auto pair = generate2Num(pair_num);
    auto pair = selectPairMos(pl_db_, pl_db_.v_config());
    gigaplace::Operator::createNewInitPair(pl_db_, pair.first, pair.second);
    for (int i = 0; i < 1; i++) {
      PlaceDB temp_pl_db = init_pl_db;
      temp_pl_db.l_config().clear();
      gigaplace::Operator::v_configTol_config(pl_db_.v_config(), temp_pl_db.l_config());
      auto cost = MLASPlace(pair_num, temp_pl_db);
      if (new_cost > cost) {
        new_cost = cost;
        pl_db_.l_config() = temp_pl_db.l_config();
        pl_db_.mos_list() = temp_pl_db.mos_list();
        pl_db_.nets() = temp_pl_db.nets();
      } else
        continue;
    }
//    std::cout << "new_cost" << ' ' << new_cost << std::endl;
    auto delta_C = computeDeltaC(new_cost, old_cost);
    if (!accept(delta_C, G_T_)) {
      pl_db_.v_config() = config_vector;
      pl_db_.l_config() = config_list;
      pl_db_.mos_list() = mos_list;
      pl_db_.nets() = nets;
    } else {
      old_cost = new_cost;
      score_ = old_cost;
    }
//    std::cout << "current_G_T" << ' ' << G_T_ << std::endl;
    G_T_ *= 0.9;
  }
}

std::pair<uint16_t, uint16_t> gigaplace::GigaPlace::selectPairMos(gigaplace::PlaceDB &pl_db,
                                                                  std::vector<PlaceDB::Configuration> &v_config) {
  std::unordered_map<std::string, index> name_map{};
  std::vector<std::string> gate_name{};
  std::vector<std::vector<index>> same_gate_pair{};
  std::vector<index> empty{};

  //get gate name
  index i = 0;
  for (auto kPair : v_config) {
    auto &mos = pl_db.mos_list().at(kPair.pair_list.at(0).nmos_idx);
    auto iter = name_map.find(mos.getGate());
    if (iter == name_map.end()) {
      name_map.emplace(mos.getGate(), i);
      i++;
      gate_name.push_back(mos.getGate());
      same_gate_pair.push_back(empty);
    }
  }

  for (auto &kPair : v_config) {
    auto &mos = pl_db.mos_list().at(kPair.pair_list.at(0).nmos_idx);
    auto iter = name_map.find(mos.getGate());
    if (iter != name_map.end())
      same_gate_pair.at(name_map.at(mos.getGate())).push_back(kPair.pair_list.at(0).pair_idx);
  }

  std::vector<std::vector<index>> same_gate_pair2{};
  for (auto &kgate : same_gate_pair) {
    if (kgate.size() > 1)
      same_gate_pair2.push_back(kgate);
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  uint16_t num_gate = gate_name.size() - 1;
  std::uniform_int_distribution<> distrib_num_gate(0, num_gate);
//  std::cout << num_gate << std::endl;
  uint16_t random_num_gate = distrib_num_gate(gen);

  uint16_t num_gate_pair = same_gate_pair2.at(random_num_gate).size();

  num_gate_pair = same_gate_pair2.at(random_num_gate).size();
//  std::cout << random_num_gate << " " << num_gate_pair << std::endl;
  std::pair<uint16_t, uint16_t> get2pair{};
  std::pair f_get2pair = generate2Num(num_gate_pair - 1);
//  std::cout << f_get2pair.first << ' ' << f_get2pair.second<<std::endl;
  get2pair.first = same_gate_pair.at(random_num_gate).at(f_get2pair.first);
  get2pair.second = same_gate_pair.at(random_num_gate).at(f_get2pair.second);
//  std::cout << get2pair.first << ' ' << get2pair.second << std::endl;
  return get2pair;
}
float gigaplace::GigaPlace::MLASPlace(uint16_t pair_num, PlaceDB &temp_pl_db) {
  int Eval = 50000;
  Operator::setCoordinates(temp_pl_db, temp_pl_db.l_config());
  auto place_obj = new gigaplace::PlaceObj(temp_pl_db, ref_width_);
  auto old_cost = -place_obj->get_score();
  delete place_obj;
  for (int i = 0; i < Eval; ++i) {
    auto config_list = temp_pl_db.l_config();
    auto mos_list = temp_pl_db.mos_list();
    auto nets = temp_pl_db.nets();
//    std::cout << "old_cost" << old_cost << std::endl;
    auto pair = generate2Num(pair_num);

    Operator::createNewLayout(temp_pl_db, pair.first, pair.second);
    Operator::setCoordinates(temp_pl_db, temp_pl_db.l_config());
    place_obj = new gigaplace::PlaceObj(temp_pl_db, ref_width_);
    auto new_cost = -place_obj->get_score();
//    std::cout << "new_cost" << new_cost << std::endl;
    delete place_obj;

    auto delta_C = computeDeltaC(new_cost, old_cost);
    if (delta_C < 0) {
      MLASS_accept_rate_ = (float) 0.002 * (499 * MLASS_accept_rate_ + 1);
      old_cost = new_cost;
    } else {
      if (accept(delta_C, MLASS_T_)) {
        MLASS_accept_rate_ = (float) 0.002 * (499 * MLASS_accept_rate_ + 1);
        old_cost = new_cost;
      } else {
        temp_pl_db.l_config() = config_list;
        temp_pl_db.mos_list() = mos_list;
        temp_pl_db.nets() = nets;
        MLASS_accept_rate_ = (float) 0.002 * (499 * MLASS_accept_rate_);
      }
    }
    if ((float) i / (float) Eval < 0.15)
      MLASS_lam_rate_ = 0.44 + 0.56 * std::pow(560, -((float) i / (float) Eval) / 0.15);
    else if ((float) i / (float) Eval < 0.65 && (float) i / (float) Eval >= 0.15)
      MLASS_lam_rate_ = 0.44;
    else if ((float) i / (float) Eval >= 0.65)
      MLASS_lam_rate_ = 0.44 * std::pow(440, -(((float) i / (float) Eval) - 0.65) / 0.35);
    if (MLASS_accept_rate_ > MLASS_lam_rate_)
      MLASS_T_ *= 0.999;
    else
      MLASS_T_ /= 0.999;
  }
  MLASS_T_ = 0.5;
  score_ = old_cost;
  return old_cost;
}
int32_t gigaplace::GigaPlace::numTactics(gigaplace::PlaceDB &pl_db, std::vector<PlaceDB::Configuration> &v_config) {
  std::unordered_map<std::string, index> name_map{};
  std::vector<std::string> gate_name{};
  std::vector<std::vector<index>> same_gate_pair{};
  std::vector<index> empty{};

  //get gate name
  index i = 0;
  for (auto kPair : v_config) {
    auto &mos = pl_db.mos_list().at(kPair.pair_list.at(0).nmos_idx);
    auto iter = name_map.find(mos.getGate());
    if (iter == name_map.end()) {
      name_map.emplace(mos.getGate(), i);
      i++;
      gate_name.push_back(mos.getGate());
      same_gate_pair.push_back(empty);
    }
  }

  for (auto &kPair : v_config) {
    auto &mos = pl_db.mos_list().at(kPair.pair_list.at(0).nmos_idx);
    auto iter = name_map.find(mos.getGate());
    if (iter != name_map.end())
      same_gate_pair.at(name_map.at(mos.getGate())).push_back(kPair.pair_list.at(0).pair_idx);
  }

  std::vector<std::vector<index>> same_gate_pair2{};
  for (auto &kgate : same_gate_pair) {
    if (kgate.size() > 1)
      same_gate_pair2.push_back(kgate);
  }

  int32_t num_tactics = 0;
//  int32_t m = 2;
  for(auto &kgate : same_gate_pair2){
    int32_t res = 1;
    int32_t n = kgate.size();
    for(int32_t j = 1; j <= 2; j++){
      res = res * (n -j + 1)/j;
    }
    num_tactics += res;
  }
  std::cout << num_tactics << std::endl;
  return num_tactics;
}

void gigaplace::GigaPlace::GDUTPlace(uint16_t pair_num) {
  float old_cost = 0;
  PlaceDB init_pl_db = pl_db_;
  int Eval = 200;
  for (int i = 0; i < Eval; ++i) {
    float new_cost = 0;
    PlaceDB tmp_pl_db1 = init_pl_db;
    tmp_pl_db1.l_config().clear();
    gigaplace::Operator::v_configTol_config(pl_db_.v_config(), tmp_pl_db1.l_config());
    auto cost1 = MLASPlace(pair_num, tmp_pl_db1);
    if (old_cost > cost1) {
      old_cost = cost1;
      pl_db_.l_config() = tmp_pl_db1.l_config();
      pl_db_.mos_list() = tmp_pl_db1.mos_list();
      pl_db_.nets() = tmp_pl_db1.nets();
    }
//    std::cout << "old_cost" << ' ' << old_cost << std::endl;
    auto config_vector = pl_db_.v_config();
    auto config_list = pl_db_.l_config();
    auto mos_list = pl_db_.mos_list();
    auto nets = pl_db_.nets();

    auto pair = selectPairMos(pl_db_, pl_db_.v_config());
    gigaplace::Operator::createNewInitPair(pl_db_, pair.first, pair.second);
    PlaceDB tmp_pl_db2 = init_pl_db;
    tmp_pl_db2.l_config().clear();
    gigaplace::Operator::v_configTol_config(pl_db_.v_config(), tmp_pl_db2.l_config());
    auto cost2 = MLASPlace(pair_num, tmp_pl_db2);
    if (new_cost > cost2) {
      new_cost = cost2;
      pl_db_.l_config() = tmp_pl_db2.l_config();
      pl_db_.mos_list() = tmp_pl_db2.mos_list();
      pl_db_.nets() = tmp_pl_db2.nets();
    }
//    std::cout << "new_cost" << ' ' << new_cost << std::endl;
    auto delta_C = computeDeltaC(new_cost, old_cost);
    if (delta_C < 0) {
      GDUT_accept_rate_ = (float) 0.002 * (499 * GDUT_accept_rate_ + 1);
      old_cost = new_cost;
    } else {
      if (accept(delta_C, GDUT_T_)) {
        GDUT_accept_rate_ = (float) 0.002 * (499 * GDUT_accept_rate_ + 1);
        old_cost = new_cost;
      } else {
        pl_db_.v_config() = config_vector;
        pl_db_.l_config() = config_list;
        pl_db_.mos_list() = mos_list;
        pl_db_.nets() = nets;
        GDUT_accept_rate_ = (float) 0.002 * (499 * GDUT_accept_rate_);
      }
    }
    if ((float) i / (float) Eval < 0.15)
      GDUT_lam_rate_ = 0.44 + 0.56 * std::pow(560, -((float) i / (float) Eval) / 0.15);
    else if ((float) i / (float) Eval < 0.65 && (float) i / (float) Eval >= 0.15)
      GDUT_lam_rate_ = 0.44;
    else if ((float) i / (float) Eval >= 0.65)
      GDUT_lam_rate_ = 0.44 * std::pow(440, -(((float) i / (float) Eval) - 0.65) / 0.35);
    if (GDUT_accept_rate_ > GDUT_lam_rate_)
      GDUT_T_ *= 0.999;
    else
      GDUT_T_ /= 0.999;
  }
  GDUT_T_ = 0.5;
  score_ = old_cost;
}
