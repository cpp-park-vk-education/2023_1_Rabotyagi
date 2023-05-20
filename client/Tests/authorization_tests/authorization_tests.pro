include(gtest_dependency.pri)
QT       += core gui widgets

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
QT += testlib
QT += gui

HEADERS += \
#    ../../mainwindow.h \
#    ../../loginwindow.h \
#    ../../registrationwindow.h \
#    ../../usercontrol.h \
    ../../../client2/ITSwarm/windows/login_window/loginwindow.hpp \
    ../../../client2/ITSwarm/windows/reg_window/reg_window.h \
    ../../../client2/ITSwarm/controls/user_control/user_control.h \
    ../../../client/Tests/authorization_tests/tst_my_test.h

SOURCES += \
        ../../../client/Tests/authorization_tests/main.cpp \
        ../../../client/Tests/authorization_tests/tst_my_test.cpp \
        ../../../client2/ITSwarm/windows/login_window/loginwindow.cpp \
        ../../../client2/ITSwarm/windows/reg_window/reg_window.cpp \
        ../../../client2/ITSwarm/controls/user_control/user_control.cpp

FORMS += \
    ../../../client2/ITSwarm/windows/login_window/loginwindow.ui \
    ../../../client2/ITSwarm/windows/reg_window/reg_window.ui

