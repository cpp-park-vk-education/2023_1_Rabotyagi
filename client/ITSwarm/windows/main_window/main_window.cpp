#include "main_window.h"
#include "ui_main_window.h"
#include "settingswindow.h"
#include "gitconnection.h"
#include "guildconnector.h"
#include "guild_add.hpp"
#include <memory>
#include <QtWidgets>
#include <QPixmap>
#include <QIcon>
#include <QFont>
#include <QHBoxLayout>
//#include "sidebar.h"

MainWindow::MainWindow(int* flag, QWidget *parent)
    :QMainWindow(parent),
    _flag(flag),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMainWindow::setWindowTitle("ITSwarm");


    content_window = std::make_shared<ContentWindow>(this);
    content_window->move(200, 80);
    channel_sidebar = std::make_shared<ChannelSidebar>(content_window, this);

    channel_sidebar->move(0, 80);

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
    user_settings->move(0, 620);

    timer = new QTimer();
    timer->start(2000);
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


void MainWindow::on_connect_clicked()
{
    auto guild_connector = std::make_shared<GuildConnector>(this);
    connect(guild_connector.get(), &GuildConnector::guild_connected, guildbar.get(), &Guildbar::UpdateGuildList);
    guild_connector->setModal(true);
    guild_connector->exec();
}


void MainWindow::on_add_new_clicked()
{
    auto guild_creator = std::make_shared<Guild_Add>(this);
    connect(guild_creator.get(), &Guild_Add::guild_created, guildbar.get(), &Guildbar::UpdateGuildList);
    guild_creator->setModal(true);
    guild_creator->exec();
}

