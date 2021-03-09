//
// Created by fs on 1/25/21.
//

#pragma once

#include <string>

namespace ucfg {
namespace detail {

static constexpr char kDefaultStripChars[] = " \t\r\n";

/**
 * Strip function, delete the specified characters on both sides of the string.
 */

inline std::string &left_strip(std::string &s,
                        const std::string &characters = kDefaultStripChars) {
  return s.erase(0, s.find_first_not_of(characters));
}

inline std::string left_strip(const std::string &s,
                       const std::string &characters = kDefaultStripChars) {
  return std::string{s}.erase(0, s.find_first_not_of(characters));
}

inline std::string &right_strip(std::string &s,
                         const std::string &characters = kDefaultStripChars) {
  return s.erase(s.find_last_not_of(characters) + 1);
}

inline std::string right_strip(const std::string &s,
                        const std::string &characters = kDefaultStripChars) {
  return std::string{s}.erase(s.find_last_not_of(characters) + 1);
}

template <typename StrType>
inline std::string strip(StrType &&s,
                  const std::string &characters = kDefaultStripChars) {
  return right_strip(left_strip(std::forward<StrType>(s), characters),
                     characters);
}

}  // namespace detail
}  // namespace ucfg
