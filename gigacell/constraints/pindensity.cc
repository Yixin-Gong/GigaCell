//
// Created by zy on 23-10-28.
//

#include "pindensity.h"

float gigaplace::PinDensity::getPinAccess() {
  Area area(pl_db_);
  auto width = area.calWidth();
//  std::vector<std::string> v_pin_name{};
  std::vector<float> pin_coords{};
//  for (auto &pin : pl_db_.v_pin_list())
//    v_pin_name.push_back(pin.pinName);
  for (auto &kNet : pl_db_.nets()) {
    if (isPinNet(kNet.first, pl_db_.v_pin())) {
      pin_coords.push_back(0);
      std::vector<float> net_pos{};
      float max_distance = -std::numeric_limits<float>::max();
      for (auto &kMos : kNet.second) {
        if (pl_db_.mos_list().at(kMos.idx).getMosName().find("finger")!=std::string::npos)
          continue;
        if (kMos.electrode_name == "left")
          net_pos.push_back(pl_db_.mos_list().at(kMos.idx).getLeftLoc());
        else if (kMos.electrode_name == "gate")
          net_pos.push_back(pl_db_.mos_list().at(kMos.idx).getGateLoc());
        else
          net_pos.push_back(pl_db_.mos_list().at(kMos.idx).getRightLoc());
      }
      std::vector<float> another_pos{};
      for (auto &kNet1 : pl_db_.nets()) {
        if (isPinNet(kNet1.first, pl_db_.v_pin()) && kNet1.first != kNet.first) {
          for (auto &kMos : kNet1.second) {
            if (pl_db_.mos_list().at(kMos.idx).getMosName().find("finger")!=std::string::npos)
              continue;
            if (kMos.electrode_name == "left")
              another_pos.push_back(pl_db_.mos_list().at(kMos.idx).getLeftLoc());
            else if (kMos.electrode_name == "gate")
              another_pos.push_back(pl_db_.mos_list().at(kMos.idx).getGateLoc());
            else
              another_pos.push_back(pl_db_.mos_list().at(kMos.idx).getRightLoc());
          }
        }
      }
      std::sort(another_pos.begin(), another_pos.end());
      for (auto &pos : net_pos) {
        float distance = 0;
        if (another_pos.at(0) > pos)
          distance = std::abs(another_pos.at(0) - pos);
        else if (another_pos.at(another_pos.size() - 1) < pos)
          distance = std::abs(another_pos.at(another_pos.size() - 1) - pos);
        else {
          for (int32_t i = 0; i < another_pos.size() - 1; i++) {
            if (pos > another_pos.at(i) && pos < another_pos.at(i + 1))
              distance = std::min(std::abs(another_pos.at(i) - pos), std::abs(another_pos.at(i + 1) - pos));
          }
        }

        if (distance > max_distance) {
          max_distance = distance;
          pin_coords.at(pin_coords.size() - 1) = pos;

        }

      }

    }
  }
  float half_unit = 0.5;
  std::sort(pin_coords.begin(), pin_coords.end());
  std::vector<float> pin_spacing{};
  float left_spacing = pin_coords.at(0) + half_unit;
  float right_spacing = width - half_unit - pin_coords.at(pin_coords.size() - 1);
  if (left_spacing > 1)
    pin_spacing.push_back(left_spacing / width);
  if (right_spacing > 1)
    pin_spacing.push_back(right_spacing / width);

  for (int32_t i = 0; i < pin_coords.size() - 1; i++)
    pin_spacing.push_back((pin_coords.at(i + 1) - pin_coords.at(i)) / width);

  return calStandardDeviation(pin_spacing);
}

bool gigaplace::PinDensity::isPinNet(const std::string &netName, const std::vector<std::string> &v_pin_name) {
  auto it = std::find(v_pin_name.begin(), v_pin_name.end(), netName);
  if (it != v_pin_name.end())
    return true;
  else
    return false;
}

float gigaplace::PinDensity::calStandardDeviation(const std::vector<float> &pin_spacing) {
  float sum = 0;
  auto N = (float) pin_spacing.size();
  float average;
  float variance;
  for (auto &val : pin_spacing)
    sum += val;
  average = sum / N;
  for (auto &val : pin_spacing)
    variance += (float) std::pow(val - average, 2);
  variance = variance / N;

  return std::sqrt(variance);
}
