#ifndef GIGACELL_MOS_H
#define GIGACELL_MOS_H

#include <iostream>

class Mos {
 public:
  Mos() = default;
  float &getGateLoc() { return gate_loc_; }
  float &getSourceLoc() {return source_loc_;}
  float &getDrainLoc() {return drain_loc_;}
  int32_t &getType() { return type_; }
  std::string &getSource() { return source_; }
  std::string &getGate() { return gate_; }
  std::string &getDrain() { return drain_; }
  std::string &getMosName(){ return mosName_; }
  float &getWidth() { return width_; }

 private:
  float gate_loc_{};        //gate location
  float source_loc_{};        //source location
  float drain_loc_{};        //drown location
  int32_t type_{};       //0-NMOS 1-PMOS

  std::string source_; //right net
  std::string gate_;   //
  std::string drain_;  //light net

  float width_{};        //width >= 0 nm
  std::string mosName_;  //mosName


  //d,g,s
};

#endif //GIGACELL_MOS_H
