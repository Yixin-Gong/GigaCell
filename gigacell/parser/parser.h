//
// Created by eric on 23-9-15.
//

#ifndef GIGACELL_GIGACELL_PARSER_PARSER_H_
#define GIGACELL_GIGACELL_PARSER_PARSER_H_

#include <utility>
#include "database/database.h"
#include <fstream>

namespace gigaplace {
class Parser {
 public:
  Parser(std::string filename, DataBase &db, std::string cellname) : filename_(std::move(filename)), file_(), db_(db),
                                                                     cell_name_(std::move(cellname)) {}
  void parse();

 private:
  std::string filename_;
  std::string cell_name_;
  std::ifstream file_;
  DataBase &db_;

  static std::vector<std::string> split_(const std::string &str, char delimiter);
};
}
#endif //GIGACELL_GIGACELL_PARSER_PARSER_H_
