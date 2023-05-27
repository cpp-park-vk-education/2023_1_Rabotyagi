#include "main_window.h"
#include "ui_main_window.h"
#include "settingswindow.h"
#include "gitconnection.h"
#include <memory>
#include <QtWidgets>
#include <QPixmap>
#include <QIcon>
#include <QFont>
//#include "sidebar.h"

MainWindow::MainWindow(int* flag, QWidget *parent)
    :QMainWindow(parent),
    ui(new Ui::MainWindow),
    _flag(flag)
{
    ui->setupUi(this);
    QMainWindow::setWindowTitle("ITSwarm");
    ui->gitButton->setIcon(QIcon(":/img/images/icons8-git-50.png"));
    ui->settingsButton->setIcon(QIcon(":/img/images/icons8-settings-50.png"));

    //client = std::make_shared<TCPClient>();
    //client->ConnectToServer("127.0.0.1", 8000);
//    client = std::make_shared<Client>();

    content_window = std::make_shared<ContentWindow>(this);
    content_window->move(130, 60);

    userbar = std::make_shared<Userbar>(this);
    userbar->move(970, 110);

    //sidebar = std::make_shared<Sidebar>(this);
    //sidebar->move(10, 60);

    channel_sidebar = std::make_shared<ChannelSidebar>(content_window, this);
    channel_sidebar->move(10, 60);

    channel_sidebar->on_textChannelButton_1_clicked();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_settingsButton_clicked()
{
    settings = std::make_shared<SettingsWindow>(this);
    settings->setModal(true);
    settings->exec();
}

void MainWindow::on_gitButton_clicked()
{
    git = std::make_shared<GitConnection>(this);
    git->show();
}

