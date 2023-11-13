//
// Created by eric on 23-9-15.
//
#include <fstream>
#include "utils/json.hpp"
#include "writer.h"
using json = nlohmann::json;

void gigaplace::writer::exporter(gigaplace::PlaceDB &pl_db) {
  json j;
  json placement;
  for (auto &kmos : pl_db.mos_list()) {
    json mos;
    if (kmos.getDummyFlag())
      continue;
    mos =
        {{"x", kmos.getGateLoc()}, {"y", kmos.getType()}, {"source", kmos.getLeft()}, {"gate", kmos.getGate()},
         {"drain", kmos.getRight()}, {"width", kmos.getWidth()}};
    placement[kmos.getMosName()] = mos;
    j["placement"] = placement;
  }
  std::ofstream os("output.json");
  os << std::setw(4) << j << std::endl;
  os.close();
}
