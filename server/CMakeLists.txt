cmake_minimum_required(VERSION 3.0.0)
project(project VERSION 0.1.0)


add_executable(server udp_server.cpp)
add_executable(client udp_client.cpp)
add_executable(test test.cpp)

set_property(TARGET server client test PROPERTY CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_subdirectory(libs)
# add_subdirectory(tests)


find_package(Boost REQUIRED)
IF (Boost_FOUND)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()


include(FetchContent)

# Json fetch from repo release
FetchContent_Declare(json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.2)
FetchContent_MakeAvailable(json)

# Google Test fetch from git repo
FetchContent_Declare(googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG release-1.12.1)
FetchContent_MakeAvailable(googletest)

target_link_libraries(server PRIVATE libs)
target_link_libraries(client PRIVATE libs)
target_link_libraries(server PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(client PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(test gtest_main gmock_main)