#include "guildbar.h"
#include <QDebug>
#include <Qt>
#include "guild_add.hpp"
#include "user_control.h"
#include <cpr/cpr.h>
#include <json.hpp>
#include <iostream>
#include "channelsidebar.h"

using json = nlohmann::json;

Guildbar::Guildbar(QWidget *parent) : QScrollArea(parent), active_guild(0)
{
    this->resize(600, 62);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    widget = new QWidget(this);
    layout = new QHBoxLayout(widget);
    layout->setSpacing(10);
    layout->setDirection(QBoxLayout::LeftToRight);

//    QPushButton* button = new QPushButton("+ сервер", widget);
//    button->setFixedSize(QSize(70, 20));
//    layout->addWidget(button);
//    layout->setAlignment(button, Qt::AlignLeft);

    setWidgetResizable(true);
    setWidget(widget);

    UpdateGuildList();
    //connect(button, &QPushButton::clicked, this, &Guildbar::onButtonClicked);

//    try {
//        cpr::Response response = cpr::Get(
//                    cpr::Url{"http://localhost:8000/api/v1/IUser/guild"},
//                    cpr::Parameters{
//                        {"user_id", std::to_string(UserManager::getInstance()->id)}
//                    });

//        auto json_response = json::parse(response.text)["guilds"];

//        if (response.status_code == 200){
//            for (auto guild : json_response){
//                createGuild(guild["id"].get<int>(), guild["name"].get<std::string>());
//            }
//        }

//    }
//    catch (const std::exception& e) {
//        std::cerr << "hello" << '\n';
//        //std::cerr << "Request failed, error: " << e.what() << '\n';
//    }
}

//void Guildbar::onButtonClicked()
//{
//    auto modal_add = std::make_shared<Guild_Add>(this);
//    modal_add->setModal(true);
//    modal_add->exec();
//}

void Guildbar::onActiveGuildChangeValue(int guild_id){
    active_guild = guild_id;
    UserManager::getInstance()->guild_id = guild_id;

    try {
        cpr::Response response = cpr::Get(
                    cpr::Url{"http://localhost:8000/api/v1/IGuild"},
                    cpr::Parameters{
                        {"guild_id", std::to_string(guild_id)}
                    });

        auto guilds = json::parse(response.text);

        if (response.status_code == 200){

        }

    }
    catch (const std::exception& e) {
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }
    qDebug() << "Changed guild to " << active_guild;

    emit ActiveGuildChanged();
}

void Guildbar::createGuild(int guild_id, std::string name)
{
    GuildButton* NewButton = new GuildButton(name.c_str(), widget);
    NewButton->guild_id = guild_id;
    qDebug() << "Created guild " << NewButton->guild_id;
    NewButton->setFixedSize(QSize(150, 20));

    buttons.append(NewButton);
    layout->insertWidget(buttons.count() - 1, NewButton);

    connect(NewButton, &QPushButton::clicked, this, [this, NewButton]{ onActiveGuildChangeValue(NewButton->guild_id); });
}

void Guildbar::UpdateGuildList()
{
    try {
        cpr::Response response = cpr::Get(
                    cpr::Url{"http://localhost:8000/api/v1/IUser/guild"},
                    cpr::Parameters{
                        {"user_id", std::to_string(UserManager::getInstance()->id)}
                    });

        auto json_response = json::parse(response.text)["guilds"];

        if (response.status_code == 200){
            for (auto guild : json_response){
                createGuild(guild["id"].get<int>(), guild["name"].get<std::string>());
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "hello" << '\n';
        //std::cerr << "Request failed, error: " << e.what() << '\n';
    }
}

