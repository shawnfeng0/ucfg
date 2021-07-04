//
// Created by shawnfeng on 7/2/21.
//

#include <stdio.h>
#include <string.h>

#include "param_define.h"

// Precompiler define to get only filename;
#if !defined(__FILENAME__)
#define __FILENAME__                                        \
  ({                                                        \
    strrchr(__FILE__, '/')    ? strrchr(__FILE__, '/') + 1  \
    : strrchr(__FILE__, '\\') ? strrchr(__FILE__, '\\') + 1 \
                              : __FILE__;                   \
  })
#endif

#define LOGGER_TOKEN(format, token) \
  printf("(%s:%d) %s -> " format "\r\n", __FILENAME__, __LINE__, #token, token)

#define LOGGER_TOKEN_INT(token) LOGGER_TOKEN("%d", token)
#define LOGGER_TOKEN_FLOAT(token) LOGGER_TOKEN("%f", token)
#define LOGGER_TOKEN_STR(token) LOGGER_TOKEN("%s", token)

void test() {
  // Read
  {
    LOGGER_TOKEN_INT(param_get_control_enable());
    LOGGER_TOKEN_INT(param_get_control_max_speed());
    LOGGER_TOKEN_FLOAT(param_get_control_acceleration());

    char server[100];
    param_get_server_domain(server, sizeof(server));
    LOGGER_TOKEN_STR(server);
  }

  // Write
  {
    LOGGER_TOKEN_INT(param_get_control_max_speed());
    param_save_control_max_speed(30);
    LOGGER_TOKEN_INT(param_get_control_max_speed());

    char server[100];
    param_get_server_domain(server, sizeof(server));
    LOGGER_TOKEN_STR(server);
    param_save_server_domain("www.unknown.com");
    param_get_server_domain(server, sizeof(server));
    LOGGER_TOKEN_STR(server);
  }
}
