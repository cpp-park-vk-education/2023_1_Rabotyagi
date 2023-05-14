include(gtest_dependency.pri)
QT       += core gui widgets

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread




INCLUDEPATH += "../../"

HEADERS += \
    ../../loginwindow.h \
    ../../registrationwindow.h \
    tst_my_test.h

SOURCES += \
        main.cpp \
        tst_my_test.cpp \
        ../../loginwindow.cpp \
        ../../registrationwindow.cpp

FORMS += \
    ../../loginwindow.ui \
    ../../registrationwindow.ui

