#include "main.h"

int main(int argc, char *argv[]) {


  //std::string filename = "/home/lky/case.txt";

  cmdline::parser a;
  a.add<std::string>("file_name", 'f', "file name", true, "");
  a.parse_check(argc, argv);
  std::string filename = a.get<std::string>("file_name");
  gigaplace::DataBase db;
  gigaplace::Parser parser(db, filename);
  parser.parse();
  gigaplace::PlaceDB pl_db(db);

  float loc = 0;
  for (auto &nmos : pl_db.nmos_list()) {
    nmos.getGateLoc() = loc;
    nmos.getSourceLoc() = nmos.getGateLoc() - 0.5;
    nmos.getDrainLoc() = nmos.getGateLoc() + 0.5;
    loc += 2;
  }

  loc = 0;
  for (auto &pmos : pl_db.pmos_list()) {
    pmos.getGateLoc() = loc;
    pmos.getSourceLoc() = pmos.getGateLoc() - 0.5;
    pmos.getDrainLoc() = pmos.getGateLoc() + 0.5;
    loc += 2;
  }

  for(auto &nmos : pl_db.nmos_list()){
    std::cout << ' ' << nmos.getSourceLoc() << ' ' << nmos.getGateLoc() << ' ' << nmos.getDrainLoc() << std::endl;
  }

  for(auto &pmos : pl_db.pmos_list()){
    std::cout << ' ' << pmos.getSourceLoc() << ' ' << pmos.getGateLoc() << ' ' << pmos.getDrainLoc() << std::endl;
  }

  gigaplace::NetLength length(pl_db);
  loc = length.netLength();
  std::cout << loc << std::endl;
  gigaplace::Area area0(pl_db);
  loc = area0.computeArea();
  std:: cout << loc << std::endl;

  for (auto &item : pl_db.nets()) {
    std::cout << item.first << "\t";
    for (auto &kItem : item.second) {
      std::cout << kItem.idx << "\t" << kItem.type << "\t" << kItem.electrode_name << "\t" << std::endl;
    }
  }

  return 0;
}