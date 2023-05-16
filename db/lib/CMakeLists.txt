project(lib VERSION 0.1.0)

add_library(lib INTERFACE)
target_include_directories(lib INTERFACE .)
target_link_libraries(lib INTERFACE tables data_types)