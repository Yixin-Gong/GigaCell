//
// Created by eric on 23-9-21.
//

#ifndef GIGACELL_GIGACELL_OPS_OPERATOR_H_
#define GIGACELL_GIGACELL_OPS_OPERATOR_H_
#include "placement/place_db.h"
#include <algorithm>

namespace gigaplace {
    class Operator {

    public:
        Operator() = default;

        static void mosFlip(PlaceDB &pl_db, index &mos_idx);

        static void configFlip(PlaceDB &pl_db, PlaceDB::Configuration &config);

        static void swap(PlaceDB &pl_db, index &pair1, index &pair2);

        //TODO:Implement pairing and sharing.@zy and lky

        static std::string shouldShare(PlaceDB &pl_db, PlaceDB::Configuration &c1, PlaceDB::Configuration &c2);

        static void share(PlaceDB &pl_db, std::vector<PlaceDB::Configuration> &config_list);

        static void adjacentShare(PlaceDB &pl_db, index &pair);

        static void addConfig(PlaceDB &pl_db, std::vector<PlaceDB::Configuration> &config_list, index &mos1_idx, index &mos2_idx);

        static void createDummy(PlaceDB &pl_db, PlaceDB::Configuration &config_pair,index &single_idx);

        static PlaceDB::Configuration creatTempConfig(PlaceDB &pl_db,PlaceDB::Configuration & c1 ,PlaceDB::Configuration & c2);

        static void pairSingleMos(PlaceDB &pl_db);

        static void v_configTol_config(gigaplace::PlaceDB &pl_db);

        static void setCoordinates(gigaplace::PlaceDB &pl_db, std::list<PlaceDB::Configuration> &l_config);

        static void createNewLayout(PlaceDB &pl_db, index &pair1, index &pair2);

        static void splitConfig(PlaceDB &pl_db,index &split_pair);
    };
}
#endif //GIGACELL_GIGACELL_OPS_OPERATOR_H_
