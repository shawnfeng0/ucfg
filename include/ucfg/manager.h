//
// Created by shawnfeng on 2021-01-26.
//

#pragma once

#include <sys/stat.h>
#include <ucfg/config_data.h>
#include <ucfg/internal/file.h>
#include <ucfg/internal/file_storage.h>
#include <ucfg/internal/parser.h>

#include <algorithm>
#include <mutex>
#include <utility>

namespace ucfg {

class ConfigManager {
 public:
  explicit ConfigManager(const std::string& filename,
                         ConfigData default_data = {})
      : file_storage_(filename), default_data_(std::move(default_data)) {
    ReloadFile();
  }

  auto ReloadFile() -> decltype(*this) {
    std::lock_guard<std::mutex> lg(lock_);
    return LoadFileLocked();
  }

  auto ReloadFileIfUpdate() -> decltype(*this) {
    std::lock_guard<std::mutex> lg(lock_);
    if (file_storage_.IsModifiedByExternal()) {
      return LoadFileLocked();
    } else {
      return *this;
    }
  }

  template <typename T>
  void Visit(const T& visitor) const {
    std::lock_guard<std::mutex> lg(lock_);
    for (const auto& sections : data_)
      for (const auto& key_value : sections.second)
        visitor(sections.first, key_value.first, key_value.second);
  }

  template <typename T>
  void Visit(const std::string& section, const T& visitor) const {
    std::lock_guard<std::mutex> lg(lock_);
    if (data_.count(section) != 0) {
      for (const auto& j : data_.at(section)) visitor(j.first, j.second);
    }
  }

  bool Contains(const std::string& section, const std::string& key) const {
    std::lock_guard<std::mutex> lg(lock_);
    return data_.count(section) && data_.at(section).count(key);
  }

  bool Contains(const std::string& section) const {
    std::lock_guard<std::mutex> lg(lock_);
    return data_.count(section) != 0;
  }

  auto SetString(const std::string& section, const std::string& key,
                 const std::string& value) -> decltype(*this) {
    std::lock_guard<std::mutex> lg(lock_);
    data_[section][key] = value;
    return *this;
  }

  auto SetInteger(const std::string& section, const std::string& key,
                  long value) -> decltype(*this) {
    return SetString(section, key, std::to_string(value));
  }

  auto SetDouble(const std::string& section, const std::string& key,
                 double value) -> decltype(*this) {
    return SetString(section, key, std::to_string(value));
  }

  auto SetBool(const std::string& section, const std::string& key, bool value)
      -> decltype(*this) {
    return SetString(section, key, value ? "true" : "false");
  }

  std::string GetString(const std::string& section, const std::string& key,
                        const std::string& default_value = "") const {
    std::lock_guard<std::mutex> lg(lock_);
    return (data_.count(section) && data_.at(section).count(key))
               ? data_.at(section).at(key)
               : default_value;
  }

  long GetInteger(const std::string& section, const std::string& name,
                  long default_value = 0) const {
    std::string value_str = GetString(section, name, "");
    char* end;
    // This parses "1234" (decimal) and also "0x4D2" (hex)
    long n = strtol(value_str.c_str(), &end, 0);
    return end > value_str.c_str() ? n : default_value;
  }

  double GetDouble(const std::string& section, const std::string& key,
                   double default_value = 0) const {
    std::string value_str = GetString(section, key, "");
    char* end;
    double n = strtod(value_str.c_str(), &end);
    return end > value_str.c_str() ? n : default_value;
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

  bool IsNumber(const std::string& section, const std::string& key) const {
    std::string str = GetString(section, key, "");
    int dot_number = 0;
    // All numbers
    if (!str.empty() &&
        str.size() == static_cast<std::size_t>(
                          std::count_if(str.cbegin(), str.cend(),
                                        [&](char c) {
                                          if (c == '.') dot_number++;
                                          return std::isdigit(c) || c == '.';
                                        })) &&
        dot_number < 2) {
      return true;
    }
    return false;
  }

  bool IsBoolean(const std::string& section, const std::string& key) const {
    std::string str = GetString(section, key, "");
    // Convert to lower case to make string comparisons case-insensitive
    std::transform(str.begin(), str.end(), str.begin(), ::tolower);
    if (str == "true" || str == "false") return true;
    return false;
  }

  auto RestoreDefault() -> decltype(*this) {
    std::lock_guard<std::mutex> lg(lock_);
    data_ = default_data_;
    return *this;
  }

  std::string Dump() const {
    std::lock_guard<std::mutex> lg(lock_);
    return internal::Dump(data_);
  }

  auto Save() -> decltype(*this) {
    std::lock_guard<std::mutex> lg(lock_);
    file_storage_.SaveData(data_);
    return *this;
  }

  auto SaveTo(const std::string& filename) const -> decltype(*this) {
    std::lock_guard<std::mutex> lg(lock_);
    internal::DumpSyncToFile(filename, data_);
    return *this;
  }

  ConfigData get_data() const {
    std::lock_guard<std::mutex> lg(lock_);
    return data_;
  }

 private:
  auto LoadFileLocked() -> decltype(*this) {
    data_ = ConfigData(default_data_).merge_new(file_storage_.LoadData());
    return *this;
  }

  mutable std::mutex lock_{};

  internal::FileStorage file_storage_;

  const ConfigData default_data_;
  ConfigData data_;
};

}  // namespace ucfg
