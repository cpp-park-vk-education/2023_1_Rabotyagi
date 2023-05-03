cmake_minimum_required(VERSION 3.0.0)
project(project VERSION 0.1.0)


add_executable(server udp_server.cpp)
add_executable(client udp_client.cpp)
set_property(TARGET server PROPERTY CXX_STANDARD 20)
set_property(TARGET client PROPERTY CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(libs/Server)
target_link_libraries(server PRIVATE Server)
target_link_libraries(client PRIVATE Server)

find_package(Boost REQUIRED)
IF (Boost_FOUND)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()


include(FetchContent)
FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

target_link_libraries(server PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(client PRIVATE nlohmann_json::nlohmann_json)