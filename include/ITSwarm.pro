QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    channel.cpp \
    channelcontrol.cpp \
    channelsidebar.cpp \
    client.cpp \
    contentwindow.cpp \
    gitconnection.cpp \
    guild.cpp \
    main.cpp \
    mainwindow.cpp \
    message.cpp \
    messagecontrol.cpp \
    settingswindow.cpp \
    sidebar.cpp \
    userbar.cpp

HEADERS += \
    channel.h \
    channelcontrol.h \
    channelsidebar.h \
    client.h \
    contentwindow.h \
    gitconnection.h \
    guild.h \
    mainwindow.h \
    message.h \
    messagecontrol.h \
    settingswindow.h \
    sidebar.h \
    userbar.h

FORMS += \
    channelsidebar.ui \
    contentwindow.ui \
    gitconnection.ui \
    mainwindow.ui \
    settingswindow.ui \
    sidebar.ui \
    userbar.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc

DISTFILES +=

# TEMPLATE = lib

# DEFINES += SHARED_LIBRARY

