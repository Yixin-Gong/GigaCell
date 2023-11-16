//
// Created by eric on 23-9-15.
//
#include <fstream>
#include "utils/json.hpp"
#include "writer.h"
using json = nlohmann::json;

void gigaplace::Writer::output() {
  json j;
  json placement;
  for (auto &kmos : pl_db_.mos_list()) {
    json mos;
    if (kmos.getDummyFlag())
      continue;
    mos =
        {{"x", kmos.getGateLoc()}, {"y", kmos.getType()}, {"source", kmos.getLeft()}, {"gate", kmos.getGate()},
         {"drain", kmos.getRight()}, {"width", kmos.getWidth()}};
    placement[kmos.getMosName()] = mos;
    j["placement"] = placement;
  }
  if (*output_path_.rbegin() != '/' && !output_path_.empty()) {
    std::ofstream os(output_path_ + "/" + cell_name_ + ".json");
    os << std::setw(4) << j << std::endl;
    os.close();
  } else if (*output_path_.rbegin() == '/' || output_path_.empty()) {
    std::ofstream os(output_path_ + cell_name_ + ".json");
    os << std::setw(4) << j << std::endl;
    os.close();
  }
}