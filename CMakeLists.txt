cmake_minimum_required(VERSION 3.5)
project(ucfg)

option(UCFG_BUILD_TESTS "Build tests" OFF)
option(UCFG_BUILD_EXAMPLES "Build examples" OFF)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

add_compile_options(-Wextra -Wall)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)

add_library(${PROJECT_NAME}_param src/param/param.cc)
target_include_directories(${PROJECT_NAME}_param PUBLIC include)

# install
file(GLOB UCFG_HEADERS include/ucfg/*.h)
install(TARGETS ${PROJECT_NAME}_param
        ARCHIVE DESTINATION lib)
install(FILES ${UCFG_HEADERS} DESTINATION include/ucfg)
file(GLOB UCFG_PARAM_HEADERS include/ucfg/param/*.h)
install(FILES ${UCFG_PARAM_HEADERS} DESTINATION include/ucfg/param)
file(GLOB UCFG_INTERNAL_HEADERS include/ucfg/internal/*.h)
install(FILES ${UCFG_INTERNAL_HEADERS} DESTINATION include/ucfg/internal)

if (UCFG_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()

if (UCFG_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()
