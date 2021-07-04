//
// Created by shawnfeng on 7/2/21.
// Copyright (c) 2021 shawnfeng. All rights reserved.
//
#pragma once

#include "ucfg/internal/intrusive_list.h"
#include "ucfg/param/param_default_data.h"
#include "ucfg/ucfg.h"

namespace ucfg {

class DefaultDataNode : public internal::ListNode<DefaultDataNode *> {
 private:
  union Value {
    explicit Value(bool value) : bool_value(value){};
    explicit Value(int value) : int_value(value){};
    explicit Value(float value) : float_value(value){};
    explicit Value(const char *value) : string_value(value){};
    bool bool_value;
    int int_value;
    float float_value;
    const char *string_value;
  };

 public:
  enum Type {
    t_bool,
    t_int,
    t_float,
    t_string,
  };
  DefaultDataNode(const char *key, bool value) noexcept
      : key_(key), type_(t_bool), value_{value} {}
  DefaultDataNode(const char *key, int value) noexcept
      : key_(key), type_(t_int), value_{value} {}
  DefaultDataNode(const char *key, float value) noexcept
      : key_(key), type_(t_float), value_{value} {}
  DefaultDataNode(const char *key, const char *value) noexcept
      : key_(key), type_(t_string), value_(value) {}

  Type get_type() const { return type_; }
  const char *get_key() const { return key_; }
  bool as_bool() const { return value_.bool_value; }
  int as_int() const { return value_.int_value; }
  float as_float() const { return value_.float_value; }
  const char *as_string() const { return value_.string_value; }

 private:
  const char *key_;
  enum Type type_;
  union Value value_;
};

using DefaultDataList = internal::List<DefaultDataNode *>;

static inline ConfigData ConvertDefault2Config(
    const DefaultDataList &data_list) {
  ConfigData result;
  for (auto node : data_list) {
    std::string section, name;
    std::tie(section, name) =
        ucfg::detail::split_two_string(node->get_key(), "-");
    switch (node->get_type()) {
      case DefaultDataNode::t_bool:
        result[section][name] = node->as_bool() ? "true" : "false";
        break;
      case DefaultDataNode::t_int:
        result[section][name] = std::to_string(node->as_int());
        break;
      case DefaultDataNode::t_float:
        result[section][name] = std::to_string(node->as_float());
        break;
      case DefaultDataNode::t_string:
        result[section][name] = node->as_string() ? node->as_string() : "";
        break;
    }
  }
  return result;
}

}  // namespace ucfg
