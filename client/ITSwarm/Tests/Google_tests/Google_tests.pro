include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
QT += core gui widgets

INCLUDEPATH += \
        "../../" \
        "../../controls/json_parser" \
        "../../controls/data_types/message"

HEADERS += \
        ../../controls/json_parser/json_parser.h \
        ../../controls/data_types/message/message.h \
        json_test.h


SOURCES += \
        json_test.cpp \
        main.cpp \
        ../../controls/json_parser/json_parser.cpp \
        ../../controls/data_types/message/message.cpp


