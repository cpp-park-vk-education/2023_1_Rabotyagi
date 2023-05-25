cmake_minimum_required(VERSION 3.14)
project(data_types
    VERSION 1.0.0
    DESCRIPTION "Библиотека с типами данных"
    LANGUAGES CXX)

add_library(data_types src/data_types.cpp)
# add_library(data_types::Data_Types ALIAS data_types)

target_include_directories(data_types PUBLIC include)

install(TARGETS data_types
        EXPORT data_types_target
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
# install(FILES include/request.hpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT data_types_target
        FILE data_types_target.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/data_types
)