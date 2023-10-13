#include "main.h"

int main(int argc, char *argv[]) {
  cmdline::parser a;
  a.add<std::string>("file_name", 'f', "file name", true, "");
  a.parse_check(argc, argv);
  std::string filename = a.get<std::string>("file_name");

  gigaplace::DataBase db;
  gigaplace::Parser parser(db, filename);
  parser.parse();

  gigaplace::PlaceDB pl_db(db);
  gigaplace::KaHyPar ka_hy_par(pl_db);
  ka_hy_par.partition();

  gigaplace::Cluster cluster(pl_db);
  for(auto &block_hash : pl_db.blocks()){
          cluster.getBlock(block_hash.second);
          cluster.creatConfigList();
          gigaplace::Operator::share(pl_db, cluster.config_list());
          cluster.clearConfigList();

      }

gigaplace::Operator::pairSingleMos(pl_db);
//
//  cluster.getBlock(pl_db.blocks().at(0));
//  cluster.creatConfigList();
//  for(auto &config : cluster.config_list()){
//      std::cout<<config.pair_list.at(0).nmos_idx<<' '<<config.pair_list.at(0).pmos_idx<<std::endl;
//
//  }
//  gigaplace::Operator::share(pl_db,cluster.config_list());
//  for(auto &config : pl_db.config_list()) {
//      std::cout << config.left_net0 << ' ' << config.left_net1<<std::endl;
//      std::cout<<config.right_net0 << ' ' << config.right_net1<< std::endl;
//      std::cout<<config.num_finger<<std::endl;
//      for(auto &pair : config.pair_list)
//          std::cout<<pair.nmos_idx<<' '<<pair.pmos_idx<<std::endl;
//      for(auto &pair : config.pair_list) {
//          std::cout <<pl_db.mos_list().at(pair.pmos_idx).getLeft()<<' '<<pl_db.mos_list().at(pair.pmos_idx).getRight()<<std::endl;
//          std::cout <<pl_db.mos_list().at(pair.nmos_idx).getLeft()<<' '<<pl_db.mos_list().at(pair.nmos_idx).getRight()<<std::endl;
//      }
//  }
//  cluster.clearConfigList();
//  cluster.getBlock(pl_db.blocks().at(1));
//  cluster.creatConfigList();
//  gigaplace::Operator::share(pl_db,cluster.config_list());
//    for(auto &config : pl_db.config_list()) {
//        std::cout << config.left_net0 << ' ' << config.left_net1<<std::endl;
//        std::cout<<config.right_net0 << ' ' << config.right_net1<< std::endl;
//        std::cout<<config.num_finger<<std::endl;
//        for(auto &pair : config.pair_list)
//            std::cout<<pair.nmos_idx<<' '<<pair.pmos_idx<<std::endl;
//        for(auto &pair : config.pair_list) {
//            std::cout <<pl_db.mos_list().at(pair.pmos_idx).getLeft()<<' '<<pl_db.mos_list().at(pair.pmos_idx).getRight()<<std::endl;
//            std::cout <<pl_db.mos_list().at(pair.nmos_idx).getLeft()<<' '<<pl_db.mos_list().at(pair.nmos_idx).getRight()<<std::endl;
//        }
//    }
//    for(auto &pair : pl_db.pair_list())
//        std::cout<<pair.pair_list.at(0).nmos_idx<<' '<<pair.pair_list.at(0).pmos_idx<<std::endl;
//    for(auto &single_mos_idx : pl_db.single_mos_ids())
//        std::cout<<single_mos_idx<<std::endl;

for(auto &mos : pl_db.mos_list()){


    std::cout<<mos.getLeft()<<' '<<mos.getRight()<<std::endl;
}


//  std::vector<gigaplace::index> index_list={0,1,2,3,4,5};
//  std::reverse(index_list.begin(), index_list.end());
//  for(auto &index : index_list)
//      std::cout << index<<std::endl;
//  std::cout<<' '<<std::endl;

//  std::cout<<cluster.config_list().at(0).left_net0<<std::endl;
//  gigaplace::Operator::configFlip(pl_db,cluster.config_list().at(0));
//  std::cout<<cluster.config_list().at(0).left_net0<<std::endl;

//  gigaplace::index a1=1;
//  std::cout<<pl_db.mos_list().at(a1).getLeft()<<std::endl;
//  gigaplace::Operator::mosFlip(pl_db, a1);
//  std::cout<<pl_db.mos_list().at(a1).getLeft()<<std::endl;


  //test creat config list from block
//  for (auto &config : cluster.config_list()) {
//    std::cout << config.pair_list.at << std::endl;
//    std::cout << config.right_net1 << std::endl;
//    for (auto &pair : config.pair_list) {
//      std::cout << pair.nmos_idx << ' ' << pair.pmos_idx << std::endl;
//    }
//  }

//  std::cout << cluster.config_list().at(0).left_net0<<std::endl;
//  gigaplace::Operator::configFlip(pl_db, cluster.config_list().at(0));
//  std::cout << cluster.config_list().at(0).left_net0<<std::endl;
//
//
//  for (auto index : pl_db.mos_ids())
//    std::cout << index << std::endl;


  //init mos loc
//  float loc = 0;
//  for (auto &nmos : pl_db.nmos_list()) {
//    nmos.getGateLoc() = loc;
//    nmos.getLeftLoc() = nmos.getGateLoc() - 0.5;
//    nmos.getRightLoc() = nmos.getGateLoc() + 0.5;
//    loc += 2;
//  }
//
//  loc = 0;
//  for (auto &pmos : pl_db.pmos_list()) {
//    pmos.getGateLoc() = loc;
//    pmos.getLeftLoc() = pmos.getGateLoc() - 0.5;
//    pmos.getRightLoc() = pmos.getGateLoc() + 0.5;
//    loc += 2;
//  }
//
//  auto loc = 0;
//  for (auto &mos : pl_db.mos_list()) {
//    mos.getGateLoc() = loc;
//    mos.getLeftLoc() = mos.getGateLoc() - 0.5;
//    mos.getRightLoc() = mos.getGateLoc() + 0.5;
//    loc += 2;
//  }


  //test  mos_swap and mos_flip
//  gigaplace::Operator::swap(pl_db.mos_list()[0], pl_db.mos_list()[9], pl_db.mos_ids()[0],
//                            pl_db.mos_ids()[9]);
//  gigaplace::Operator::mosFlip(pl_db.mos_list().at(0));
//  gigaplace::Operator::mosFlip(pl_db.mos_list().at(1));

//  for (auto &mos : pl_db.mos_list()) {
//    std::cout << mos.getMosName() << ' ' << mos.getType() << ' ' << mos.getLeft() << ' ' << mos.getGate() << ' '
//              << mos.getRight() << ' ' << mos.getLeftLoc() << ' ' << mos.getGateLoc() << ' '
//              << mos.getRightLoc() << ' ' << mos.getWidth() << ' ' << std::endl;
//  }
//

//  for (auto &nmos : pl_db.nmos_list()) {
//    std::cout << nmos.getMosName() << ' ' << nmos.getLeftLoc() << ' ' << nmos.getGateLoc() << ' '
//              << nmos.getRightLoc() << ' ' << nmos.getWidth() << std::endl;
//  }
//
//  for (auto &pmos : pl_db.pmos_list()) {
//    std::cout << pmos.getMosName() << ' ' << pmos.getLeftLoc() << ' ' << pmos.getGateLoc() << ' '
//              << pmos.getRightLoc() << ' ' << pmos.getWidth() << std::endl;
//  }
//


////test calculate net length
//  gigaplace::NetLength length(pl_db);
//  loc = length.netLength();
//  std::cout << loc << std::endl;
//

  //test calculate net area
//  gigaplace::Area area0(pl_db);
//  loc = area0.computeArea();
//  std::cout << loc << std::endl;

  //test map of nets
//  for (auto &item : pl_db.nets()) {
//    std::cout << item.first << "\t";
//    for (auto &kItem : item.second) {
//      std::cout << kItem.idx << "\t" << kItem.type << "\t" << kItem.electrode_name << "\t" << std::endl;
//    }
//  }
//
//  for (const auto &item : pl_db.mos_ids()) {
//    std::cout << item << " ";
//  }
  return 0;
}