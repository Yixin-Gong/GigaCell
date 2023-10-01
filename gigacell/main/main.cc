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
//  float loc = 0;
//  for (auto &nmos : pl_db.nmos_list()) {
//    nmos.getGateLoc() = loc;
//    nmos.getSourceLoc() = nmos.getGateLoc() - 0.5;
//    nmos.getDrainLoc() = nmos.getGateLoc() + 0.5;
//    loc += 2;
//  }
//
//  loc = 0;
//  for (auto &pmos : pl_db.pmos_list()) {
//    pmos.getGateLoc() = loc;
//    pmos.getSourceLoc() = pmos.getGateLoc() - 0.5;
//    pmos.getDrainLoc() = pmos.getGateLoc() + 0.5;
//    loc += 2;
//  }
//
//  loc = 0;
//  for (auto &mos : pl_db.mos_list()) {
//    mos.getGateLoc() = loc;
//    mos.getSourceLoc() = mos.getGateLoc() - 0.5;
//    mos.getDrainLoc() = mos.getGateLoc() + 0.5;
//    loc += 2;
//  }

//  gigaplace::Operator::swap(pl_db.mos_list()[0], pl_db.mos_list()[9], pl_db.mos_ids()[0],
//                            pl_db.mos_ids()[9]);
//  gigaplace::Operator::flip(pl_db.mos_list().at(0));
//  gigaplace::Operator::flip(pl_db.mos_list().at(1));

//  for (auto &mos : pl_db.mos_list()) {
//    std::cout << mos.getMosName() << ' ' << mos.getType() << ' ' << mos.getSource() << ' ' << mos.getGate() << ' '
//              << mos.getDrain() << ' ' << mos.getSourceLoc() << ' ' << mos.getGateLoc() << ' '
//              << mos.getDrainLoc() << ' ' << mos.getWidth() << ' ' << std::endl;
//  }
//

//  for (auto &nmos : pl_db.nmos_list()) {
//    std::cout << nmos.getMosName() << ' ' << nmos.getSourceLoc() << ' ' << nmos.getGateLoc() << ' '
//              << nmos.getDrainLoc() << ' ' << nmos.getWidth() << std::endl;
//  }
//
//  for (auto &pmos : pl_db.pmos_list()) {
//    std::cout << pmos.getMosName() << ' ' << pmos.getSourceLoc() << ' ' << pmos.getGateLoc() << ' '
//              << pmos.getDrainLoc() << ' ' << pmos.getWidth() << std::endl;
//  }
//
//  gigaplace::NetLength length(pl_db);
//  loc = length.netLength();
//  std::cout << loc << std::endl;
//  gigaplace::Area area0(pl_db);
//  loc = area0.computeArea();
//  std::cout << loc << std::endl;
//
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