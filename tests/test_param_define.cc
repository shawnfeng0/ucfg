//
// Created by shawnfeng on 7/2/21.
//

#include <gtest/gtest.h>

#include "param_define.h"

TEST(ucfg, param) {
  param_save_s1_test(true);
  EXPECT_EQ(param_get_s1_test(), true);

  param_save_s1_test(false);
  EXPECT_EQ(param_get_s1_test(), false);

  // set and restore default
  auto default_s3 = param_get_s3_test();
  param_save_s3_test(100);
  EXPECT_EQ(param_get_s3_test(), 100);
  param_erase_all();
  EXPECT_EQ(param_get_s3_test(), default_s3);
}
