//
// Created by fs on 1/25/21.
//

#ifndef UCFG__STRING_HELPER_H_
#define UCFG__STRING_HELPER_H_

#include <string>

namespace ucfg {

static constexpr char kDefaultStripCharacterSet[] = " \t\r\n";

/**
 * Strip function, delete the specified characters on both sides of the string.
 */

std::string &left_strip(
    std::string &s, const std::string &characters = kDefaultStripCharacterSet) {
  return s.erase(0, s.find_first_not_of(characters));
}

std::string left_strip(const std::string &s, const std::string &characters =
                                                 kDefaultStripCharacterSet) {
  return std::string{s}.erase(0, s.find_first_not_of(characters));
}

std::string &right_strip(
    std::string &s, const std::string &characters = kDefaultStripCharacterSet) {
  return s.erase(s.find_last_not_of(characters) + 1);
}

std::string right_strip(const std::string &s, const std::string &characters =
                                                  kDefaultStripCharacterSet) {
  return std::string{s}.erase(s.find_last_not_of(characters) + 1);
}

template <typename StrType>
std::string strip(StrType &&s,
                  const std::string &characters = kDefaultStripCharacterSet) {
  return right_strip(left_strip(std::forward<StrType>(s), characters),
                     characters);
}

}  // namespace ucfg

#endif  // UCFG__STRING_HELPER_H_
