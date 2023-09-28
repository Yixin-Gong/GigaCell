//
// Created by eric on 23-9-21.
//

#include "operator.h"


void gigaplace::Operator::flip(Mos &mos) {
    if (mos.getDrainLoc() - mos.getSourceLoc() > 0) {
        mos.getDrainLoc() = mos.getDrainLoc() - 1;
        mos.getSourceLoc() = mos.getSourceLoc() + 1;
    } else {
        mos.getDrainLoc() = mos.getDrainLoc() + 1;
        mos.getSourceLoc() = mos.getSourceLoc() - 1;

    }
}

void gigaplace::Operator::swap(Mos &mos1, Mos &mos2, index &index1, index &index2) {
    if (mos1.getType() != mos2.getType()) {
        std::cerr<<"Error"<<std::endl;
        return;
    }

    index idx;
    idx = index2;
    index2= index1;
    index1 = idx;

    float loc;
    loc = mos2.getGateLoc();
    mos2.getGateLoc() = mos1.getGateLoc();
    mos1.getGateLoc() = loc;

    loc = mos2.getDrainLoc();
    mos2.getDrainLoc() = mos1.getDrainLoc();
    mos1.getDrainLoc() = loc;

    loc = mos2.getSourceLoc();
    mos2.getSourceLoc() = mos1.getSourceLoc();
    mos1.getSourceLoc() = loc;


}
void gigaplace::Operator::fold(gigaplace::PlaceDB &pl_db) {
  std::stringstream  ss;

  for(auto &nmos : pl_db.nmos_list()){
    if(nmos.getWidth() < 220 ){
      continue;
    }
    index n;
    n = std::ceil(nmos.getWidth() / 220);
    nmos.getWidth() = (float )std::round((nmos.getWidth()/(float)n) * 100)/100;

    for(index i = 1; i < n; i++){
      Mos new_mos;
      new_mos.getType() = 0;
      ss << i;
      std::string str = ss.str();
      //   new_mos.getMosName()= a;
      ss << nmos.getMosName() << "_finger" << str;

      new_mos.getMosName() = ss.str();
      new_mos.getSource() = nmos.getSource();
      new_mos.getGate() = nmos.getGate();
      new_mos.getDrain() = nmos.getDrain();
      new_mos.getWidth() = nmos.getWidth();
      pl_db.nmos_list().push_back(new_mos);

      index new_index = i + pl_db.nmos_ids().size();
      pl_db.nmos_ids().push_back(new_index);
    }
  }

  for(auto &pmos : pl_db.pmos_list()){
    if(pmos.getWidth() < 220 ){
      continue;
    }
    index n;
    n = std::ceil(pmos.getWidth() / 220);
    pmos.getWidth() = (float )std::round((pmos.getWidth()/(float)n) * 100)/100;

    for(index i = 1; i < n; i++){
      Mos new_mos;
      new_mos.getType() = 1;
      ss << i;
      std::string str = ss.str();
      //   new_mos.getMosName()= a;
      ss << pmos.getMosName() << "_finger" << str;

      new_mos.getMosName() = ss.str();
      new_mos.getSource() = pmos.getSource();
      new_mos.getGate() = pmos.getGate();
      new_mos.getDrain() = pmos.getDrain();
      new_mos.getWidth() = pmos.getWidth();
      pl_db.pmos_list().push_back(new_mos);

      index new_index = i + pl_db.pmos_ids().size();
      pl_db.pmos_ids().push_back(new_index);
    }
  }
}
