//
// Created by eric on 23-9-21.
//

#include "mos_swap.h"

namespace gigaplace {
    void MosSwap::swap() {
        if (mos1_.getType() != mos2_.getType()) {
            return;
        }

        index idx;
        idx = index2_;
        index2_ = index1_;
        index1_ = idx;

        float loc;
        loc = mos2_.getGateLoc();
        mos2_.getGateLoc() = mos1_.getGateLoc();
        mos1_.getGateLoc() = loc;

        loc = mos2_.getDrainLoc();
        mos2_.getDrainLoc() = mos1_.getDrainLoc();
        mos1_.getDrainLoc() = loc;

        loc = mos2_.getSourceLoc();
        mos2_.getSourceLoc() = mos1_.getSourceLoc();
        mos1_.getSourceLoc() = loc;

    }
}