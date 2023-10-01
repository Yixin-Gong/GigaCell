//
// Created by eric on 23-9-21.
//

#ifndef GIGACELL_GIGACELL_OPS_OPERATOR_H_
#define GIGACELL_GIGACELL_OPS_OPERATOR_H_

#include "database/database.h"
#include <limits>
#define NAME(a,b)  #a "_finger" #b;

namespace gigaplace {
    class Operator {

    public:
        Operator() = default;

        static void flip(Mos &mos);

        static void swap(Mos &mos1, Mos &mos2, index &index1, index &index2);

        static void fold(DataBase &db);
    };
}
#endif //GIGACELL_GIGACELL_OPS_OPERATOR_H_
