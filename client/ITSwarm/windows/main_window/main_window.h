#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "settingswindow.h"
#include "gitconnection.h"
#include <memory>
#include "userbar.h"
#include "contentwindow.h"
//#include "sidebar.h"
#include "channelsidebar.h"
#include <QMainWindow>
#include <QVector>
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
    virtual ~MainWindow();

public slots:
    void on_settingsButton_clicked();
    void on_gitButton_clicked();

private:
    Ui::MainWindow *ui;
    int* _flag;

//    std::shared_ptr<Client> client;
    //std::shared_ptr<TCPClient> client;

    std::shared_ptr<SettingsWindow> settings;
    std::shared_ptr<GitConnection> git;

    QString nickname;

    std::shared_ptr<Userbar> userbar;
    std::shared_ptr<ContentWindow> content_window;
    //std::shared_ptr<Sidebar> sidebar;
    std::shared_ptr<ChannelSidebar> channel_sidebar;

};
#endif // MAINWINDOW_H
