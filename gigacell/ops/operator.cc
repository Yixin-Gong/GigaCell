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
