//
// Created by shawnfeng on 7/2/21.
// Copyright (c) 2021 shawnfeng. All rights reserved.
//
#pragma once

#include <ucfg/param/param.h>

// Declare parameter
UCFG_DECLARE_PARAM_MANAGER(param);

UCFG_DECLARE_PARAM_BOOL(param, control, enable);
UCFG_DECLARE_PARAM_INT(param, control, max_speed);
UCFG_DECLARE_PARAM_FLOAT(param, control, acceleration);
UCFG_DECLARE_PARAM_STRING(param, server, domain);

UCFG_DECLARE_PARAM_STRING(param, , system_name);
