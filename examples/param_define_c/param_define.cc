//
// Created by shawnfeng on 7/2/21.
//
#include "ucfg/param/param.h"

// Define a parameter manager
UCFG_DEFINE_PARAM_MANAGER(param, "./param.cfg");

// Define parameter, the parameter can be bool/int/float/string types
UCFG_DEFINE_PARAM_BOOL(param, control, enable, true);
UCFG_DEFINE_PARAM_INT(param, control, max_speed, 10);
UCFG_DEFINE_PARAM_FLOAT(param, control, acceleration, 1);
UCFG_DEFINE_PARAM_STRING(param, server, domain, "www.server.com");

// Global param, section is none
UCFG_DEFINE_PARAM_STRING(param, , system_name, "robot");
