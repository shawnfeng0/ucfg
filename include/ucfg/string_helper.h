//
// Created by fs on 1/25/21.
//

#pragma once

#include <string>
#include <tuple>

namespace ucfg {
namespace detail {

static constexpr char kDefaultStripChars[] = " \t\r\n";

/**
 * Strip function, delete the specified characters on both sides of the string.
 */

inline std::string &left_strip(
    std::string &s, const std::string &characters = kDefaultStripChars) {
  return s.erase(0, s.find_first_not_of(characters));
}

inline std::string left_strip(
    const std::string &s, const std::string &characters = kDefaultStripChars) {
  return std::string{s}.erase(0, s.find_first_not_of(characters));
}

inline std::string &right_strip(
    std::string &s, const std::string &characters = kDefaultStripChars) {
  return s.erase(s.find_last_not_of(characters) + 1);
}

inline std::string right_strip(
    const std::string &s, const std::string &characters = kDefaultStripChars) {
  return std::string{s}.erase(s.find_last_not_of(characters) + 1);
}

template <typename StrType>
inline std::string strip(StrType &&s,
                         const std::string &characters = kDefaultStripChars) {
  return right_strip(left_strip(std::forward<StrType>(s), characters),
                     characters);
}

inline std::tuple<std::string, std::string> split_two_string(
    const std::string &str, const std::string &delimiter) {
  using StringPair = std::tuple<std::string, std::string>;
  std::string left;
  std::string right;
  auto pos = str.find(delimiter);
  if (pos == std::string::npos) {
    return StringPair{"", str};
  }
  left = str.substr(0, pos);
  right = str.substr(pos + delimiter.length());
  return StringPair{left, right};
}

}  // namespace detail
}  // namespace ucfg
