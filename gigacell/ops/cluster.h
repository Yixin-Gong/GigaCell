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
  Cluster(PlaceDB &pl_db,std::vector<index> &block) : pl_db_(pl_db),block_(block){}
  std::vector<Configuration> &config_list() {return config_list_;}

  void creatConfigList();
  void clearConfigList();


 private:
  std::vector<Configuration> config_list_{};
  PlaceDB &pl_db_;
  std::vector<index> &block_;

};
}
#endif //GIGACELL_GIGACELL_OPS_CLUSTER_H_
