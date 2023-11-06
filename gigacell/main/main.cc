#include "main.h"

int main(int argc, char *argv[]) {
  cmdline::parser a;
  a.add<std::string>("file_name", 'f', "file name", true, "");
  a.parse_check(argc, argv);
  std::string filename = a.get<std::string>("file_name");

  std::vector<gigaplace::DataBase> db;
  gigaplace::Parser parser(filename, db);
  parser.parse();

//  for(auto cell : db){
//    std::cout << cell.cell_name() << std::endl;
//    for(auto mos : cell.pmos_list()){
//      std::cout << mos.getMosName() << " " ;
//    }
//    std::cout << " " << std::endl;
//    for(auto mos : cell.nmos_list()){
//      std::cout << mos.getMosName() << " " ;
//    }
//    std::cout << " " << std::endl;
//  }

  for (auto current_db : db) {
    auto ref_width = current_db.getRefWidth();
    auto *current_pl_db = new gigaplace::PlaceDB(current_db);
    gigaplace::KaHyPar ka_hy_par(*current_pl_db);
    ka_hy_par.partition();
    gigaplace::Cluster cluster(*current_pl_db);
    for (auto &block_hash : (*current_pl_db).blocks()) {
      cluster.getBlock(block_hash.second);
      cluster.creatConfigList();
      gigaplace::Operator::share(*current_pl_db, cluster.config_list());
      for (auto &config : cluster.config_list()) {
        if (!config.share_flag)
          (*current_pl_db).v_config().push_back(config);
      }
      cluster.clearConfigList();
    }
    gigaplace::Operator::pairSingleMos(*current_pl_db);
    auto index = 0;
    for (auto &config : (*current_pl_db).v_config()) {
      for (auto &pair : config.pair_list) {
        pair.pair_idx = index;
        index++;
      }
    }
//    for (auto &config : (*current_pl_db).v_config()) {
//      for (auto &pair : config.pair_list)
//        std::cout << pair.pair_idx << std::endl;
//    }
    gigaplace::Operator::v_configTol_config(*current_pl_db);

    auto giga_place = new gigaplace::GigaPlace(*current_pl_db,ref_width,10000000);
    giga_place->SAPlace(index - 1);

    gigaplace::writer::exporter(*current_pl_db);
    delete giga_place;
    delete current_pl_db;

  }




//  for(auto current_db : db){
//    gigaplace::PlaceDB pl_db(current_db);
//    gigaplace::KaHyPar ka_hy_par(pl_db);
//    ka_hy_par.partition();
//  }

/*
gigaplace::Cluster cluster(pl_db);
for (auto &block_hash : pl_db.blocks()) {
  cluster.getBlock(block_hash.second);
  cluster.creatConfigList();
  gigaplace::Operator::share(pl_db, cluster.config_list());
  for (auto &config : cluster.config_list()) {
    if (!config.share_flag)
      pl_db.v_config().push_back(config);
  }
  cluster.clearConfigList();

}

gigaplace::Operator::pairSingleMos(pl_db);
auto index = 0;
for (auto &config : pl_db.v_config()) {
  for (auto &pair : config.pair_list) {
    pair.pair_idx = index;
    index++;
  }
}
for (auto &config : pl_db.v_config()) {
  for (auto &pair : config.pair_list)
    std::cout << pair.pair_idx << std::endl;
}

gigaplace::Operator::v_configTol_config(pl_db);
//  gigaplace::Operator::setCoordinates(pl_db,pl_db.l_config());
gigaplace::index p1=4;
gigaplace::index p2=5;
//gigaplace::Operator::createNewLayout(pl_db,p1,p2);
gigaplace::Operator::splitConfig(pl_db,p1);
//  std::cout<<pl_db.pair_list().size()<<std::endl;
*/
//for(auto &config : pl_db.v_config())
//  std::cout<<config.pair_list.size()<<std::endl;
//
//  cluster.getBlock(pl_db.blocks().at(0));
//  cluster.creatConfigList();
//  for(auto &config : cluster.v_config()){
//      std::cout<<config.pair_list.at(0).nmos_idx<<' '<<config.pair_list.at(0).pmos_idx<<std::endl;
//
//  }
//  gigaplace::Operator::share(pl_db,cluster.v_config());
//  for(auto &config : pl_db.v_config()) {
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
//  gigaplace::Operator::share(pl_db,cluster.v_config());
//    for(auto &config : pl_db.v_config()) {
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


/*
for(auto &mos : pl_db.mos_list()){


    std::cout<<mos.getLeft()<<' '<<mos.getRight()<<std::endl;
}
std::list<int32_t> list1={10,20,30,40,50};
auto it=list1.begin();
auto left_of_begin = std::prev(list1.begin());
std::advance(it ,2);
auto left = std::prev(it);
auto right = std::next(it);
auto insertHere = list1.begin();
std::advance(insertHere,4);
list1.insert(insertHere,60);
list1.insert(insertHere,70);

list1.erase(right);
list1.erase(it);
if(left != left_of_begin)
        list1.erase(left);


*/
//std::cout<<*it1<<std::endl;
//std::advance(it,4);
//auto leftIt=std::prev(it);
//auto rightIt=std::next(it);
//auto insertHere=list1.begin();
//
//list1.insert(insertHere,45);
//list1.insert(insertHere,46);
//list1.erase(it);
//list1.erase(leftIt);
//
//for(auto &i : list1)
//    std::cout<<i<<std::endl;

//list1.erase(rightIt);
//std::advance(it1,1);
//auto it2=list1.begin();
//std::advance(it2,3);
//std::swap(*it1,*it2);


//  std::vector<gigaplace::index> index_list={0,1,2,3,4,5};
//  std::reverse(index_list.begin(), index_list.end());
//  for(auto &index : index_list)
//      std::cout << index<<std::endl;
//  std::cout<<' '<<std::endl;

//  std::cout<<cluster.v_config().at(0).left_net0<<std::endl;
//  gigaplace::Operator::configFlip(pl_db,cluster.v_config().at(0));
//  std::cout<<cluster.v_config().at(0).left_net0<<std::endl;

//  gigaplace::index a1=1;
//  std::cout<<pl_db.mos_list().at(a1).getLeft()<<std::endl;
//  gigaplace::Operator::mosFlip(pl_db, a1);
//  std::cout<<pl_db.mos_list().at(a1).getLeft()<<std::endl;


//test creat config list from block
//  for (auto &config : cluster.v_config()) {
//    std::cout << config.pair_list.at << std::endl;
//    std::cout << config.right_net1 << std::endl;
//    for (auto &pair : config.pair_list) {
//      std::cout << pair.nmos_idx << ' ' << pair.pmos_idx << std::endl;
//    }
//  }

//  std::cout << cluster.v_config().at(0).left_net0<<std::endl;
//  gigaplace::Operator::configFlip(pl_db, cluster.v_config().at(0));
//  std::cout << cluster.v_config().at(0).left_net0<<std::endl;
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
