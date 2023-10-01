//
// Created by eric on 23-9-21.
//

#ifndef GIGACELL_GIGACELL_OPS_OPERATOR_H_
#define GIGACELL_GIGACELL_OPS_OPERATOR_H_

#include "database/database.h"

namespace gigaplace {
    class Operator {

    public:
        Operator() = default;

        static void flip(Mos &mos);

        static void swap(Mos &mos1, Mos &mos2, index &index1, index &index2);

        static void fold(DataBase &db);

        //TODO:Implement pairing and sharing.@zy and lky

        static bool isFold();

        static bool shouldFold();

        static void sharing_by_pair();

        static void pairing();

        static Mos createDummy();

        static bool isSingle();
    };
}
#endif //GIGACELL_GIGACELL_OPS_OPERATOR_H_
