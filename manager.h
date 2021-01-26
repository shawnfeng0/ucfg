//
// Created by fs on 2021-01-26.
//

#ifndef UCFG__MANAGER_H_
#define UCFG__MANAGER_H_

#include "parser.h"

namespace ucfg {

class Manager {
 private:
  const std::string filename_;
  Result data_;

 public:
  Manager(const std::string& filename, bool open = true)
      : filename_(filename),
        data_(open ? ucfg::detail::ParserFile(filename) : Result{}) {}

  auto ReloadFile() -> decltype(*this) {
    data_ = ucfg::detail::ParserFile(filename_);
    return *this;
  }

  template <typename T>
  void Visit(const T& visitor) const {
    for (const auto& sections : data_)
      for (const auto& key_value : sections.second)
        visitor(sections.first, key_value.first, key_value.second);
  }

  template <typename T>
  void Visit(const std::string& section, const T& visitor) const {
    if (Contains(section))
      for (const auto& j : data_.at(section)) visitor(j.first, j.second);
  }

  bool Contains(const std::string& section, const std::string& key) const {
    return data_.count(section) && data_.at(section).count(key);
  }

  bool Contains(const std::string& section) const {
    return data_.count(section) != 0;
  }

  auto SetString(const std::string& section, const std::string& key,
                 const std::string& value) -> decltype(*this) {
    data_[section][key] = value;
    return *this;
  }

  auto SetInteger(const std::string& section, const std::string& key,
                  long value) -> decltype(*this) {
    SetString(section, key, std::to_string(value));
    return *this;
  }

  auto SetDouble(const std::string& section, const std::string& key,
                 double value) -> decltype(*this) {
    SetString(section, key, std::to_string(value));
    return *this;
  }

  auto SetBool(const std::string& section, const std::string& key, bool value)
      -> decltype(*this) {
    SetString(section, key, value ? "true" : "false");
    return *this;
  }

  std::string GetString(const std::string& section, const std::string& key,
                        const std::string& default_value = "") const {
    return Contains(section, key) ? data_.at(section).at(key) : default_value;
  }

  long GetInteger(const std::string& section, const std::string& name,
                  long default_value = 0) const {
    std::string value_str = GetString(section, name, "");
    const char* value = value_str.c_str();
    char tmp, *end = &tmp;  // Any value other than nullptr
    // This parses "1234" (decimal) and also "0x4D2" (hex)
    long n = strtol(value, &end, 0);
    return end > value ? n : default_value;
  }

  double GetDouble(const std::string& section, const std::string& key,
                   double default_value = 0) const {
    std::string value_str = GetString(section, key, "");
    const char* value = value_str.c_str();
    char tmp, *end = &tmp;  // Any value other than nullptr
    double n = strtod(value, &end);
    return end > value ? n : default_value;
  }

  bool GetBool(const std::string& section, const std::string& key,
                  bool default_value = false) const {
    std::string str = GetString(section, key, "");
    // Convert to lower case to make string comparisons case-insensitive
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    if (str == "true" || str == "yes" || str == "on" || str == "1")
      return true;
    else if (str == "false" || str == "no" || str == "off" || str == "0")
      return false;
    else
      return default_value;
  }

  auto Clear() -> decltype(*this) {
    data_.clear();
    return *this;
  }

  std::string Dump() const { return ::ucfg::detail::Dump(data_); }
  auto DumpToFile() const -> decltype(*this) {
    ::ucfg::detail::DumpToFile(filename_, data_);
    return *this;
  }
  auto DumpToFile(const std::string& filename) const -> decltype(*this) {
    ::ucfg::detail::DumpToFile(filename, data_);
    return *this;
  }

 private:
  // Hide
  Result& get_data() { return data_; }
  auto set_data(const Result& data) -> decltype(*this) {
    if (&data != &data_) data_ = data;
    return *this;
  }
};
}  // namespace ucfg

#endif  // UCFG__MANAGER_H_
