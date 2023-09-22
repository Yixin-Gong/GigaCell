#include "main.h"


int main(int argc, char *argv[]) {


    std::string filename = "/home/lky/case.txt";
    gigaplace::DataBase db;
    gigaplace::Parser parser(db, filename);    cmdline::parser a;
    a.add<std::string>("file_name", 'f', "file name", true, "");
    a.parse_check(argc, argv);

//    std::string filename = a.get<std::string>("file_name");
    parser.parse();
    gigaplace::PlaceDB pl_db(db);
    for (auto &item: pl_db.nets()) {
        std::cout << item.first << "\t";
        for (auto &kItem: item.second) {
            std::cout << kItem.idx << "\t" << kItem.type << "\t" << kItem.electrode_name << "\t" << std::endl;
        }
    }
    return 0;
}