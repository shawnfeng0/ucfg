cmake_minimum_required(VERSION 3.5)
project(ucfg)

option(UCFG_BUILD_TESTS "Build tests" OFF)
option(UCFG_BUILD_EXAMPLES "Build examples" OFF)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_C_STANDARD 99)

add_compile_options(-Wextra -Wall)

add_library(${PROJECT_NAME} INTERFACE)
target_include_directories(${PROJECT_NAME} INTERFACE include)

add_library(${PROJECT_NAME}_param src/param/param.cc)
target_link_libraries(${PROJECT_NAME}_param PUBLIC ${PROJECT_NAME})

# install
install(TARGETS ${PROJECT_NAME}_param
        ARCHIVE DESTINATION lib)
install(DIRECTORY include/ucfg DESTINATION include)

if (UCFG_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif ()

if (UCFG_BUILD_EXAMPLES)
    add_subdirectory(examples)
endif ()
