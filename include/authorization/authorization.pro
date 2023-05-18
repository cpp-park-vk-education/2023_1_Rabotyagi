QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


CONFIG += c++11
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    srs/authorization/main.cpp \
    srs/authorization/mainwindow.cpp \
    srs/authorization/loginwindow.cpp \
    srs/authorization/registrationwindow.cpp \
    srs/authorization/usercontrol.cpp

HEADERS += \
    mainwindow.h \
    loginwindow.h \
    registrationwindow.h \
    usercontrol.h


FORMS += \
    ui/authorization/mainwindow.ui \
    ui/authorization/loginwindow.ui \
    ui/authorization/registrationwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
