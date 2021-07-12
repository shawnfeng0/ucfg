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

  const char *key_;
  enum Type type_;
  union Value value_;
};

static inline ConfigData ConvertDefault2Config(const DefaultDataNode **begin,
                                               const DefaultDataNode **end) {
  static_assert(std::is_trivial<ucfg::DefaultDataNode>::value,
                "Not a trivial struct.");
  ConfigData result;
  for (auto node = begin; node < end; node++) {
    std::string section, name;
    std::tie(section, name) =
        ucfg::detail::split_two_string((*node)->key_, "-");
    switch ((*node)->type_) {
      case DefaultDataNode::t_bool: {
        result[section][name] = (*node)->value_.bool_value ? "true" : "false";
      } break;
      case DefaultDataNode::t_int: {
        result[section][name] = std::to_string((*node)->value_.int_value);
      } break;
      case DefaultDataNode::t_float:
        result[section][name] = std::to_string((*node)->value_.float_value);
        break;
      case DefaultDataNode::t_string:
        result[section][name] =
            (*node)->value_.string_value ? (*node)->value_.string_value : "";
        break;
    }
  }
  return result;
}

}  // namespace ucfg
