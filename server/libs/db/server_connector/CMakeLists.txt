cmake_minimum_required(VERSION 3.0.0)

project(server_connector
    VERSION 1.0.0
    DESCRIPTION "Библиотека с классами-коннекторами к бд постгреса"
    LANGUAGES CXX
)
find_package(PostgreSQL REQUIRED)

include(FetchContent)
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1)
FetchContent_MakeAvailable(googletest)


add_library(server_connector src/server_connector.cpp)

target_include_directories(server_connector PUBLIC include)

target_link_libraries(server_connector
data_types
PostgreSQL::PostgreSQL
)

# add_executable(test tests/tests.cpp)
# target_link_libraries(test gtest_main gmock_main server_connector)