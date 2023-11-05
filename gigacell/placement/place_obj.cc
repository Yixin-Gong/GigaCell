//
// Created by eric on 23-9-21.
//

#include "place_obj.h"

float gigaplace::PlaceObj::getMinGap() {
  float u_odd_num = 0;
  float l_odd_num = 0;

  //make map
  std::unordered_map<std::string, int32_t> upper_Graph;
  std::unordered_map<std::string, int32_t> lower_Graph;
  int32_t unit_degree = 1;

  for (auto &kMos : pl_db_.pmos_list()) {
    if (upper_Graph.find(kMos.getLeft()) == upper_Graph.end())
      upper_Graph.emplace(kMos.getLeft(), unit_degree);
    else
      upper_Graph.find(kMos.getLeft())->second++;
    if (upper_Graph.find(kMos.getRight()) == upper_Graph.end())
      upper_Graph.emplace(kMos.getRight(), unit_degree);
    else
      upper_Graph.find(kMos.getRight())->second++;

  }
  for (auto &kMos : pl_db_.nmos_list()) {
    if (lower_Graph.find(kMos.getLeft()) == lower_Graph.end())
      lower_Graph.emplace(kMos.getLeft(), unit_degree);
    else
      lower_Graph.find(kMos.getLeft())->second++;
    if (lower_Graph.find(kMos.getRight()) == lower_Graph.end())
      lower_Graph.emplace(kMos.getRight(), unit_degree);
    else
      lower_Graph.find(kMos.getRight())->second++;
  }
  for (auto &node : upper_Graph) {
    if (node.second % 2)
      u_odd_num += 1;
  }
  for (auto &node : lower_Graph) {
    if (node.second % 2)
      l_odd_num += 1;
  }

  return std::max(float(0.0), (u_odd_num + l_odd_num - 4) / 2);
}
void gigaplace::PlaceObj::getCellRefWidth() {
  auto min_gap = getMinGap();
  cell_ref_width_ = (min_gap + ref_width_) / 2;
}
void gigaplace::PlaceObj::getWidthScore() {
  Area area(pl_db_);
  auto width = area.calWidth();
  ws_ = 40 * (1 - (width - cell_ref_width_) / (cell_ref_width_ + 20));
}
void gigaplace::PlaceObj::getNetScore() {
  NetLength netlength(pl_db_);
  auto bbox = netlength.calNetLength();
  auto pin_len = (float) pl_db_.v_pin_list().size();
  bs_ = std::min((float) 20, 20 * (1 - (bbox - cell_ref_width_ * (pin_len - 1)) / 60));
}
void gigaplace::PlaceObj::init() {
  getCellRefWidth();
  getWidthScore();
  getNetScore();
  getPinScore();
  score_ = ws_ + bs_ + ps_;
}
void gigaplace::PlaceObj::getPinScore() {
  PinDensity pindensity(pl_db_);
  auto pin_access = pindensity.getPinAccess();
  ps_ = 10 * (1 - pin_access);

}
