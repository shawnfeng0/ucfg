#include <ucfg/param/param.h>
#include <ucfg/ucfg.h>

template <typename DefaultValueType, typename GetFunc>
static auto ucfg_get_value(ucfg::ConfigManager *manager,
                           DefaultValueType default_value, const char *key,
                           GetFunc get_func) {
  using ReturnType = decltype((manager->*get_func)("", "", default_value));

  if (!manager || !key) return ReturnType(default_value);

  manager->ReloadFileIfUpdate();

  std::string section, name;
  std::tie(section, name) = ucfg::internal::split_two_string(key, "-");
  return (manager->*get_func)(section, name, default_value);
}

template <typename ValueType, typename SaveFunc>
static void ucfg_save_value(ucfg::ConfigManager *manager, SaveFunc save_func,
                            const char *key, ValueType value) {
  if (!manager || !key) return;

  manager->ReloadFileIfUpdate();

  std::string section, name;
  std::tie(section, name) = ucfg::internal::split_two_string(key, "-");
  (manager->*save_func)(section, name, value).Save();
}

void ucfg_erase_all(ucfg_manager *manager) {
  if (!manager) return;

  auto ucfg_manager = reinterpret_cast<ucfg::ConfigManager *>(manager);
  ucfg_manager->RestoreDefault().Save();
}

void ucfg_get_string(ucfg_manager *manager, const char *key,
                     const char *default_value, char *out_str,
                     size_t out_max_length) {
  if (!default_value || !out_str) return;

  auto ucfg_manager = reinterpret_cast<ucfg::ConfigManager *>(manager);
  auto str = ucfg_get_value(ucfg_manager, default_value, key,
                            &ucfg::ConfigManager::GetString);
  snprintf(out_str, out_max_length, "%s", str.c_str());
}

void ucfg_save_string(ucfg_manager *manager, const char *key,
                      const char *value) {
  auto ucfg_manager = reinterpret_cast<ucfg::ConfigManager *>(manager);
  ucfg_save_value(ucfg_manager, &ucfg::ConfigManager::SetString, key, value);
}

bool ucfg_is_number(ucfg_manager *manager, const char *key) {
  if (!manager || !key) return false;

  auto ucfg_manager = reinterpret_cast<ucfg::ConfigManager *>(manager);
  std::string section, name;
  std::tie(section, name) = ucfg::internal::split_two_string(key, "-");
  return ucfg_manager->IsNumber(section, name);
}

int ucfg_get_int(ucfg_manager *manager, const char *key, int default_value) {
  auto ucfg_manager = reinterpret_cast<ucfg::ConfigManager *>(manager);
  return (int)ucfg_get_value(ucfg_manager, default_value, key,
                             &ucfg::ConfigManager::GetInteger);
}

void ucfg_save_int(ucfg_manager *manager, const char *key, int value) {
  auto ucfg_manager = reinterpret_cast<ucfg::ConfigManager *>(manager);
  ucfg_save_value(ucfg_manager, &ucfg::ConfigManager::SetInteger, key, value);
}

bool ucfg_is_boolean(ucfg_manager *manager, const char *key) {
  if (!manager || !key) return false;

  auto ucfg_manager = reinterpret_cast<ucfg::ConfigManager *>(manager);
  std::string section, name;
  std::tie(section, name) = ucfg::internal::split_two_string(key, "-");
  return ucfg_manager->IsBoolean(section, name);
}

bool ucfg_get_bool(ucfg_manager *manager, const char *key, bool default_value) {
  auto ucfg_manager = reinterpret_cast<ucfg::ConfigManager *>(manager);
  return ucfg_get_value(ucfg_manager, default_value, key,
                        &ucfg::ConfigManager::GetBool);
}

void ucfg_save_bool(ucfg_manager *manager, const char *key, bool value) {
  auto ucfg_manager = reinterpret_cast<ucfg::ConfigManager *>(manager);
  ucfg_save_value(ucfg_manager, &ucfg::ConfigManager::SetBool, key, value);
}

float ucfg_get_float(ucfg_manager *manager, const char *key,
                     float default_value) {
  auto ucfg_manager = reinterpret_cast<ucfg::ConfigManager *>(manager);
  return (float)ucfg_get_value(ucfg_manager, default_value, key,
                               &ucfg::ConfigManager::GetDouble);
}

void ucfg_save_float(ucfg_manager *manager, const char *key, float value) {
  auto ucfg_manager = reinterpret_cast<ucfg::ConfigManager *>(manager);
  ucfg_save_value(ucfg_manager, &ucfg::ConfigManager::SetDouble, key, value);
}
