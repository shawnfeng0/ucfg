#pragma once

#include <stdbool.h>
#include <stddef.h>

#include "param_default_data.h"

/*
# Config File example:

[database]
file = payroll.dat
port = 143
server = 192.0.2.62


# Set param:

ucfg_save_int("database-port", 143);
ucfg_save_string("database-server", "192.0.2.62");
// use...


# Get param:

int port = ucfg_get_int("database-port", 120);
char server[16];
ucfg_get_string("database-port", "", server, sizeof(server));
// use...

*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Create ucfg manager
 * @return
 */
struct ucfg_manager *ucfg_create_manager(
    const char *config_path, struct ucfg_default_data *default_data);
void ucfg_erase_all(struct ucfg_manager *manager);

void ucfg_get_string(struct ucfg_manager *manager, const char *key,
                     const char *default_value, char *out_str,
                     size_t out_max_length);
void ucfg_save_string(struct ucfg_manager *manager, const char *key,
                      const char *value);

bool ucfg_is_number(struct ucfg_manager *manager, const char *key);
int ucfg_get_int(struct ucfg_manager *manager, const char *key,
                 int default_value);
void ucfg_save_int(struct ucfg_manager *manager, const char *key, int value);

bool ucfg_is_boolean(struct ucfg_manager *manager, const char *key);
bool ucfg_get_bool(struct ucfg_manager *manager, const char *key,
                   bool default_value);
void ucfg_save_bool(struct ucfg_manager *manager, const char *key, bool value);

float ucfg_get_float(struct ucfg_manager *manager, const char *key,
                     float default_value);
void ucfg_save_float(struct ucfg_manager *manager, const char *key,
                     float value);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#define UCFG_EXPORT extern "C"
#else
#define UCFG_EXPORT
#endif

#define UCFG_DEFAULT_DATA(manager_name) default_data##manager_name
#define UCFG_ID(manager_name) ucfg_##manager_name()

/**
 * ucfg_default_data uses static variables and ucfg_manager uses static
 * functions to delay initialization of ucfg_manager to ensure that
 * ucfg_default_data has been set.
 */
#define UCFG_DEFINE_PARAM_MANAGER(manager, file_path)               \
  static struct ucfg_default_data *UCFG_DEFAULT_DATA(manager) =     \
      ucfg_create_default_data();                                   \
  UCFG_EXPORT struct ucfg_manager *UCFG_ID(manager) {               \
    static struct ucfg_manager *manager_ =                          \
        ucfg_create_manager(file_path, UCFG_DEFAULT_DATA(manager)); \
    return manager_;                                                \
  }                                                                 \
  struct hack

#define UCFG_DECLARE_PARAM_MANAGER(manager)                                    \
  UCFG_EXPORT struct ucfg_manager *UCFG_ID(manager);                           \
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

#define UCFG_DEFINE_PARAM(manager, type, section, name, default_value) \
  static bool register_default_##section##_##name =                    \
      ucfg_register_default_##type(UCFG_DEFAULT_DATA(manager),         \
                                   #section "-" #name, default_value)
#define UCFG_DECLARE_PARAM(manager, type, param_section, name)             \
  static inline type manager##_get_##param_section##_##name() {            \
    return ucfg_get_##type(UCFG_ID(manager), #param_section "-" #name, 0); \
  }                                                                        \
  static inline void manager##_save_##param_section##_##name(type value) { \
    ucfg_save_##type(UCFG_ID(manager), #param_section "-" #name, value);   \
  }

#define UCFG_DEFINE_PARAM_STRING(manager, section, name, default_value) \
  UCFG_DEFINE_PARAM(manager, string, section, name, default_value)
#define UCFG_DECLARE_PARAM_STRING(manager, section, name)                     \
  static inline void manager##_get_##section##_##name(char *out_str,          \
                                                      size_t size) {          \
    ucfg_get_string(UCFG_ID(manager), #section "-" #name, "", out_str, size); \
  }                                                                           \
  static inline void manager##_save_##section##_##name(const char *value) {   \
    ucfg_save_string(UCFG_ID(manager), #section "-" #name, value);            \
  }                                                                           \
  struct hack

#define UCFG_DEFINE_PARAM_BOOL(manager, section, name, default_value) \
  UCFG_DEFINE_PARAM(manager, bool, section, name, default_value)

#define UCFG_DECLARE_PARAM_BOOL(manager, section, name) \
  UCFG_DECLARE_PARAM(manager, bool, section, name)

#define UCFG_DEFINE_PARAM_INT(manager, section, name, default_value) \
  UCFG_DEFINE_PARAM(manager, int, section, name, default_value)

#define UCFG_DECLARE_PARAM_INT(manager, section, name) \
  UCFG_DECLARE_PARAM(manager, int, section, name)

#define UCFG_DEFINE_PARAM_FLOAT(manager, section, name, default_value) \
  UCFG_DEFINE_PARAM(manager, float, section, name, default_value)

#define UCFG_DECLARE_PARAM_FLOAT(manager, section, name) \
  UCFG_DECLARE_PARAM(manager, float, section, name)
