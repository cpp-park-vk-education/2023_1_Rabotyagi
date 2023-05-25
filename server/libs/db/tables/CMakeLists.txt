cmake_minimum_required(VERSION 3.0.0)
project(tables
    VERSION 1.0.0
    DESCRIPTION "Библиотека с таблицами"
    LANGUAGES CXX
)
find_package(PostgreSQL REQUIRED)

include(FetchContent)
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1)
FetchContent_MakeAvailable(googletest)

add_library(tables src/tables.cpp)
target_include_directories(tables PUBLIC include)

target_link_libraries(tables
    data_types
    PostgreSQL::PostgreSQL
)