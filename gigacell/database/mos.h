#ifndef GIGACELL_MOS_H
#define GIGACELL_MOS_H

#include <iostream>

class Mos {
 public:
  Mos() = default;
  float &getGLoc() { return gLoc_; }
  float &getSLoc() {return sLoc_;}
  float &getDLoc() {return dLoc_;}
  int32_t &getType() { return type_; }
  std::string &getSource() { return source_; }
  std::string &getGate() { return gate_; }
  std::string &getDrain() { return drain_; }
  std::string &getMosName(){ return mosName_; }
  float &getWidth() { return width_; }

 private:
  float gLoc_{};        //gate location
  float sLoc_{};        //source location
  float dLoc_{};        //drown location
  int32_t type_{};       //0-NMOS 1-PMOS
  std::string source_; //left net
  std::string gate_;   //
  std::string drain_;  //right net
  float width_{};        //width >= 0 nm
  std::string mosName_;  //mosName

};

#endif //GIGACELL_MOS_H
