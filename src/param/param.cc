#include <ucfg/param/param.h>
#include <ucfg/ucfg.h>

void ucfg_erase_all(ucfg_manager *manager) {
  if (!manager) return;

  auto ucfg_manager = reinterpret_cast<ucfg::ConfigManager *>(manager);
  ucfg_manager->RestoreDefault().Save();
}

void ucfg_get_string(ucfg_manager *manager, const char *key,
                     const char *default_value, char *out_str,
                     size_t out_max_length) {
  if (!manager || !key || !default_value || !out_str) return;

  auto ucfg_manager = reinterpret_cast<ucfg::ConfigManager *>(manager);
  ucfg_manager->ReloadFileIfUpdate();

  std::string section, name;
  std::tie(section, name) = ucfg::internal::split_two_string(key, "-");
  std::string str = ucfg_manager->GetString(section, name, default_value);
  snprintf(out_str, out_max_length, "%s", str.c_str());
}

void ucfg_save_string(ucfg_manager *manager, const char *key,
                      const char *value) {
  if (!manager || !key) return;

  auto ucfg_manager = reinterpret_cast<ucfg::ConfigManager *>(manager);
  ucfg_manager->ReloadFileIfUpdate();

  std::string section, name;
  std::tie(section, name) = ucfg::internal::split_two_string(key, "-");
  ucfg_manager->SetString(section, name, value).Save();
}

bool ucfg_is_number(ucfg_manager *manager, const char *key) {
  if (!manager || !key) return false;

  auto ucfg_manager = reinterpret_cast<ucfg::ConfigManager *>(manager);
  std::string section, name;
  std::tie(section, name) = ucfg::internal::split_two_string(key, "-");
  return ucfg_manager->IsNumber(section, name);
}

int ucfg_get_int(ucfg_manager *manager, const char *key, int default_value) {
  if (!manager || !key) return 0;

  auto ucfg_manager = reinterpret_cast<ucfg::ConfigManager *>(manager);
  ucfg_manager->ReloadFileIfUpdate();

  std::string section, name;
  std::tie(section, name) = ucfg::internal::split_two_string(key, "-");
  return (int)ucfg_manager->GetInteger(section, name, default_value);
}

void ucfg_save_int(ucfg_manager *manager, const char *key, int value) {
  if (!manager || !key) return;

  auto ucfg_manager = reinterpret_cast<ucfg::ConfigManager *>(manager);
  ucfg_manager->ReloadFileIfUpdate();

  std::string section, name;
  std::tie(section, name) = ucfg::internal::split_two_string(key, "-");
  ucfg_manager->SetInteger(section, name, value).Save();
}

bool ucfg_is_boolean(ucfg_manager *manager, const char *key) {
  if (!manager || !key) return false;

  auto ucfg_manager = reinterpret_cast<ucfg::ConfigManager *>(manager);
  std::string section, name;
  std::tie(section, name) = ucfg::internal::split_two_string(key, "-");
  return ucfg_manager->IsBoolean(section, name);
}

bool ucfg_get_bool(ucfg_manager *manager, const char *key, bool default_value) {
  if (!manager || !key) return false;

  auto ucfg_manager = reinterpret_cast<ucfg::ConfigManager *>(manager);
  ucfg_manager->ReloadFileIfUpdate();

  std::string section, name;
  std::tie(section, name) = ucfg::internal::split_two_string(key, "-");
  return ucfg_manager->GetBool(section, name, default_value);
}

void ucfg_save_bool(ucfg_manager *manager, const char *key, bool value) {
  if (!manager || !key) return;

  auto ucfg_manager = reinterpret_cast<ucfg::ConfigManager *>(manager);
  ucfg_manager->ReloadFileIfUpdate();

  std::string section, name;
  std::tie(section, name) = ucfg::internal::split_two_string(key, "-");
  ucfg_manager->SetBool(section, name, value).Save();
}

float ucfg_get_float(ucfg_manager *manager, const char *key,
                     float default_value) {
  if (!manager || !key) return 0;

  auto ucfg_manager = reinterpret_cast<ucfg::ConfigManager *>(manager);
  ucfg_manager->ReloadFileIfUpdate();

  std::string section, name;
  std::tie(section, name) = ucfg::internal::split_two_string(key, "-");
  return (float)ucfg_manager->GetDouble(section, name, default_value);
}

void ucfg_save_float(ucfg_manager *manager, const char *key, float value) {
  if (!manager || !key) return;

  auto ucfg_manager = reinterpret_cast<ucfg::ConfigManager *>(manager);
  ucfg_manager->ReloadFileIfUpdate();

  std::string section, name;
  std::tie(section, name) = ucfg::internal::split_two_string(key, "-");
  ucfg_manager->SetDouble(section, name, value).Save();
}
