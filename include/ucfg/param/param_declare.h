//
// Created by shawnfeng on 7/13/21.
// Copyright (c) 2021 shawnfeng. All rights reserved.
//
#pragma once

#include <ucfg/param/param_base.h>

#define UCFG_DECLARE_PARAM_MANAGER(manager)                                    \
  UCFG_EXPORT ucfg_manager *UCFG_ID(manager);                                  \
  static inline void manager##_erase_all() {                                   \
    ucfg_erase_all(UCFG_ID(manager));                                          \
  }                                                                            \
  static inline void manager##_get_string(                                     \
      const char *key, const char *default_value, char *out_str,               \
      size_t out_max_length) {                                                 \
    ucfg_get_string(UCFG_ID(manager), key, default_value, out_str,             \
                    out_max_length);                                           \
  }                                                                            \
  static inline void manager##_save_string(const char *key,                    \
                                           const char *value) {                \
    ucfg_save_string(UCFG_ID(manager), key, value);                            \
  }                                                                            \
  static inline bool manager##_is_number(const char *key) {                    \
    return ucfg_is_number(UCFG_ID(manager), key);                              \
  }                                                                            \
  static inline int manager##_get_int(const char *key, int default_value) {    \
    return ucfg_get_int(UCFG_ID(manager), key, default_value);                 \
  }                                                                            \
  static inline void manager##_save_int(const char *key, int value) {          \
    ucfg_save_int(UCFG_ID(manager), key, value);                               \
  }                                                                            \
  static inline bool manager##_is_boolean(const char *key) {                   \
    return ucfg_is_boolean(UCFG_ID(manager), key);                             \
  }                                                                            \
  static inline bool manager##_get_bool(const char *key, bool default_value) { \
    return ucfg_get_bool(UCFG_ID(manager), key, default_value);                \
  }                                                                            \
  static inline void manager##_save_bool(const char *key, bool value) {        \
    ucfg_save_bool(UCFG_ID(manager), key, value);                              \
  }                                                                            \
  static inline float manager##_get_float(const char *key,                     \
                                          float default_value) {               \
    return ucfg_get_float(UCFG_ID(manager), key, default_value);               \
  }                                                                            \
  static inline void manager##_save_float(const char *key, float value) {      \
    ucfg_save_float(UCFG_ID(manager), key, value);                             \
  }                                                                            \
  struct hack

#define UCFG_DECLARE_PARAM(manager, type, param_section, name)             \
  static inline type manager##_get_##param_section##_##name() {            \
    return ucfg_get_##type(UCFG_ID(manager), #param_section "-" #name, 0); \
  }                                                                        \
  static inline void manager##_save_##param_section##_##name(type value) { \
    ucfg_save_##type(UCFG_ID(manager), #param_section "-" #name, value);   \
  }                                                                        \
  struct hack

#define UCFG_DECLARE_PARAM_BOOL(manager, section, name) \
  UCFG_DECLARE_PARAM(manager, bool, section, name)
#define UCFG_DECLARE_PARAM_INT(manager, section, name) \
  UCFG_DECLARE_PARAM(manager, int, section, name)
#define UCFG_DECLARE_PARAM_FLOAT(manager, section, name) \
  UCFG_DECLARE_PARAM(manager, float, section, name)

#define UCFG_DECLARE_PARAM_STRING(manager, section, name)                     \
  static inline void manager##_get_##section##_##name(char *out_str,          \
                                                      size_t size) {          \
    ucfg_get_string(UCFG_ID(manager), #section "-" #name, "", out_str, size); \
  }                                                                           \
  static inline void manager##_save_##section##_##name(const char *value) {   \
    ucfg_save_string(UCFG_ID(manager), #section "-" #name, value);            \
  }                                                                           \
  struct hack
