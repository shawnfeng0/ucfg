cmake_minimum_required(VERSION 3.5)
project(ucfg)

option(UCFG_BUILD_TESTS "Build tests" OFF)

set(CMAKE_CXX_STANDARD 14)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)

add_library(${PROJECT_NAME}_param src/param/param.cc src/param/param_default_data.cc)
target_include_directories(${PROJECT_NAME}_param PUBLIC include)

# install
file(GLOB UCFG_HEADERS include/ucfg/*.h)
file(GLOB UCFG_PARAM_HEADERS include/ucfg/param/*.h)
install(TARGETS ${PROJECT_NAME}_param
        ARCHIVE DESTINATION lib)
install(FILES ${UCFG_HEADERS} DESTINATION include/ucfg)
install(FILES ${UCFG_PARAM_HEADERS} DESTINATION include/ucfg/param)

if (UCFG_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()
