//
// Created by eric on 23-9-21.
//

#ifndef GIGACELL_GIGACELL_OPS_OPERATOR_H_
#define GIGACELL_GIGACELL_OPS_OPERATOR_H_
#include "placement/place_db.h"
#include <algorithm>
#define CONFIG_HAD_BEEN_USED 0 //1/2 config had been used
//two pair flip 0
#define NO_FLIP 1//do without Flip
//two pair flip 4
#define CONFIGFLIP_C1_C2 2//mosFlip c1_0_1 c2_0_1
//two pair flip 1
#define MOSFLIP_C1P 3//mosFlip c1_1
#define MOSFLIP_C1N 4//mosFlip c1_0
#define MOSFLIP_C2P 5//mosFlip c2_1
#define MOSFLIP_C2N 6//mosFlip c2_0
//two pair flip 3
#define MOSFLIP_C1N_CONFIGFLIP_C2 7//mosFlip c1_0 configFlip c2
#define MOSFLIP_C1P_CONFIGFLIP_C2 8//mosFlip c1_1 configFlip c2
#define MOSFLIP_C2N_CONFIGFLIP_C1 9//mosFlip c2_0 configFlip c1
#define MOSFLIP_C2P_CONFIGFLIP_C1 10//mosFlip c2_1 configFlip c1
//two pair flip 2
#define MOSFLIP_C1P_C2P 11//mosFlip c1_1 c2_1
#define CONFIGFLIP_C2 12//configFlip c2
#define MOSFLIP_C1N_C2N 13//mosFlip c1_0 c2_0
#define CONFIGFLIP_C1 14//configFlip c1
#define MOSFLIP_C1P_C2N 15//mosFlip c1_1 c2_0
#define MOSFLIP_C1N_C2P 16//mosFlip c1_0 c2_1
//c1 pair c2 config

//c1 config c2 pair

//two config
#define COULD_NOT_SHARE 17//could not share



namespace gigaplace {
    class Operator {

    public:
        Operator() = default;

        static void mosFlip(PlaceDB &pl_db, index &mos_idx);

        static void configFlip(PlaceDB &pl_db, PlaceDB::Configuration &config);

        static void swap(PlaceDB &pl_db, index &pair1, index &pair2);

        static int32_t shouldShare(PlaceDB &pl_db, PlaceDB::Configuration &c1, PlaceDB::Configuration &c2);

        static void share(PlaceDB &pl_db, std::vector<PlaceDB::Configuration> &config_list);

        static void adjacentShare(PlaceDB &pl_db, index &pair);

        static void adjacentShareTwoSelectedPair(PlaceDB &pl_db,index &pair1,index &pair2);

        static void addConfig(PlaceDB &pl_db, std::vector<PlaceDB::Configuration> &config_list, index &mos1_idx, index &mos2_idx);

        static PlaceDB::Configuration creatTempConfig(PlaceDB &pl_db,PlaceDB::Configuration & c1 ,PlaceDB::Configuration & c2);

        static void pairSingleMos(PlaceDB &pl_db);

        static void v_configTol_config(gigaplace::PlaceDB &pl_db);

        static void setCoordinates(gigaplace::PlaceDB &pl_db, std::list<PlaceDB::Configuration> &l_config);

        static void createNewLayout(PlaceDB &pl_db, index &pair1, index &pair2);

        static void splitConfig(PlaceDB &pl_db,index &split_pair);

        static int32_t getShouldDo(PlaceDB &pl_db,PlaceDB::Configuration &c1,PlaceDB::Configuration &c2,std::vector<std::pair<std::string,index>> &v_special_mos_pair);

        static void fixConfigNet(PlaceDB &pl_db,PlaceDB::Configuration &c1,PlaceDB::Configuration &c2,std::pair<std::string,index> &special_mos);
    };


}
#endif //GIGACELL_GIGACELL_OPS_OPERATOR_H_
