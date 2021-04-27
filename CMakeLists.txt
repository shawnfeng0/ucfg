cmake_minimum_required(VERSION 3.5)
project(ucfg)

option(BUILD_TESTS "Build tests" OFF)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()
