//
// Created by shawnfeng on 2021/9/8.
//

#pragma once

#include <map>
#include <string>

namespace ucfg {

class ConfigData
    : public std::map<std::string, std::map<std::string, std::string>> {
 public:
  ConfigData& merge_new(const ConfigData& r) {
    for (const auto& i : r) {
      // Use the [] operator, add it if it does not exist
      auto& section = this->operator[](i.first);
      for (const auto& j : i.second) {
        section[j.first] = j.second;
      }
    }
    return *this;
  }
};

}  // namespace ucfg
