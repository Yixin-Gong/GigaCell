//
// Created by eric on 23-9-15.
//

#include "database.h"
void DataBase::addNet(const std::string &name, Net &net) {
  nets_.emplace(name, net);
}
