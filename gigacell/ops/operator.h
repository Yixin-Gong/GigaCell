//
// Created by eric on 23-9-21.
//

#ifndef GIGACELL_GIGACELL_OPS_OPERATOR_H_
#define GIGACELL_GIGACELL_OPS_OPERATOR_H_

#include "placement/place_db.h"

namespace gigaplace {
    class Operator {

    public:
        Operator() = default;

        static void flip(Mos &mos);

        static void swap(Mos &mos1, Mos &mos2, index &index1, index &index2);

    };
}
#endif //GIGACELL_GIGACELL_OPS_OPERATOR_H_
