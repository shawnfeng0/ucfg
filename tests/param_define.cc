//
// Created by shawnfeng on 7/2/21.
//

#include "param_define.h"

#include <ucfg/param/param.h>

UCFG_DEFINE_PARAM_MANAGER(param, "./param.cfg");
UCFG_DEFINE_PARAM_BOOL(param, s1, test, true);
UCFG_DEFINE_PARAM_INT(param, s2, test, 10);
UCFG_DEFINE_PARAM_FLOAT(param, s3, test, 10.143);
UCFG_DEFINE_PARAM_STRING(param, s4, test, "test");

UCFG_DEFINE_PARAM_FLOAT(param, , test, 10.143);
