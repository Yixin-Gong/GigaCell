//
// Created by eric on 23-9-25.
//

#include "kahypar.h"
void gigaplace::KaHyPar::partition() {
  kahypar_configure_context_from_file(context_, ini_file_name_);
  kahypar_set_seed(context_, 42);
  auto idx1 = 0;
  auto idx2 = 1;
  ulong num = 0;
  for (auto &kNet : pl_db_.nets()) {
    num += kNet.second.size();
    idx2++;
    for (auto &kMos : kNet.second) {
      idx1++;
    }
  }
  hyperedges_ = std::make_unique<kahypar_hyperedge_id_t[]>(num);
  hyperedge_indices_ = std::make_unique<size_t[]>(idx2);
  num_hyperedges_ = idx2 - 1;
  hyperedge_weights_ = std::make_unique<kahypar_hyperedge_weight_t[]>(idx2 - 1);

  idx1 = 0;
  idx2 = 1;
  num = 0;
  hyperedge_indices_[0] = 0;
  for (auto &kNet : pl_db_.nets()) {
    num += kNet.second.size();
    hyperedge_indices_[idx2] = num;
//    std::cout << idx2 << ' ' << hyperedge_indices_[idx2] << std::endl;
    for (auto &kMos : kNet.second) {
      if (kMos.type == 0)
        hyperedges_[idx1] = kMos.idx;
      else
        hyperedges_[idx1] = kMos.idx + pl_db_.nmos_list().size();
      //set high weight to those have gate net
      if (kMos.electrode_name == "gate")
        hyperedge_weights_[idx2 - 1] = 1000;
      else
        hyperedge_weights_[idx2 - 1] = 1;
      idx1++;
    }
    idx2++;
  }

  kahypar_partition(num_vertices_, num_hyperedges_,
                    imbalance_, k_,
      /*vertex_weights */ nullptr, hyperedge_weights_.get(),
                    hyperedge_indices_.get(), hyperedges_.get(),
                    &objective_, context_, partition_.data());

  for (int i = 0; i != num_vertices_; i++) {
    std::vector<index> ids;
    if (pl_db_.blocks().find(partition_[i]) == pl_db_.blocks().end()) {
      pl_db_.blocks().emplace(partition_[i], ids);
      pl_db_.blocks().find(partition_[i])->second.emplace_back(i);
    } else{
      pl_db_.blocks().find(partition_[i])->second.emplace_back(i);
    }
//    std::cout << i << ":" << partition_[i] << std::endl;
  }

  kahypar_context_free(context_);
}
