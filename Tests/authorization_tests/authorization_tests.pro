include(gtest_dependency.pri)
QT       += core gui widgets

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread




INCLUDEPATH += "../../"

HEADERS += \
    ../../mainwindow.h \
    ../../loginwindow.h \
    ../../registrationwindow.h \
    ../../usercontrol.h \
    tst_my_test.h

SOURCES += \
        main.cpp \
        tst_my_test.cpp \
        ../../mainwindow.cpp \
        ../../loginwindow.cpp \
        ../../registrationwindow.cpp \
        ../../usercontrol.cpp

FORMS += \
    ../../mainwindow.ui \
    ../../loginwindow.ui \
    ../../registrationwindow.ui

