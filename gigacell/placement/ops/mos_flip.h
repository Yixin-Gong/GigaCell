//
// Created by eric on 23-9-21.
//

#ifndef GIGACELL_GIGACELL_PLACEMENT_OPS_MOS_FLIP_H_
#define GIGACELL_GIGACELL_PLACEMENT_OPS_MOS_FLIP_H_

#include "database/mos.h"
namespace gigaplace {
    class MosFlip {
    public:
        explicit MosFlip(Mos &mos) : mos_(mos) {}

        void flip();

    private:
        Mos &mos_;
    };
}
#endif //GIGACELL_GIGACELL_PLACEMENT_OPS_MOS_FLIP_H_
