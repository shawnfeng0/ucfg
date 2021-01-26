#include "../string_helper.h"

#include <gtest/gtest.h>

using namespace ucfg::detail;

TEST(ucfg, string) {
  std::string str{" x "};
  EXPECT_EQ(strip(str), "x");
  str = "  x  ";
  EXPECT_EQ(strip(str), "x");

  EXPECT_EQ(strip(" x "), "x");
  EXPECT_EQ(strip("  x "), "x");
  EXPECT_EQ(strip(" x  "), "x");
  EXPECT_EQ(strip(" x"), "x");
  EXPECT_EQ(strip("  x"), "x");
  EXPECT_EQ(strip("x "), "x");
  EXPECT_EQ(strip("x  "), "x");
  EXPECT_EQ(strip(""), "");

  EXPECT_EQ(strip(" "), "");
  EXPECT_EQ(strip(" "), "");
  EXPECT_EQ(strip("\t"), "");
  EXPECT_EQ(strip("\r\n \t"), "");
  EXPECT_EQ(strip("\r\n "), "");
}
