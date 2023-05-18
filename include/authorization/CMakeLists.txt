cmake_minimum_required(VERSION 3.5)

project(authorisation VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        loginwindow.h
        loginwindow.cpp
        loginwindow.ui
        registrationwindow.h
        registrationwindow.cpp
        registrationwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(authorisation
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET authorisation APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(authorisation SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(authorisation
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(authorisation PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(authorisation PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(authorisation)
endif()

#FetchContent_Declare(googletest
#    GIT_REPOSITORY https://github.com/google/googletest.git
#    GIT_TAG release-1.12.1)
#FetchContent_MakeAvailable(googletest)

#target_link_libraries(server PRIVATE Server)
#target_link_libraries(client PRIVATE Server)
#target_link_libraries(server PRIVATE nlohmann_json::nlohmann_json)
#target_link_libraries(client PRIVATE nlohmann_json::nlohmann_json)
#target_link_libraries(test gtest_main gmock_main tests_headers)
