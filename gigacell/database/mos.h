#ifndef GIGACELL_MOS_H
#define GIGACELL_MOS_H

#include <iostream>

class Mos {
 public:
  Mos() = default;
  float &getGateLoc() { return gate_loc_; }
  float &getLeftLoc() { return left_loc_; }
  float &getRightLoc() { return right_loc_; }
  int32_t &getType() { return type_; }
  std::string &getLeft() { return left_; }
  std::string &getGate() { return gate_; }
  std::string &getRight() { return right_; }
  std::string &getMosName() { return mosName_; }
  float &getWidth() { return width_; }
  bool &getConfigFlag(){return config_flag_; }
  bool &getDummyFlag(){return dummy_flag_;}
 private:
  float gate_loc_{};        //gate location
  float left_loc_{};        //source location
  float right_loc_{};        //drown location
  int32_t type_{};       //0-NMOS 1-PMOS

  std::string left_; //left net source
  std::string gate_;   //
  std::string right_;  //right net left

  float width_{};        //width >= 0 nm
  std::string mosName_;  //mosName

  bool config_flag_ = false;
  bool dummy_flag_= false;
};

#endif //GIGACELL_MOS_H
