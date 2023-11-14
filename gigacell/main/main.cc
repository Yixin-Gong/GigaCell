#include "main.h"

int main(int argc, char *argv[]) {
  cmdline::parser a;
  a.add<std::string>("file_name", 'f', "file name", true, "");
  a.add<std::string>("cell_name", 'c', "cell name", true, "");

  a.parse_check(argc, argv);
  std::string filename = a.get<std::string>("file_name");
  std::string cellname = a.get<std::string>("cell_name");
  gigaplace::DataBase db{};
  gigaplace::Parser parser(filename, db, cellname);
  parser.parse();
    auto ref_width = db.getRefWidth();
//    auto *current_pl_db = new gigaplace::PlaceDB(db);
  gigaplace::PlaceDB current_pl_db(db);
    gigaplace::Cluster cluster(current_pl_db);

      cluster.getBlock((current_pl_db).mos_ids());
      cluster.creatConfigList();

      for (auto &config : cluster.config_list()) {
        if (!config.share_flag)
          (current_pl_db).v_config().push_back(config);
      }
      cluster.clearConfigList();
    gigaplace::Operator::pairSingleMos(current_pl_db);
    auto index = 0;
    for (auto &config : (current_pl_db).v_config()) {
      for (auto &pair : config.pair_list) {
        pair.pair_idx = index;
        index++;
      }
    }
    gigaplace::Operator::v_configTol_config((current_pl_db).v_config(),(current_pl_db).l_config());

    auto giga_place = new gigaplace::GigaPlace(current_pl_db,ref_width,10000000);
//    giga_place->SAPlace(index - 1,current_pl_db);
//    giga_place->GDUTPlace(index-1);
    giga_place->GPlace(index-1);
//    giga_place->MLASPlace(index-1,current_pl_db);
//    giga_place->MLASPlace(index-1,current_pl_db);
//    giga_place->MLASPlace(index-1,current_pl_db);
    gigaplace::writer::exporter(current_pl_db);
    delete giga_place;
//    delete current_pl_db;


//  cmdline::parser a;
//  a.add<std::string>("file_name", 'f', "file name", true, "");
//  a.parse_check(argc, argv);
//  std::string filename = a.get<std::string>("file_name");
//
//  std::vector<gigaplace::DataBase> db;
//  gigaplace::Parser parser(filename, db);
//  parser.parse();
//  for (auto current_db : db) {
//    if(current_db.cell_name() != "EDFD2")
//      continue;
//
//    auto ref_width = current_db.getRefWidth();
//    auto *current_pl_db = new gigaplace::PlaceDB(current_db);
//
//    gigaplace::Cluster cluster(*current_pl_db);
//
//      cluster.getBlock((*current_pl_db).mos_ids());
//      cluster.creatConfigList();
//
//      for (auto &config : cluster.config_list()) {
//        if (!config.share_flag)
//          (*current_pl_db).v_config().push_back(config);
//      }
//      cluster.clearConfigList();
//    gigaplace::Operator::pairSingleMos(*current_pl_db);
//    auto index = 0;
//    for (auto &config : (*current_pl_db).v_config()) {
//      for (auto &pair : config.pair_list) {
//        pair.pair_idx = index;
//        index++;
//      }
//    }
//    gigaplace::Operator::v_configTol_config((*current_pl_db).v_config(),(*current_pl_db).l_config());
//
//    auto giga_place = new gigaplace::GigaPlace(*current_pl_db,ref_width,10000000);
//    giga_place->SAPlace(index - 1,*current_pl_db);
//
//    gigaplace::writer::exporter(*current_pl_db);
//    delete giga_place;
//    delete current_pl_db;
//    break;
//  }

  return 0;
}
