cmake_minimum_required(VERSION 3.17)
project(ucfg)

# gtest
find_package(GTest REQUIRED)
link_libraries(GTest::GTest GTest::Main)
include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)

add_executable(ucfg_string_parser_test manager_test.cc)
add_executable(ucfg_string_helper_test string_helper_test.cc)
