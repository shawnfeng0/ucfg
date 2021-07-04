project(param_examples_cpp)

aux_source_directory(. EXAMPLE_SOURCE)
add_executable(${PROJECT_NAME} ${EXAMPLE_SOURCE})
target_link_libraries(${PROJECT_NAME} ucfg_param)
