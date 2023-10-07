//
// Created by zy on 23-10-2.
//

#ifndef GIGACELL_GIGACELL_OPS_CLUSTER_H_
#define GIGACELL_GIGACELL_OPS_CLUSTER_H_
#include"placement/place_db.h"
#include "operator.h"
namespace gigaplace {

class Cluster {
 public:
  explicit Cluster(PlaceDB &pl_db) : pl_db_(pl_db){}
  std::vector<PlaceDB::Configuration> &config_list() {return config_list_;}

  void creatConfigList();
  void clearConfigList();
  void getBlock(std::vector<index> &block);

 private:
  std::vector<PlaceDB::Configuration> config_list_{};
  PlaceDB &pl_db_;
  std::vector<index> block_;

};
}
#endif //GIGACELL_GIGACELL_OPS_CLUSTER_H_
