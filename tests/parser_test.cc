//
// Created by fs on 2021-01-25.
//

#include "../parser.h"

#include <gtest/gtest.h>

#include "../manager.h"
#include "ulog/ulog.h"

TEST(ucfg, parser_new) {
  logger_enable_time_output(false);
  logger_enable_process_id_output(false);
  logger_enable_level_output(false);

  auto manager = ucfg::Manager("../example_new.cfg");
  manager.Visit([](const std::string &section, const std::string &key,
                   const std::string &value) {
    LOGGER_MULTI_TOKEN(section.c_str(), key.c_str(), value.c_str());
  });
}

TEST(ucfg, parser) {
  logger_enable_time_output(false);
  logger_enable_process_id_output(false);
  logger_enable_level_output(false);

  auto manager = ucfg::Manager("../example.cfg");
  manager.DumpToFile("../example1.cfg");
  manager.SetString("numbers", "string_key", "string_string_string")
      .SetBool("numbers", "bool_key", true)
      .SetInteger("numbers", "integer_key", 120234808)
      .SetDouble("numbers", "double_key", 1234.9028304808);
  manager.Visit([](const std::string &section, const std::string &key,
                   const std::string &value) {
    LOGGER_MULTI_TOKEN(section.c_str(), key.c_str(), value.c_str());
  });
  manager.DumpToFile("../example_new.cfg");
}
