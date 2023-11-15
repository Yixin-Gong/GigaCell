#include "main.h"

int main(int argc, char *argv[]) {
  auto start_time_total = std::chrono::high_resolution_clock::now();
  cmdline::parser a;
  a.add<std::string>("file_name", 'n', "file name", true, "");
  a.add<std::string>("cell_name", 'c', "cell name", true, "");
  a.parse_check(argc, argv);
  std::string filename = a.get<std::string>("file_name");
  std::string cellname = a.get<std::string>("cell_name");
  gigaplace::DataBase db{};
  gigaplace::Parser parser(filename, db, cellname);
  parser.parse();
  auto ref_width = db.getRefWidth();
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
  gigaplace::Operator::v_configTol_config((current_pl_db).v_config(), (current_pl_db).l_config());
  auto giga_place = new gigaplace::GigaPlace(current_pl_db, ref_width, 10000000);
  if (!gigaplace::GigaPlace::isPlace(current_pl_db, current_pl_db.v_config()))
    giga_place->MLASPlace(index - 1, current_pl_db);
  else
    giga_place->GDUTPlace(index - 1);
  gigaplace::Writer writer(current_pl_db,cellname);
  writer.output();
  delete giga_place;
  auto end_time = std::chrono::high_resolution_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time_total);
  std::cout << "Total runtime is " << (double) duration.count() / 1000000.0f << "s" << std::endl;
  return 0;
}
