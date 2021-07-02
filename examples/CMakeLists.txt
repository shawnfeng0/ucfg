project(param_examples)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} EXAMPLE_SOURCE)
add_executable(${PROJECT_NAME} ${EXAMPLE_SOURCE})
target_link_libraries(${PROJECT_NAME} ucfg_param)
