#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "settingswindow.h"
#include "gitconnection.h"
#include <memory>
#include "userbar.h"
#include "contentwindow.h"
#include "sidebar.h"
#include "channelsidebar.h"
#include "guildbar.h"
#include "usersettings.h"
#include <QMainWindow>
#include <QVector>
#include <QTimer>
#include <QTime>
//#include "client.h"
//#include "tcpclient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:   
    MainWindow(int* flag, QWidget *parent = nullptr);
    int* _flag;
    virtual ~MainWindow();

    enum class States {
        to_login_window = 3
    };
    void UpdateUser();

public slots:
    void on_settingsButton_clicked();
    void on_gitButton_clicked();


private slots:
    void on_connect_clicked();

    void on_add_new_clicked();

private:
    Ui::MainWindow *ui;

//    std::shared_ptr<Client> client;
    //std::shared_ptr<TCPClient> client;

    std::shared_ptr<SettingsWindow> settings;
    std::shared_ptr<GitConnection> git;

    QString nickname;

    std::shared_ptr<Userbar> userbar;
    std::shared_ptr<ContentWindow> content_window;
    std::shared_ptr<Sidebar> sidebar;
    std::shared_ptr<ChannelSidebar> channel_sidebar;
    std::shared_ptr<Guildbar> guildbar;
    std::shared_ptr<UserSettings> user_settings;
    QTimer* timer;

};
#endif // MAINWINDOW_H
