//
// Created by fs on 2021-01-25.
//

#include <gtest/gtest.h>

#include "ucfg/parser.h"
#include "ucfg/ucfg.h"

using namespace ucfg;
using namespace ucfg::detail;

TEST(ucfg, default_config) {
  std::string cfg_filename{"test.cfg"};
  std::string default_filename{"default.cfg"};

  ConfigData res1 = ParserFile(default_filename);
  std::cout << Dump(res1) << std::endl;

  std::cout << std::string(20, '-') << std::endl;

  ConfigData res2 = ParserFile(cfg_filename);
  std::cout << Dump(res2) << std::endl;

  std::cout << std::string(20, '-') << std::endl;

  res1.merge_new(res2);

  std::cout << Dump(res1) << std::endl;
}

TEST(ucfg, manager) {
  std::string cfg_filename{"test.cfg"};
  std::string default_filename{"default.cfg"};

  // Clear file
  {
    ucfg::ConfigManager manager(cfg_filename);
    manager.Clear().Save();
  }

  // Set key_-value_
  {
    ucfg::ConfigManager manager(cfg_filename);
    manager.SetInteger("values", "int_key", 1234);
    manager.SetDouble("values", "double_key", 1234.234);
    manager.SetBool("values", "bool_true_key", true);
    manager.SetBool("values", "bool_false_key", false);
    manager.SetString("values", "string_key", "This is a string.");
    manager.Save();
  }

  // Test key_-value_
  {
    ucfg::ConfigManager manager(cfg_filename);
    EXPECT_EQ(manager.GetInteger("values", "int_key"), 1234);
    EXPECT_EQ(manager.GetDouble("values", "double_key"), 1234.234);
    EXPECT_EQ(manager.GetBool("values", "bool_true_key"), true);
    EXPECT_EQ(manager.GetBool("values", "bool_false_key"), false);
    EXPECT_EQ(manager.GetString("values", "string_key"), "This is a string.");
  }

  // Dump test
  {
    ucfg::ConfigManager manager(cfg_filename);
    auto dump_data{manager.Dump()};
    EXPECT_EQ(dump_data, R"([values]
bool_false_key = false
bool_true_key = true
double_key = 1234.234000
int_key = 1234
string_key = This is a string.
)");
  }
}
