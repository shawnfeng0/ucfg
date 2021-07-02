//
// Created by shawnfeng on 7/2/21.
//

#include <string.h>

#include <iostream>

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
#define LOGGER_TOKEN(token)                                             \
  std::cout << "(" << __FILENAME__ << ":" << __LINE__ << ") " << #token \
            << " -> " << token << std::endl

int main() {
  // Read
  {
    LOGGER_TOKEN(param_get_control_enable());
    LOGGER_TOKEN(param_get_control_max_speed());
    LOGGER_TOKEN(param_get_control_acceleration());

    char server[100];
    param_get_server_domain(server, sizeof(server));
    LOGGER_TOKEN(server);
  }

  // Write
  {
    LOGGER_TOKEN(param_get_control_max_speed());
    param_save_control_max_speed(30);
    LOGGER_TOKEN(param_get_control_max_speed());

    char server[100];
    param_get_server_domain(server, sizeof(server));
    LOGGER_TOKEN(server);
    param_save_server_domain("www.unknown.com");
    param_get_server_domain(server, sizeof(server));
    LOGGER_TOKEN(server);
  }
}
