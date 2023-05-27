#include "channelsidebar.h"
#include "ui_channelsidebar.h"
#include "ui_contentwindow.h"

ChannelSidebar::ChannelSidebar(std::shared_ptr<ContentWindow> content_window, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChannelSidebar),
    content_window(content_window)
{
    ui->setupUi(this);

    ui->textChannelButton_1->setIcon(QIcon(":/img/images/Channels-Iconhovered.png"));
    ui->textChannelButton_2->setIcon(QIcon(":/img/images/Channels-Iconhovered.png"));
    ui->textChannelButton_3->setIcon(QIcon(":/img/images/Channels-Iconhovered.png"));
    ui->voiceChannelButton_1->setIcon(QIcon(":/img/images/Channels-Iconvoice hovered.png"));
    ui->voiceChannelButton_2->setIcon(QIcon(":/img/images/Channels-Iconvoice hovered.png"));
    ui->voiceChannelButton_3->setIcon(QIcon(":/img/images/Channels-Iconvoice hovered.png"));

    //ConnectToChannelControl();
//    channels.push_back(std::make_shared<Channel>(Channel("1", ChannelType::Message)));
//    channels.push_back(std::make_shared<Channel>(Channel("2", ChannelType::Message)));
//    channels.push_back(std::make_shared<Channel>(Channel("3", ChannelType::Message)));

    active_channel = channels[0];
}

void ChannelSidebar::ChangeActiveChannel(std::shared_ptr<Channel> channel)
{
    active_channel = channel;
    content_window->ui->textBrowser->clear();
    qDebug() << "switched to channel 1";
}


ChannelSidebar::~ChannelSidebar()
{
    delete ui;
}

/*void ChannelSidebar::ConnectToChannelControl()
{
    channel_control = std::make_shared<ChannelControl>();
}*/

void ChannelSidebar::on_textChannelButton_1_clicked()
{
    ChangeActiveChannel(channels[0]);
    content_window->ChangeActiveChannel(active_channel);
}


void ChannelSidebar::on_textChannelButton_2_clicked()
{
    ChangeActiveChannel(channels[1]);
    content_window->ChangeActiveChannel(active_channel);
}


void ChannelSidebar::on_textChannelButton_3_clicked()
{
    ChangeActiveChannel(channels[2]);
    content_window->ChangeActiveChannel(active_channel);
}

