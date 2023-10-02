//
// Created by eric on 23-9-25.
//

#ifndef GIGACELL_GIGACELL_PARTITION_KAHYPAR_H_
#define GIGACELL_GIGACELL_PARTITION_KAHYPAR_H_
#include<memory>
#include<vector>
#include<iostream>
#include<libkahypar.h>
#include"placement/place_db.h"

namespace gigaplace {
class KaHyPar {
 public:
  explicit KaHyPar(PlaceDB &pl_db)
      : context_(kahypar_context_new()),
        ini_file_name_("../../../config/config.ini"),
        imbalance_(0.03),
        num_vertices_(pl_db.mos_list().size()),
        partition_(num_vertices_, -1),
        k_((int32_t)pl_db.mos_list().size()/4),
        objective_(0),
        pl_db_(pl_db) {}
  void partition();
 private:
  kahypar_context_t *context_{};
  const char *const ini_file_name_{};
  std::unique_ptr<kahypar_hyperedge_weight_t[]> hyperedge_weights_{};
  std::unique_ptr<size_t[]> hyperedge_indices_{};
  std::unique_ptr<kahypar_hyperedge_id_t[]> hyperedges_{};
  const double imbalance_{};
  const kahypar_hypernode_id_t num_vertices_{};
  kahypar_hyperedge_id_t num_hyperedges_{};
  std::vector<kahypar_partition_id_t> partition_{};
  const kahypar_partition_id_t k_{};
  kahypar_hyperedge_weight_t objective_{};
  PlaceDB &pl_db_;
};
}
#endif //GIGACELL_GIGACELL_PARTITION_KAHYPAR_H_
