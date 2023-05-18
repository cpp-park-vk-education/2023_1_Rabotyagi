QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11



# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main/channel.cpp \
    src/main/channelcontrol.cpp \
    src/main/channelsidebar.cpp \
    src/main/client.cpp \
    src/main/contentwindow.cpp \
    src/main/gitconnection.cpp \
    src/main/guild.cpp \
    src/main/main.cpp \
    src/main/mainwindow.cpp \
    src/main/message.cpp \
    src/main/messagecontrol.cpp \
    src/main/settingswindow.cpp \
    src/main/sidebar.cpp \
    src/main/userbar.cpp

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
    ui/main/channelsidebar.ui \
    ui/main/contentwindow.ui \
    ui/main/gitconnection.ui \
    ui/main/mainwindow.ui \
    ui/main/settingswindow.ui \
    ui/main/sidebar.ui \
    ui/main/userbar.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc

DISTFILES +=

# TEMPLATE = lib

# DEFINES += SHARED_LIBRARY

