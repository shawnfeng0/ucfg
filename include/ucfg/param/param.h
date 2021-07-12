#pragma once

#include <stdbool.h>
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef void ucfg_manager;
void ucfg_erase_all(ucfg_manager *manager);

void ucfg_get_string(ucfg_manager *manager, const char *key,
                     const char *default_value, char *out_str,
                     size_t out_max_length);
void ucfg_save_string(ucfg_manager *manager, const char *key,
                      const char *value);

bool ucfg_is_number(ucfg_manager *manager, const char *key);
int ucfg_get_int(ucfg_manager *manager, const char *key, int default_value);
void ucfg_save_int(ucfg_manager *manager, const char *key, int value);

bool ucfg_is_boolean(ucfg_manager *manager, const char *key);
bool ucfg_get_bool(ucfg_manager *manager, const char *key, bool default_value);
void ucfg_save_bool(ucfg_manager *manager, const char *key, bool value);

float ucfg_get_float(ucfg_manager *manager, const char *key,
                     float default_value);
void ucfg_save_float(ucfg_manager *manager, const char *key, float value);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#define UCFG_EXPORT extern "C"
#else
#define UCFG_EXPORT
#endif

#define UCFG_ID(manager_name) ucfg_##manager_name()

#define UCFG_DEFAULT_DATA_SECTION(manager) ucfg_default_data_##manager

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

#ifdef __cplusplus
#include "param_default_data.h"

// ucfg_manager uses functions to delay initialization of ucfg_manager
#define UCFG_DEFINE_PARAM_MANAGER(manager, file_path)                         \
  extern struct ucfg::DefaultDataNode UCFG_SECTION_BEGIN(manager);            \
  extern struct ucfg::DefaultDataNode UCFG_SECTION_END(manager);              \
  UCFG_EXPORT ucfg_manager *UCFG_ID(manager) {                                \
    static auto *manager_ = reinterpret_cast<ucfg_manager *>(                 \
        new ucfg::ConfigManager(file_path, ucfg::ConvertDefault2Config(       \
                                               &UCFG_SECTION_BEGIN(manager),  \
                                               &UCFG_SECTION_END(manager)))); \
    return manager_;                                                          \
  }                                                                           \
  struct hack

#define UCFG_DEFINE_PARAM(manager, type, section, name, default_value)        \
  static struct ucfg::DefaultDataNode _ucfg_register_##manager##section##name \
  UCFG_SECTION_DECLARE(UCFG_DEFAULT_DATA_SECTION(manager)) {                  \
    .key_ = #section "-" #name, .type_ = (ucfg::DefaultDataNode::t_##type),   \
    .value_ {                                                                 \
      .UCFG_CAT(type, _value) = (default_value)                               \
    }                                                                         \
  }

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
