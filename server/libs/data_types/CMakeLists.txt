cmake_minimum_required(VERSION 3.0.0)
project(data_types
    VERSION 1.0.0
    DESCRIPTION "Библиотека с типами данных"
    LANGUAGES CXX)

add_library(data_types STATIC src/data_types.cpp)
# add_library(data_types::Data_Types ALIAS data_types)

target_include_directories(data_types PUBLIC include)