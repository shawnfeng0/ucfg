//
// Created by shawnfeng on 7/2/21.
// Copyright (c) 2021 shawnfeng. All rights reserved.
//
#pragma once

#include "ucfg/param/param.h"

UCFG_DECLARE_PARAM_MANAGER(param);
UCFG_DECLARE_PARAM_BOOL(param, s1, test);
UCFG_DECLARE_PARAM_INT(param, s2, test);
UCFG_DECLARE_PARAM_FLOAT(param, s3, test);
UCFG_DECLARE_PARAM_STRING(param, s4, test);

UCFG_DECLARE_PARAM_FLOAT(param, , test);
