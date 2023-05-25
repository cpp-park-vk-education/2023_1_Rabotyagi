cmake_minimum_required(VERSION 3.0.0)
project(dispatcher
    VERSION 1.0.0
    DESCRIPTION "Библиотека url роутером для сервера"
    LANGUAGES CXX
)

# include(FetchContent)
include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

# FetchContent_Declare(googletest
# GIT_REPOSITORY https://github.com/google/googletest.git
# GIT_TAG release-1.12.1)
# FetchContent_MakeAvailable(googletest)

add_library(dispatcher STATIC src/dispatcher.cpp)
set_property(TARGET dispatcher PROPERTY CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# find_library(request request REQUIRED)


# add_executable(dispatcher_tests tests/tests.cpp)
# target_link_libraries(dispatcher_tests gtest_main gmock_main)
# add_library(data_types::Data_Types ALIAS data_types)



target_include_directories(
    dispatcher 
        PUBLIC include
        # PRIVATE request
)

target_link_libraries(dispatcher 
    PRIVATE data_types
    PRIVATE request
    PRIVATE nlohmann_json::nlohmann_json
    )