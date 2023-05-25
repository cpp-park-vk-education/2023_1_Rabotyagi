cmake_minimum_required(VERSION 3.0.0)
project(dispatcher
    VERSION 1.0.0
    DESCRIPTION "Библиотека url роутером для сервера"
    LANGUAGES CXX
)

include(FetchContent)

FetchContent_Declare(googletest
GIT_REPOSITORY https://github.com/google/googletest.git
GIT_TAG release-1.12.1)
FetchContent_MakeAvailable(googletest)

add_library(dispatcher STATIC src/dispatcher.cpp)
find_library(request request REQUIRED)


add_executable(dispatcher_tests tests/tests.cpp)
target_link_libraries(dispatcher_tests gtest_main gmock_main)
# add_library(data_types::Data_Types ALIAS data_types)



target_include_directories(
    dispatcher 
        PUBLIC include
        PRIVATE request
)