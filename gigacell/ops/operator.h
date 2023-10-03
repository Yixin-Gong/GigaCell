//
// Created by eric on 23-9-21.
//

#ifndef GIGACELL_GIGACELL_OPS_OPERATOR_H_
#define GIGACELL_GIGACELL_OPS_OPERATOR_H_
//
//#include "database/database.h"
#include "placement/place_db.h"
#include <algorithm>

namespace gigaplace {
    class Operator {

    public:
        Operator() = default;

        static bool shouldFlip(Configuration &config1, Configuration &config2);

        static void mosFlip(PlaceDB &pl_db, index &mos_idx);

        static void configFlip(PlaceDB &pl_db, Configuration &config);

        static void swap(PlaceDB &pl_db, index &index1, index &index2);

        //TODO:Implement pairing and sharing.@zy and lky

        static bool shouldShare(PlaceDB &pl_db, Configuration &c1, Configuration &c2);

        static void share(PlaceDB &pl_db, std::vector<Configuration> &config_list);

        static void addConfig(PlaceDB &pl_db, std::vector<Configuration> &config_list, index &mos1_idx, index &mos2_idx);

        static void createDummy(PlaceDB &pl_db, std::vector<Configuration> &config_list,index &single_mos);

    };
}
#endif //GIGACELL_GIGACELL_OPS_OPERATOR_H_
