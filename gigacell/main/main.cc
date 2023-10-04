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

  gigaplace::Cluster clu(pl_db, pl_db.blocks().at(0));
  clu.creatConfigList();

//  std::cout<<clu.config_list().at(0).left_net0<<std::endl;
//  gigaplace::Operator::configFlip(pl_db,clu.config_list().at(0));
//  std::cout<<clu.config_list().at(0).left_net0<<std::endl;

  gigaplace::index a1=1;
  std::cout<<pl_db.mos_list().at(a1).getLeft()<<std::endl;
  gigaplace::Operator::mosFlip(pl_db, a1);
  std::cout<<pl_db.mos_list().at(a1).getLeft()<<std::endl;


  //test creat config list from block
  for (auto &config : clu.config_list()) {
//    std::cout << config.pair_list.at << std::endl;
//    std::cout << config.right_net1 << std::endl;
    for (auto &pair : config.pair_list) {
      std::cout << pair.nmos_idx << ' ' << pair.pmos_idx << std::endl;
    }
  }

  std::cout << clu.config_list().at(0).left_net0<<std::endl;
  gigaplace::Operator::configFlip(pl_db, clu.config_list().at(0));
  std::cout << clu.config_list().at(0).left_net0<<std::endl;


  for (auto index : pl_db.mos_ids())
    std::cout << index << std::endl;


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