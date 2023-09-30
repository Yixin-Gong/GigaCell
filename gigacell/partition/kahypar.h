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
  KaHyPar()
      : context_(kahypar_context_new()),
        ini_file_name_(),
        hyperedge_weights_(std::make_unique<kahypar_hyperedge_weight_t[]>(4)),
        hyperedge_indices_(std::make_unique<size_t[]>(5)),
        hyperedges_(std::make_unique<kahypar_hyperedge_id_t[]>(12)),
        imbalance_(0.03),
        num_vertices_(),
        num_hyperedges_(),
        partition_(num_vertices_, -1),
        k_() {}
  void partition();
 private:
  kahypar_context_t *context_{};
  const std::string ini_file_name_{};
  std::unique_ptr<kahypar_hyperedge_weight_t[]> hyperedge_weights_{};
  std::unique_ptr<size_t[]> hyperedge_indices_{};
  std::unique_ptr<kahypar_hyperedge_id_t[]> hyperedges_{};
  const double imbalance_{};
  const kahypar_hypernode_id_t num_vertices_{};
  const kahypar_hyperedge_id_t num_hyperedges_{};
  std::vector<kahypar_partition_id_t> partition_{};
  const kahypar_partition_id_t k_{};
  kahypar_hyperedge_weight_t objective_{};
};
}
#endif //GIGACELL_GIGACELL_PARTITION_KAHYPAR_H_
