cmake_minimum_required(VERSION 3.0.0)
project(request
    VERSION 1.0.0
    DESCRIPTION "Библиотека request типа"
    LANGUAGES CXX
)

include(FetchContent)

FetchContent_Declare(googletest
GIT_REPOSITORY https://github.com/google/googletest.git
GIT_TAG release-1.12.1)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.2/json.tar.xz)
FetchContent_MakeAvailable(json)

add_library(request STATIC src/request.cpp)
add_subdirectory(include/data_types)

target_link_libraries(request 
    PRIVATE data_types
    PRIVATE nlohmann_json::nlohmann_json
)


target_include_directories(request PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)
set_target_properties(request PROPERTIES PUBLIC_HEADER  include/request.hpp)

add_executable(request_tests tests/tests.cpp)
target_link_libraries(
    request_tests 
        PRIVATE gtest_main 
        PRIVATE gmock_main 
        PRIVATE request
        PRIVATE data_types
        PRIVATE nlohmann_json::nlohmann_json
)

set_property(TARGET request request_tests PROPERTY CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

install(TARGETS request
        EXPORT RequestTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
# install(FILES include/request.hpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT RequestTargets
        FILE RequestTargets.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/request
)