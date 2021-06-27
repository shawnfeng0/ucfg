cmake_minimum_required(VERSION 3.5)
project(ucfg)

option(UCFG_BUILD_TESTS "Build tests" OFF)

set(CMAKE_CXX_STANDARD 14)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)

if (UCFG_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()
