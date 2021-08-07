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


}
