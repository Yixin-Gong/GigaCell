//
// Created by eric on 23-9-21.
//

#include "mos_flip.h"
namespace gigaplace {
    void MosFlip::flip() {
        if (mos_.getDrainLoc() - mos_.getSourceLoc() > 0) {
            mos_.getDrainLoc() = mos_.getDrainLoc() - 1;
            mos_.getSourceLoc() = mos_.getSourceLoc() + 1;
        } else {
            mos_.getDrainLoc() = mos_.getDrainLoc() + 1;
            mos_.getSourceLoc() = mos_.getSourceLoc() - 1;

        }

    }
}