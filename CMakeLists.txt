cmake_minimum_required(VERSION 3.5)
project(ucfg)

option(BUILD_TESTS "Build tests" ON)

set(CMAKE_CXX_STANDARD 14)

if (BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()
