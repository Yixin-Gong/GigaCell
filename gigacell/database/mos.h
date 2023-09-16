#ifndef GIGACELL_MOS_H
#define GIGACELL_MOS_H

#include <iostream>

class Mos {
 public:
  Mos() = default;
  int32_t &getLoc() { return loc_; }
  int32_t &getType() { return type_; }
  std::string &getSource() { return source_; }
  std::string &getGate() { return gate_; }
  std::string &getDrain() { return drain_; }
  float &getWidth() { return width_; }
 private:
  int32_t loc_{};        //xi > 0
  int32_t type_{};       //0-NMOS 1-PMOS
  std::string source_; //left net
  std::string gate_;   //
  std::string drain_;  //right net
  float width_{};        //width >= 0 nm

};

#endif //GIGACELL_MOS_H
