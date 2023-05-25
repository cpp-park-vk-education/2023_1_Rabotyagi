cmake_minimum_required(VERSION 3.0.0)
project(data_types
    VERSION 0.1.0 
    DESCRIPTION "Библиотека с типами данных"
    LANGUAGES CXX
)

find_package(Boost REQUIRED)
IF (Boost_FOUND)
INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
ADD_DEFINITIONS( "-DHAS_BOOST" )
ENDIF()

add_executable(main src/main.cpp)
target_include_directories(main PUBLIC include)

set_property(TARGET main PROPERTY CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(libs/request)
add_subdirectory(libs/data_types)
add_subdirectory(libs/dispatcher)

target_link_libraries(main 
    PRIVATE request
    PRIVATE data_types
    PRIVATE dispatcher
)