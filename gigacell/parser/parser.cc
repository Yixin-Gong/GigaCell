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
  index flag_name = 0;

  while (std::getline(file_, line)) {
    std::vector<std::string> tokens = split_(line, ' ');
    if (tokens[0] == ".SUBCKT") {
      if (tokens[1] != cell_name_)
        continue;
      flag_name = 1;
      db_.cell_name() = tokens[1];

      auto size = tokens.size();
      if(tokens[size -1] == "\r"){
        for(int32_t i = 2; i < tokens.size()-1; i++){
          if(tokens[i] == "VDD" || tokens[i] == "VSS" )
            continue;
          db_.v_pin_list().push_back(tokens[i]);
        }
      }else{
        for(int32_t i =2; i < tokens.size(); i++){
          if(tokens[i] == "VDD" || tokens[i] == "VSS" || tokens[i] == "VDD\r" || tokens[i] == "VSS\r")
            continue;
          if(i == tokens.size() - 1){
            db_.v_pin_list().push_back(tokens[i].substr(0,tokens[i].size() - 1));
            continue;
          }
          db_.v_pin_list().push_back(tokens[i]);
        }
      }
      continue;
    }

      if (tokens[0].at(0) == '.' && tokens[0].at(1) == 'E' && flag_name == 1) {
        break;
      }
      if (tokens[0].at(0) == '.' && tokens[0].at(1) == 'E') {
        continue;
      }
      // std::string first = tokens[0].substr(0,1);
      if (db_.cell_name() == cell_name_) {
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
          db_.nmos_list().push_back(mos);
          db_.nmos_ids().push_back(nmos_idx);
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
            if (tokens[7].at(tokens[7].size() - 1) == '\r')
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
          db_.pmos_list().push_back(mos);
          db_.pmos_ids().push_back(pmos_idx);
          pmos_idx++;
        }
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
