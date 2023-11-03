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
  DataBase::Pin pin;
  DataBase cell_db;
  std::string subStr;
  int32_t pmos_idx = 0;
  int32_t nmos_idx = 0;
  std::string line;


  while (std::getline(file_, line)) {
    std::vector<std::string> tokens = split_(line, ' ');
    if (tokens[0] == ".SUBCKT") {
      cell_db.cell_name() = tokens[1];
      for (int32_t i = 2; i < tokens.size() - 2; i++) {
        pin.pinName = tokens[i];
        cell_db.v_pin_list().push_back(pin);
      }
      continue;
    }
    if (tokens[0].at(0) == '.' && tokens[0].at(1) == 'E') {
      total_db_.push_back(cell_db);
      pmos_idx = 0;
      nmos_idx = 0;
   //   cell_db.clearDB();
      std::vector <index>().swap(cell_db.nmos_ids());
      std::vector <index>().swap(cell_db.pmos_ids());
      std::vector <Mos>().swap(cell_db.nmos_list());
      std::vector <Mos>().swap(cell_db.pmos_list());
      std::vector <DataBase::Pin>().swap(cell_db.v_pin_list());
      cell_db.cell_name().clear();
      continue;
    }
    std::string mos_initial;
    mos_initial = tokens[5].substr(0, 1);
    if (mos_initial == "n") {
      std::string w_initial;
      w_initial = tokens[6].substr(0, 1);
      if (w_initial == "W" || w_initial == "w") {
        std::string num_str;
        for (char c : tokens[6]) {
          if (isdigit(c) || c == '.')
            num_str += c;
        }
        std::string w_end;
        w_end = tokens[6].substr(tokens[6].size() - 1, 1);
        float width;
        std::istringstream iss(num_str);
        iss >> width;
        if (w_end == "u") {
          mos.getWidth() = width * 1000;
        } else {
          mos.getWidth() = width;
        }
      } else {
        std::string num_str;
        for (char c : tokens[7]) {
          if (isdigit(c) || c == '.')
            num_str += c;
        }

        std::string w_end;
        if (tokens[7].substr(tokens[7].size() - 1) == "\r")
          w_end = tokens[7].substr(tokens[7].size() - 2, 1);
        else
          w_end = tokens[7].substr(tokens[7].size() - 1, 1);

        float width;
        std::istringstream iss(num_str);
        iss >> width;
        if (w_end == "u") {
          mos.getWidth() = width * 1000;
        } else {
          mos.getWidth() = width;
        }
      }
      subStr = tokens[0].substr(1);
      mos.getMosName() = subStr;
      mos.getRight() = tokens[3];
      mos.getGate() = tokens[2];
      mos.getLeft() = tokens[1];
      mos.getType() = 0;
      //mos.getWidth()=
      cell_db.nmos_list().push_back(mos);
      cell_db.nmos_ids().push_back(nmos_idx);
      nmos_idx++;
    } else {
      //pmos
      std::string w_initial;
      w_initial = tokens[6].substr(0, 1);
      if (w_initial == "W" || w_initial == "w") {
        std::string num_str;
        for (char c : tokens[6]) {
          if (isdigit(c) || c == '.')
            num_str += c;
        }
        std::string w_end;
        w_end = tokens[6].substr(tokens[6].size() - 1, 1);
        float width;
        std::istringstream iss(num_str);
        iss >> width;
        if (w_end == "u") {
          mos.getWidth() = width * 1000;
        } else {
          mos.getWidth() = width;
        }
      } else {
        std::string num_str;
        for (char c : tokens[7]) {
          if (isdigit(c) || c == '.')
            num_str += c;
        }

        std::string w_end;
        if (tokens[7].at(tokens[7].size()-1) == '\r')
          w_end = tokens[7].substr(tokens[7].size() - 2, 1);
        else
          w_end = tokens[7].substr(tokens[7].size() - 1, 1);

        float width;
        std::istringstream iss(num_str);
        iss >> width;
        if (w_end == "u") {
          mos.getWidth() = width * 1000;
        } else {
          mos.getWidth() = width;
        }
      }
      subStr = tokens[0].substr(1);
      mos.getMosName() = subStr;
      mos.getRight() = tokens[3];
      mos.getGate() = tokens[2];
      mos.getLeft() = tokens[1];
      mos.getType() = 1;
      //mos.getWidth()=
      cell_db.pmos_list().push_back(mos);
      cell_db.pmos_ids().push_back(pmos_idx);
      pmos_idx++;
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
