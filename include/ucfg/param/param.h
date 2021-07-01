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
 * Create or destroy a ucfg manager
 * @return
 */
struct ucfg_manager *ucfg_create_manager(
    const char *config_path, struct ucfg_default_data *default_data);
void ucfg_destroy_manager(struct ucfg_manager *);

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

#define UCFG_DEFAULT_DATA(manager_name) default_data##manager_name

/**
 * ucfg_default_data uses static variables and ucfg_manager uses static
 * functions to delay initialization of ucfg_manager to ensure that
 * ucfg_default_data has been set.
 */
#define UCFG_DEFINE_PARAM_MANAGER(manager_name, file_path)               \
  static struct ucfg_default_data *UCFG_DEFAULT_DATA(manager_name) =     \
      ucfg_create_default_data();                                        \
  static struct ucfg_manager *manager_name() {                           \
    static struct ucfg_manager *manager =                                \
        ucfg_create_manager(file_path, UCFG_DEFAULT_DATA(manager_name)); \
    return manager;                                                      \
  }                                                                      \
  void manager_name##_erase() { ucfg_erase_all(manager_name()); }        \
  struct hack

#define UCFG_DECLARE_PARAM_MANAGER(name, ...) void name##_erase()

#define UCFG_DEFINE_PARAM(manager, type, param_section, param_name,     \
                          default_value)                                \
  static bool _default_data_register_##param_section##_##param_name =   \
      ucfg_register_default_##type(UCFG_DEFAULT_DATA(manager),          \
                                   #param_section "-" #param_name,      \
                                   default_value);                      \
  type manager##_get_##param_section##_##param_name() {                 \
    return ucfg_get_##type(manager(), #param_section "-" #param_name,   \
                           default_value);                              \
  }                                                                     \
  void manager##_save_##param_section##_##param_name(type value) {      \
    ucfg_save_##type(manager(), #param_section "-" #param_name, value); \
  }                                                                     \
  struct hack
#define UCFG_DECLARE_PARAM(manager, type, param_section, param_name) \
  type manager##_get_##param_section##_##param_name();               \
  void manager##_save_##param_section##_##param_name(type value)

#define UCFG_DEFINE_PARAM_STRING(manager, param_section, param_name,          \
                                 default_value)                               \
  static bool ucfg_register_##param_section##_##param_name##__LINE__ =        \
      ucfg_register_default_string(UCFG_DEFAULT_DATA(manager),                \
                                   #param_section "-" #param_name,            \
                                   default_value);                            \
  void manager##_get_##param_section##_##param_name(char *out_str,            \
                                                    size_t size) {            \
    ucfg_get_string(manager(), #param_section "-" #param_name, default_value, \
                    out_str, size);                                           \
  }                                                                           \
  void manager##_save_##param_section##_##param_name(const char *value) {     \
    ucfg_save_string(manager(), #param_section "-" #param_name, value);       \
  }                                                                           \
  struct hack

#define UCFG_DECLARE_PARAM_STRING(manager, param_section, param_name) \
  void manager##_get_##param_section##_##param_name(char *out_str,    \
                                                    size_t size);     \
  void manager##_save_##param_section##_##param_name(const char *value)

#define UCFG_DEFINE_PARAM_BOOL(manager, param_section, param_name, \
                               param_default_value)                \
  UCFG_DEFINE_PARAM(manager, bool, param_section, param_name,      \
                    param_default_value)

#define UCFG_DECLARE_PARAM_BOOL(manager, param_section, param_name) \
  UCFG_DECLARE_PARAM(manager, bool, param_section, param_name)

#define UCFG_DEFINE_PARAM_INT(manager, param_section, param_name, \
                              param_default_value)                \
  UCFG_DEFINE_PARAM(manager, int, param_section, param_name,      \
                    param_default_value)

#define UCFG_DECLARE_PARAM_INT(manager, param_section, param_name) \
  UCFG_DECLARE_PARAM(manager, int, param_section, param_name)

#define UCFG_DEFINE_PARAM_FLOAT(manager, param_section, param_name, \
                                param_default_value)                \
  UCFG_DEFINE_PARAM(manager, float, param_section, param_name,      \
                    param_default_value)

#define UCFG_DECLARE_PARAM_FLOAT(manager, param_section, param_name) \
  UCFG_DECLARE_PARAM(manager, float, param_section, param_name)
