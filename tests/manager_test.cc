//
// Created by fs on 2021-01-25.
//

#include "../parser.h"

#include <gtest/gtest.h>

#include "../manager.h"

TEST(ucfg, manager) {
  std::string test_filename{"test.cfg"};

  // Clear file
  {
    auto manager = ucfg::Manager(test_filename, false);
    manager.Clear().DumpToFile();
  }

  // Set key-value
  {
    auto manager = ucfg::Manager(test_filename, false);
    manager.SetInteger("values", "int_key", 1234);
    manager.SetDouble("values", "double_key", 1234.234);
    manager.SetBool("values", "bool_true_key", true);
    manager.SetBool("values", "bool_false_key", false);
    manager.SetString("values", "string_key", "This is a string.");
    manager.DumpToFile();
  }

  // Test key-value
  {
    auto manager = ucfg::Manager(test_filename);
    EXPECT_EQ(manager.GetInteger("values", "int_key"), 1234);
    EXPECT_EQ(manager.GetDouble("values", "double_key"), 1234.234);
    EXPECT_EQ(manager.GetBool("values", "bool_true_key"), true);
    EXPECT_EQ(manager.GetBool("values", "bool_false_key"), false);
    EXPECT_EQ(manager.GetString("values", "string_key"), "This is a string.");
  }

  // Dump test
  {
    auto manager = ucfg::Manager(test_filename);
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
