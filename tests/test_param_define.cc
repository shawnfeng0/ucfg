//
// Created by shawnfeng on 7/2/21.
//

#include <gtest/gtest.h>

#include "param_define.h"

TEST(ucfg, param_set) {
  param_save_s1_test(true);
  std::cout << "Param: " << param_get_s1_test() << std::endl;
  std::cout << "Param: " << param_get_s3_test() << std::endl;
}
