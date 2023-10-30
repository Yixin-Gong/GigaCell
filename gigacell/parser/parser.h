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
  Parser(std::string filename, std::vector<DataBase> &total_db) : filename_(std::move(filename)), file_(), total_db_(total_db) {}

  void parse();

 private:
  std::string filename_;
  std::ifstream file_;
  std::vector<DataBase> &total_db_;

  static std::vector<std::string> split_(const std::string &str, char delimiter);
};
}
#endif //GIGACELL_GIGACELL_PARSER_PARSER_H_
