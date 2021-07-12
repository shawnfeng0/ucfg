//
// Created by shawnfeng on 7/2/21.
// Copyright (c) 2021 shawnfeng. All rights reserved.
//
#pragma once

#include <ucfg/ucfg.h>

namespace ucfg {

struct DefaultDataNode {
  union Value {
    bool bool_value;
    int int_value;
    float float_value;
    const char *string_value;
  };

  enum Type {
    t_bool,
    t_int,
    t_float,
    t_string,
  };

  Type get_type() const { return type_; }
  const char *get_key() const { return key_; }
  bool as_bool() const { return value_.bool_value; }
  int as_int() const { return value_.int_value; }
  float as_float() const { return value_.float_value; }
  const char *as_string() const { return value_.string_value; }

  const char *key_;
  enum Type type_;
  union Value value_;
};

static inline ConfigData ConvertDefault2Config(const DefaultDataNode *begin,
                                               const DefaultDataNode *end) {
  static_assert(std::is_trivial<ucfg::DefaultDataNode>::value,
                "Not a trivial struct.");
  ConfigData result;
  for (auto node = begin; node < end; node++) {
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
