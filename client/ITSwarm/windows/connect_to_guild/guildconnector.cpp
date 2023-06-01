#include "guildconnector.h"
#include "ui_guildconnector.h"
#include <cpr/cpr.h>
#include "user_control.h"
#include <json.hpp>
#include <QMessageBox>
#include <iostream>
#include <string>
#include <QString>
#include "user_control.h"

using json = nlohmann::json;

GuildConnector::GuildConnector(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GuildConnector)
{
    ui->setupUi(this);
}

GuildConnector::~GuildConnector()
{
    delete ui;
}

int GuildConnector::ConnectToGuild()
{
    if (ui->name_edit->text() == "")
        return 0;

    try {
        cpr::Response response = cpr::Post(
                    cpr::Url{"http://localhost:8000/api/v1/IGuild"},
                    cpr::Multipart{
                        {"user_id", std::to_string(UserManager::getInstance()->id).c_str()},
                        {"guild_name", ui->name_edit->text().toStdString().c_str()}
                    });
        auto json_response = json::parse(response.text);

        if (response.status_code == 200){

            qDebug() << "connected to guild successfully" << ui->name_edit->text();
            emit guild_connected();
//            return 0;
        }
        else {
            QMessageBox::warning(nullptr, tr("Can't create new guild"), tr(json_response["message"].dump().c_str()));
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }
    //return 1;
    emit guild_connected();
    close();
    return 1;
}



void GuildConnector::on_create_btn_clicked()
{
    ConnectToGuild();
}


void GuildConnector::on_close_btn_clicked()
{
    close();
}


void GuildConnector::on_name_edit_returnPressed()
{
    on_create_btn_clicked();
}
