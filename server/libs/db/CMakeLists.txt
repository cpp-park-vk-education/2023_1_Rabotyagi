cmake_minimum_required(VERSION 3.0.0)
project(database VERSION 0.1.0)


add_library(database main.cpp)
set_property(TARGET database PROPERTY CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PostgreSQL REQUIRED)
target_link_libraries(database PRIVATE PostgreSQL::PostgreSQL)

add_subdirectory(data_types)
add_subdirectory(tables)
add_subdirectory(server_connector)
target_link_libraries(database 
    PUBLIC data_types
    PUBLIC tables
    PUBLIC server_connector
)