/*#include "channelsidebar.h"
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

//    active_channel = channels[0];
}

void ChannelSidebar::ChangeActiveChannel(std::shared_ptr<Channel> channel)
{
    active_channel = channel;
    content_window->ui->textBrowser->clear();
    qDebug() << "switched to anoter channel";
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
*/

#include "channelsidebar.h"
#include "channel_add.h"
#include "user_control.h"
#include <iostream>
#include <cpr/cpr.h>
#include "json.hpp"
#include <Qt>

using json = nlohmann::json;



ChannelSidebar::ChannelSidebar(std::shared_ptr<ContentWindow> content_window, QWidget *parent) :
    QScrollArea(parent),
    content_window(content_window),
    active_channel(0)
{
    this->resize(200, 540);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    widget = new QWidget(this);
    layout = new QVBoxLayout(widget);
    layout->setSpacing(10);
    layout->setDirection(QBoxLayout::TopToBottom);

    QPushButton* button = new QPushButton("+ канал", widget);
    button->setFixedSize(QSize(150, 25));
    layout->addWidget(button);
    layout->setAlignment(button, Qt::AlignTop);

    setWidgetResizable(true);
    setWidget(widget);

    connect(button, &QPushButton::clicked, this, &ChannelSidebar::onButtonClicked);

    try {
        cpr::Response response = cpr::Get(
                    cpr::Url{"http://localhost:8000/api/v1/IGuild"},
                    cpr::Parameters{
                        {"guild_id", std::to_string(UserManager::getInstance()->guild_id)}
                    });

        auto channels = json::parse(response.text)["channels"];

        if (response.status_code == 200){
            for (auto channel : channels){
                createChannel(channel["id"].get<int>(), channel["name"].get<std::string>());
            }
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }
}

void ChannelSidebar::onButtonClicked()
{
    auto modal_add = std::make_shared<Channel_Add>(this);
    modal_add->setModal(true);
    //connect(modal_add.get(), &Channel_Add::channel_created, this, &ChannelSidebar::createChannel);
    modal_add->exec();

    qDebug() << "clicked";
}

void ChannelSidebar::onActiveChannelChangeValue(int channel_id){
    active_channel = channel_id;
    UserManager::getInstance()->channel_id = channel_id;
    try {
        cpr::Response response = cpr::Get(
                    cpr::Url{"http://localhost:8000/api/v1/IChannel"},
                    cpr::Parameters{
                        {"channel_id", std::to_string(channel_id)}
                    });

        auto json_response = json::parse(response.text);

        if (response.status_code == 200){

        }

    }
    catch (const std::exception& e) {
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }

    qDebug() << "Changed channel to " << active_channel;
    emit ActiveChannelChanged();
}

void ChannelSidebar::createChannel(int channel_id, std::string name)
{
    //ChannelButton* NewButton = new ChannelButton("Канал " + QString::number(buttons.count() + 1), widget);
    ChannelButton* NewButton = new ChannelButton(name.c_str(), widget);
    NewButton->setIcon(QIcon(":/img/images/Channels-Iconhovered.png"));
    NewButton->channel_id = channel_id;
    qDebug() << "Created channel " << NewButton->channel_id;
    NewButton->setFixedSize(QSize(150, 25));

    buttons.append(NewButton);
    qDebug() << "buttons: " << buttons.size();
    layout->insertWidget(buttons.count() - 1, NewButton);


    connect(NewButton, &QPushButton::clicked, this, [this, NewButton]{ onActiveChannelChangeValue(NewButton->channel_id); });
}

int ChannelSidebar::UpdateChannels(int guild_id)
{
    for (auto current_button: buttons)
    {
        delete current_button;
    }
    buttons.clear();
    try
    {
        cpr::Response response = cpr::Get(
                    cpr::Url{"http://localhost:8000/api/v1/IGuild"},
                    cpr::Parameters{
                        {"guild_id", std::to_string(guild_id).c_str()}
                    });

        auto json_response = json::parse(response.text);

        if (response.status_code == 200){
            auto json_channels = json_response["channels"].get<json>();
            for (auto channel = json_channels.begin(); channel < json_channels.end(); ++channel)
            {
                auto channel_id = (*channel)["id"].get<int>();
                auto channel_name = (*channel)["name"].get<std::string>();
                createChannel(channel_id, channel_name);
            }

        }
    }
    catch (const std::exception& e) {
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }

    qDebug() << "changed to guild " << guild_id;
    return 0;
}
