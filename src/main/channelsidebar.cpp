#include "channelsidebar.h"
#include "ui_channelsidebar.h"

ChannelSidebar::ChannelSidebar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChannelSidebar)
{
    ui->setupUi(this);

    ui->textChannelButton_1->setIcon(QIcon(":/img/images/Channels-Iconhovered.png"));
    ui->textChannelButton_2->setIcon(QIcon(":/img/images/Channels-Iconhovered.png"));
    ui->textChannelButton_3->setIcon(QIcon(":/img/images/Channels-Iconhovered.png"));
    ui->voiceChannelButton_1->setIcon(QIcon(":/img/images/Channels-Iconvoice hovered.png"));
    ui->voiceChannelButton_2->setIcon(QIcon(":/img/images/Channels-Iconvoice hovered.png"));
    ui->voiceChannelButton_3->setIcon(QIcon(":/img/images/Channels-Iconvoice hovered.png"));

    ConnectToChannelControl();
    channels.push_back(std::make_shared<Channel>(Channel("1", ChannelType::Message)));
    channels.push_back(std::make_shared<Channel>(Channel("2", ChannelType::Message)));
    channels.push_back(std::make_shared<Channel>(Channel("3", ChannelType::Message)));

    active_channel = channels[0];
}

ChannelSidebar::~ChannelSidebar()
{
    delete ui;
}

void ChannelSidebar::ConnectToChannelControl()
{
    channel_control = std::make_shared<ChannelControl>();
}

void ChannelSidebar::on_textChannelButton_1_clicked()
{
    active_channel = channels[0];
}


void ChannelSidebar::on_textChannelButton_2_clicked()
{
    active_channel = channels[1];
}


void ChannelSidebar::on_textChannelButton_3_clicked()
{
    active_channel = channels[2];
}

