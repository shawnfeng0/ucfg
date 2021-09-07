//
// Created by shawnfeng on 7/13/21.
// Copyright (c) 2021 shawnfeng. All rights reserved.
//
#pragma once

#ifdef __cplusplus

#include <ucfg/param/param_base.h>
#include <ucfg/param/param_default_data.h>

#define UCFG_DEFAULT_DATA_SECTION(manager) ucfg_default_data_section_##manager

// __attribute((__used__)) Prevent being optimized
#define UCFG_SECTION_DECLARE_(section) \
  __attribute((__section__(#section))) __attribute((__used__))
#define UCFG_SECTION_DECLARE(section) UCFG_SECTION_DECLARE_(section)

#define UCFG_CAT_(a, b) a##b
#define UCFG_CAT(a, b) UCFG_CAT_(a, b)
#define UCFG_SECTION_BEGIN(section) \
  UCFG_CAT(__start_, UCFG_DEFAULT_DATA_SECTION(section))
#define UCFG_SECTION_END(section) \
  UCFG_CAT(__stop_, UCFG_DEFAULT_DATA_SECTION(section))

// ucfg_manager uses functions to delay initialization of ucfg_manager
#define UCFG_DEFINE_PARAM_MANAGER(manager, file_path)                        \
  UCFG_EXPORT ucfg_manager *UCFG_ID(manager) {                               \
    extern const struct ucfg::DefaultDataNode *UCFG_SECTION_BEGIN(manager);  \
    extern const struct ucfg::DefaultDataNode *UCFG_SECTION_END(manager);    \
    static ucfg::ConfigManager manager_(                                     \
        file_path, ucfg::ConvertDefault2Config(&UCFG_SECTION_BEGIN(manager), \
                                               &UCFG_SECTION_END(manager))); \
    return reinterpret_cast<ucfg_manager *>(&manager_);                      \
  }                                                                          \
  struct hack

#define UCFG_DEFINE_PARAM(manager, type, section, name, default_value)    \
  static const struct ucfg::DefaultDataNode                               \
      _ucfg_register_##manager##section##name {                           \
    .key_ = #section "-" #name, .type_ = ucfg::DefaultDataNode::t_##type, \
    .value_ = {.UCFG_CAT(type, _value) = default_value}                   \
  };                                                                      \
  static const struct ucfg::DefaultDataNode                               \
      *_ucfg_register_##manager##section##name##p UCFG_SECTION_DECLARE(   \
          UCFG_DEFAULT_DATA_SECTION(manager)) =                           \
          &_ucfg_register_##manager##section##name;

#define UCFG_DEFINE_PARAM_BOOL(manager, section, name, default_value) \
  UCFG_DEFINE_PARAM(manager, bool, section, name, default_value)
#define UCFG_DEFINE_PARAM_INT(manager, section, name, default_value) \
  UCFG_DEFINE_PARAM(manager, int, section, name, default_value)
#define UCFG_DEFINE_PARAM_FLOAT(manager, section, name, default_value) \
  UCFG_DEFINE_PARAM(manager, float, section, name, default_value)

// Use (default_value "") to make sure it must be a literal string
#define UCFG_DEFINE_PARAM_STRING(manager, section, name, default_value) \
  UCFG_DEFINE_PARAM(manager, string, section, name, default_value "")

#endif  // __cplusplus
