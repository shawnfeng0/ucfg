//
// Created by shawnfeng on 7/2/21.
// Copyright (c) 2021 shawnfeng. All rights reserved.
//
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

struct ucfg_default_data *ucfg_create_default_data();
bool ucfg_register_default_string(struct ucfg_default_data *default_config,
                                  const char *key, const char *value);
bool ucfg_register_default_bool(struct ucfg_default_data *default_config,
                                const char *key, bool value);
bool ucfg_register_default_int(struct ucfg_default_data *default_config,
                               const char *key, int value);
bool ucfg_register_default_float(struct ucfg_default_data *default_config,
                                 const char *key, float value);
#ifdef __cplusplus
}
#endif
