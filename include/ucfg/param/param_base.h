//
// Created by shawnfeng on 7/13/21.
// Copyright (c) 2021 shawnfeng. All rights reserved.
//
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
