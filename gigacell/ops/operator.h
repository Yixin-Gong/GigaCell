//
// Created by eric on 23-9-21.
//

#ifndef GIGACELL_GIGACELL_OPS_OPERATOR_H_
#define GIGACELL_GIGACELL_OPS_OPERATOR_H_
//
#include "database/database.h"
#include "placement/place_db.h"

namespace gigaplace {
    class Operator {

    public:
        Operator() = default;

        static void flip(index &mos_idx,PlaceDB &pl_db);

        static void swap(PlaceDB &pl_db, index &index1, index &index2);

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
