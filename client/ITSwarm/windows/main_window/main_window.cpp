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
    _flag(flag),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMainWindow::setWindowTitle("ITSwarm");
    ui->gitButton->setIcon(QIcon(":/img/images/icons8-git-50.png"));
    ui->settingsButton->setIcon(QIcon(":/img/images/icons8-settings-50.png"));

    content_window = std::make_shared<ContentWindow>(this);
    content_window->move(200, 60);

//    userbar = std::make_shared<Userbar>(this);
//    userbar->move(970, 110);

//    //sidebar = std::make_shared<Sidebar>(this);
//    //sidebar->move(10, 60);

    channel_sidebar = std::make_shared<ChannelSidebar>(content_window, this);
    //channel_sidebar = new ChannelSidebar(content_window, this);
    channel_sidebar->move(10, 60);

//    channel_sidebar->on_textChannelButton_1_clicked();
    guildbar = std::make_shared<Guildbar>(this);
    //guildbar = new Guildbar(this);
    guildbar->move(250, 5);

    //auto change_active_channel = [&] () {channel_sidebar->ChangeActiveChannel(guildbar->GetActiveGuild()); };

    auto change_active_guild = [&](){channel_sidebar->UpdateChannels(guildbar->GetActiveGuild());};
    connect(guildbar.get(), &Guildbar::ActiveGuildChanged, channel_sidebar.get(),
            change_active_guild);

    auto clear_content_window = [&](){content_window->ClearContentWindow();};
    connect(channel_sidebar.get(), &ChannelSidebar::ActiveChannelChanged, content_window.get(),
            clear_content_window);

    auto change_active_channel = [&](){content_window->UpdateMessages(channel_sidebar->GetActiveChannel());};
    connect(channel_sidebar.get(), &ChannelSidebar::ActiveChannelChanged, content_window.get(),
            change_active_channel);


    user_settings = std::make_shared<UserSettings>(this);
    user_settings->move(0, 560);

    timer = new QTimer();
    timer->start(1000);
    connect(timer, &QTimer::timeout, content_window.get(), clear_content_window);
    connect(timer, &QTimer::timeout, content_window.get(), change_active_channel);

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

