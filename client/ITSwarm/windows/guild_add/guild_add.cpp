#include "guild_add.hpp"
#include "ui_guild_add.h"
#include <cpr/cpr.h>
#include "user_control.h"
#include <json.hpp>
#include <QMessageBox>
#include <iostream>
#include <string>


extern UserManager user;

using json = nlohmann::json;

Guild_Add::Guild_Add(Guildbar *parent) :
    QDialog(parent),
    ui(new Ui::Guild_Add)
{
    ui->setupUi(this);
}

int Guild_Add::CreateGuild()
{
    try {
        cpr::Response response = cpr::Post(
                    cpr::Url{"http://localhost:8000/api/v1/IGuild"},
                    cpr::Multipart{
                        {"guild_name", ui->name_edit->text().toStdString().c_str()},
                        {"owner_id", std::to_string(user.getInstance()->id).c_str()},
                    });
        auto json_response = json::parse(response.text);

        if (response.status_code == 200){
            qDebug() << "created guild " << ui->name_edit->text();
            return 0;
        }
        else {
            QMessageBox::warning(nullptr, tr("Can't create new guild"), tr(json_response["message"].dump().c_str()));
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }
    //return 1;
    emit guild_created();
    close();
    return 1;
}

Guild_Add::~Guild_Add()
{
    delete ui;
}

void Guild_Add::on_create_btn_clicked()
{
    CreateGuild();
}


void Guild_Add::on_close_btn_clicked()
{
    close();
}

