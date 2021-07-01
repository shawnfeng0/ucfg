//
// Created by shawnfeng on 7/2/21.
//

#include "ucfg/param/param_default_data.h"

#include "ucfg/ucfg.h"

struct ucfg_default_data *ucfg_create_default_data() {
  return reinterpret_cast<ucfg_default_data *>(new ucfg::ConfigData());
}

bool ucfg_register_default_string(struct ucfg_default_data *default_config,
                                  const char *key, const char *value) {
  if (!default_config || !key) return false;
  auto &default_ucfg_config =
      *reinterpret_cast<ucfg::ConfigData *>(default_config);

  std::string section, name;
  std::tie(section, name) = ucfg::detail::split_two_string(key, "-");
  default_ucfg_config[section][name] = value ? value : "";
  return true;
}

bool ucfg_register_default_bool(struct ucfg_default_data *default_config,
                                const char *key, bool value) {
  if (!default_config || !key) return false;
  auto &default_ucfg_config =
      *reinterpret_cast<ucfg::ConfigData *>(default_config);

  std::string section, name;
  std::tie(section, name) = ucfg::detail::split_two_string(key, "-");
  default_ucfg_config[section][name] = value ? "true" : "false";
  return true;
}

bool ucfg_register_default_int(struct ucfg_default_data *default_config,
                               const char *key, int value) {
  if (!default_config || !key) return false;
  auto &default_ucfg_config =
      *reinterpret_cast<ucfg::ConfigData *>(default_config);

  std::string section, name;
  std::tie(section, name) = ucfg::detail::split_two_string(key, "-");
  default_ucfg_config[section][name] = std::to_string(value);
  return true;
}

bool ucfg_register_default_float(struct ucfg_default_data *default_config,
                                 const char *key, float value) {
  if (!default_config || !key) return false;
  auto &default_ucfg_config =
      *reinterpret_cast<ucfg::ConfigData *>(default_config);

  std::string section, name;
  std::tie(section, name) = ucfg::detail::split_two_string(key, "-");
  default_ucfg_config[section][name] = std::to_string(value);
  return true;
}
