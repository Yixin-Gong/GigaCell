//
// Created by eric on 23-9-25.
//

#include "kahypar.h"
void gigaplace::KaHyPar::partition() {
//  context_ = kahypar_context_new();
  kahypar_configure_context_from_file(context_, "/path/to/config.ini");
  kahypar_set_seed(context_, 42);

//  const kahypar_hypernode_id_t num_vertices = 7;
//  const kahypar_hyperedge_id_t num_hyperedges = 4;
//  std::unique_ptr<kahypar_hyperedge_weight_t[]> hyperedge_weights = std::make_unique<kahypar_hyperedge_weight_t[]>(4);

  // force the cut to contain hyperedge 0 and 2
  hyperedge_weights_[0] = 1;
  hyperedge_weights_[1] = 1000;
  hyperedge_weights_[2] = 1;
  hyperedge_weights_[3] = 1000;

//  std::unique_ptr<size_t[]> hyperedge_indices = std::make_unique<size_t[]>(5);

  hyperedge_indices_[0] = 0;
  hyperedge_indices_[1] = 2;
  hyperedge_indices_[2] = 6;
  hyperedge_indices_[3] = 9;
  hyperedge_indices_[4] = 12;

//  std::unique_ptr<kahypar_hyperedge_id_t[]> hyperedges = std::make_unique<kahypar_hyperedge_id_t[]>(12);

  // hypergraph from hMetis manual page 14
  hyperedges_[0] = 0;
  hyperedges_[1] = 2;
  hyperedges_[2] = 0;
  hyperedges_[3] = 1;
  hyperedges_[4] = 3;
  hyperedges_[5] = 4;
  hyperedges_[6] = 3;
  hyperedges_[7] = 4;
  hyperedges_[8] = 6;
  hyperedges_[9] = 2;
  hyperedges_[10] = 5;
  hyperedges_[11] = 6;

//  const double imbalance = 0.03;
//  const kahypar_partition_id_t k = 2;

//  kahypar_hyperedge_weight_t objective = 0;

//  std::vector<kahypar_partition_id_t> partition_(num_vertices_, -1);

  kahypar_partition(num_vertices_, num_hyperedges_,
                    imbalance_, k_,
      /*vertex_weights */ nullptr, hyperedge_weights_.get(),
                    hyperedge_indices_.get(), hyperedges_.get(),
                    &objective_, context_, partition_.data());

  for (int i = 0; i != num_vertices_; ++i) {
    std::cout << i << ":" << partition_[i] << std::endl;
  }

  kahypar_context_free(context_);
}
