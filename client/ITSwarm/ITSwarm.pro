QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20
QMAKE_CXXFLAGS += -std=c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

#SUBDIRS += \
#    windows \
#    controls

SOURCES += \
    controls/channel_control/channelcontrol.cpp \
#    controls/client/client.cpp \
#    controls/client/tcpclient.cpp \
    controls/message_control/messagecontrol.cpp \
    controls/user_control/user_control.cpp \
    main.cpp \
    test.cpp \
    windows/channel_widget/channelsidebar.cpp \
    windows/content_widget/contentwindow.cpp \
    windows/gitconnection/gitconnection.cpp \
    windows/login_window/loginwindow.cpp \
    windows/main_window/main_window.cpp \
    windows/reg_window/reg_window.cpp \
    windows/settings_window/settingswindow.cpp \
#    windows/sidebar/sidebar.cpp \
    windows/userbar/userbar.cpp

HEADERS += \
    controls/data_types/request.h \
    controls/data_types/data_types.hpp \
    external/HTTPRequest.hpp \
    external/data_types.hpp \
    external/json.hpp \
    controls/channel_control/channelcontrol.h \
#    controls/client/client.h \
#    controls/client/iclient.h \
#    controls/client/tcpclient.h \
    controls/data_types/data_types.hpp \
    controls/message_control/messagecontrol.h \
    controls/user_control/user_control.h \
    windows/channel_widget/channelsidebar.h \
    windows/content_widget/contentwindow.h \
    windows/gitconnection/gitconnection.h \
    windows/login_window/loginwindow.hpp \
    windows/main_window/main_window.h \
    windows/reg_window/reg_window.h \
    windows/settings_window/settingswindow.h \
#    windows/sidebar/sidebar.h \
    windows/userbar/userbar.h

FORMS += \
    windows/channel_widget/channelsidebar.ui \
    windows/content_widget/contentwindow.ui \
    windows/gitconnection/gitconnection.ui \
    windows/login_window/loginwindow.ui \
    windows/main_window/main_window.ui \
    windows/reg_window/reg_window.ui \
    windows/settings_window/settingswindow.ui \
    windows/sidebar/sidebar.ui \
    windows/userbar/userbar.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    windows/static/images.qrc

DISTFILES += \
    windows/static/images/Channels-Iconhovered.png \
    windows/static/images/Channels-Iconselected.png \
    windows/static/images/Channels-Iconvoice hovered.png \
    windows/static/images/Channels-Iconvoice_selected.png \
    windows/static/images/WF Icon Button.png \
    windows/static/images/icons8-automatic-50.png \
    windows/static/images/icons8-git-50.png \
    windows/static/images/icons8-git-75.png \
    windows/static/images/icons8-more-24.png \
    windows/static/images/icons8-search-30.png \
    windows/static/images/icons8-settings-50.png \
    windows/static/images/settings.png

INCLUDEPATH += \
    "windows/channel_widget" \
    "windows/content_widget" \
    "windows/gitconnection" \
    "windows/login_window" \
    "windows/main_window" \
    "windows/reg_window" \
    "windows/settings_window" \
    "windows/sidebar" \
    "windows/static" \
    "windows/userbar" \
    "controls/channel_control" \
    "controls/client" \
    "controls/data_types" \
    "controls/message_control" \
    "controls/user_control" \
    "external"


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../../../../usr/local/lib/release/ -lcpr
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../../../../usr/local/lib/debug/ -lcpr
else:unix: LIBS += -L$$PWD/../../../../../../usr/local/lib/ -lcpr

INCLUDEPATH += $$PWD/../../../../../../usr/local/lib
DEPENDPATH += $$PWD/../../../../../../usr/local/lib
