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

  std::tuple<std::string, std::string> split_expect{"audio", "volume"};
  EXPECT_EQ(split_two_string("audio-volume", "-"), split_expect);

  split_expect = {"", "volume"};
  EXPECT_EQ(split_two_string("volume", "-"), split_expect);

  split_expect = {"audio", ""};
  EXPECT_EQ(split_two_string("audio-", "-"), split_expect);

  split_expect = {"", ""};
  EXPECT_EQ(split_two_string("", "-"), split_expect);

  std::string section;
  std::string key;

  std::tie(section, key) = split_two_string("audio-volume", "-");
  EXPECT_EQ(section, "audio");
  EXPECT_EQ(key, "volume");
}
