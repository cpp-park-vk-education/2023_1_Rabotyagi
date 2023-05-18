add_library(libs INTERFACE)
target_include_directories(libs INTERFACE .)
target_link_libraries(libs INTERFACE nlohmann_json::nlohmann_json)