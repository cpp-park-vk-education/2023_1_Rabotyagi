include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
QT  += core gui widgets

INCLUDEPATH += "../../"

SOURCES += \
        main.cpp \
        tst_case1.cpp
