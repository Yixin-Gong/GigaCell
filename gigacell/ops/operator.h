//
// Created by eric on 23-9-21.
//

#ifndef GIGACELL_GIGACELL_OPS_OPERATOR_H_
#define GIGACELL_GIGACELL_OPS_OPERATOR_H_
//
//#include "database/database.h"
#include "placement/place_db.h"

namespace gigaplace {
    class Operator {

    public:
        Operator() = default;

        static void flip(index &mos_idx,PlaceDB &pl_db);

        static void swap(PlaceDB &pl_db, index &index1, index &index2);

//        static void fold(DataBase &db);

        //TODO:Implement pairing and sharing.@zy and lky

        static bool isFold();

        static bool shouldShare(PlaceDB &pl_db, Configuration &c1, Configuration &c2);

        static void share();

        static void creatConfig(index &mos1_idx, index &mos2_idx, std::vector<Configuration> &config_list, PlaceDB &pl_db);

        static Mos createDummy(index &single_mos , PlaceDB &pl_db, std::vector<Configuration> &config_list);

        static bool isSingle();
    };
}
#endif //GIGACELL_GIGACELL_OPS_OPERATOR_H_
