//
// Created by eric on 23-9-15.
//

#include "parser/parser.h"
#include <sstream>

void gigaplace::Parser::parse() {
  file_.open(filename_);
  if (!file_.is_open()) {
    std::cerr << "Failed to open file" << filename_ << std::endl;
    return;
  }
  Mos mos;
  std::string subStr;
  int32_t pmos_idx = 0;
  int32_t nmos_idx = 0;
  std::string line;
  while (std::getline(file_, line)) {
    std::vector<std::string> tokens = split_(line, ' ');
    if (tokens[0] == ".SUBCKT")
      continue;
    if (tokens[0] == ".ENDS")
      break;
    if (tokens[4] == "VDD") {
      std::string numStr;
      for (char c : tokens[6]) {
        if (isdigit(c) || c == '.')
          numStr += c;
      }
      float width;
      std::istringstream iss(numStr);
      iss >> width;
      mos.getWidth() = width;
      subStr = tokens[0].substr(1);
      mos.getMosName() = subStr;
      mos.getDrain() = tokens[3];
      mos.getGate() = tokens[2];
      mos.getSource() = tokens[1];
      mos.getType() = 1;
      //mos.getWidth()=
      db_.pmos_list().push_back(mos);
      db_.pmos_ids().push_back(pmos_idx);
      pmos_idx++;

    } else {
      std::string numStr;
      for (char c : tokens[6]) {
        if (isdigit(c) || c == '.')
          numStr += c;
      }
      float width;
      std::istringstream iss(numStr);
      iss >> width;
      mos.getWidth() = width;
      subStr = tokens[0].substr(1);
      mos.getMosName() = subStr;
      mos.getDrain() = tokens[3];
      mos.getGate() = tokens[2];
      mos.getSource() = tokens[1];
      mos.getType() = 0;
      //mos.getWidth()=
      db_.nmos_list().push_back(mos);
      db_.nmos_ids().push_back(nmos_idx);
      nmos_idx++;
    }

  }
  file_.close();
}

std::vector<std::string> gigaplace::Parser::split_(const std::string &str, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(str);
  while (getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}
