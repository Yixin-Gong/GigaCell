//
// Created by eric on 23-9-21.
//

#ifndef GIGACELL_GIGACELL_PLACEMENT_OPS_MOS_SWAP_H_
#define GIGACELL_GIGACELL_PLACEMENT_OPS_MOS_SWAP_H_

#include "placement/place_db.h"

namespace gigaplace {
    class MosSwap {
    public:
        MosSwap(Mos &mos1, Mos &mos2, index &index1, index &index2) : mos1_(mos1), mos2_(mos2), index1_(index1), index2_(index2){}

        void swap();

    private:
        //  PlaceDB &db_;
        Mos &mos1_;
        Mos &mos2_;
        index &index1_;
        index &index2_;
    };
}


#endif //GIGACELL_GIGACELL_PLACEMENT_OPS_MOS_SWAP_H_
