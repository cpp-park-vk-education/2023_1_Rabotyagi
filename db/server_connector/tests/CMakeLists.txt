add_library(tests_headers INTERFACE)
target_include_directories(tests_headers INTERFACE .)
target_link_libraries(tests_headers INTERFACE libs)
