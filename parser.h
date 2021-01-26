//
// Created by fs on 1/25/21.
//

#ifndef UCFG__PARSER_H_
#define UCFG__PARSER_H_

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>

#include "string_helper.h"

namespace ucfg {

using Result = std::map<std::string, std::map<std::string, std::string>>;

namespace detail {

inline bool ParserSection(const std::string& str, std::string& out) {
  const auto begin = str.find('[');
  const auto end = str.rfind(']');
  if (begin == std::string::npos || end == std::string::npos) {
    return false;
  }
  out = strip(str.substr(begin, end), " []");
  return true;
}

inline bool ParserPair(const std::string& str, std::string& key,
                       std::string& value) {
  auto pos = str.find('=');
  if (pos == std::string::npos) {
    return false;
  }
  key = strip(str.substr(0, pos - 0));
  value = strip(pos != str.length() ? str.substr(pos + 1) : "", " \"");
  return true;
}

inline bool ParserComment(const std::string& str, std::string& comment) {
  auto pos = str.find_first_of("#;");
  if (pos == std::string::npos) {
    return false;
  }
  comment = pos != str.length() ? str.substr(pos + 1) : "";
  return true;
}

Result Parser(std::istream& in_stream) {
  Result main_table;
  size_t line_num = 0;
  std::string line_str;
  std::string comment;
  std::string section;
  while (std::getline(in_stream, line_str)) {
    ++line_num;
    {
      if (ucfg::detail::ParserSection(line_str, section)) {
        // LOGGER_MULTI_TOKEN(line_num, "section",
        // line_str.c_str(), section.c_str());
        main_table.insert({section, {}});
        continue;
      }
    }

    {
      std::string key, value;
      if (ucfg::detail::ParserPair(line_str, key, value)) {
        // LOGGER_MULTI_TOKEN(line_num, "key-value",
        // line_str.c_str(), key.c_str(), value.c_str());
        main_table[section].emplace(key, value);
        continue;
      }
    }

    {
      // TODO: Comments are not supported temporarily
      if (ucfg::detail::ParserComment(line_str, comment)) {
        // LOGGER_MULTI_TOKEN(line_num, "comment",
        // line_str.c_str(), comment.c_str());
        continue;
      }
    }

    section = "";
    comment = "";
  }
  return main_table;
}

Result ParserFile(const std::string& filename) {
  std::ifstream ifs(filename.c_str(), std::ios_base::binary);
  if (!ifs.good()) {
    std::string e{std::string(__FILE__) + ":" + std::to_string(__LINE__) + " "};
    throw std::runtime_error(e + "parse: file open error -> " + filename);
  }
  return Parser(ifs);
}

std::string Dump(const Result& map) {
  std::string result;
  for (const auto& i : map) {
    if (i.first != "") {
      result += "[" + i.first + "]";
    }
    result += "\n";
    for (const auto& j : i.second) {
      result += j.first + " = " + j.second + "\n";
    }
    result += "\n";
  }
  result.pop_back();
  return result;
}

void DumpToFile(const std::string& filename, const Result& map) {
  std::ofstream ofs(filename.c_str(), std::ios_base::binary);
  if (!ofs.good()) {
    std::string e{std::string(__FILE__) + ":" + std::to_string(__LINE__) + " "};
    throw std::runtime_error(e + "dump to file: file open error -> " +
                             filename);
  }
  ofs << Dump(map);
}

}  // namespace detail
}  // namespace ucfg

#endif  // UCFG__PARSER_H_
