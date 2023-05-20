cmake_minimum_required(VERSION 3.0.0)
project(database VERSION 0.1.0)


add_library(database server_connector/main.cpp)
set_property(TARGET database PROPERTY CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PostgreSQL REQUIRED)
target_link_libraries(database PRIVATE PostgreSQL::PostgreSQL)

add_subdirectory(lib)
target_link_libraries(database PRIVATE lib)
target_link_libraries(database PRIVATE server_connector)
# add_subdirectory(server_connector)