#include "channel_add.h"
#include "ui_channel_add.h"
#include "user_control.h"
#include <cpr/cpr.h>
#include <json.hpp>
#include <QMessageBox>
#include <iostream>
#include <string>

extern UserManager user;

using json = nlohmann::json;

Channel_Add::Channel_Add(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Channel_Add)
{
    ui->setupUi(this);
}

Channel_Add::~Channel_Add()
{
    delete ui;
}

void Channel_Add::on_create_btn_clicked()
{
    CreateChannel();
}

int Channel_Add::CreateChannel()
{
    if (ui->name_edit->text() == "")
        return 0;

    try {
        cpr::Response response = cpr::Post(
                    cpr::Url{"http://localhost:8000/api/v1/IChannel"},
                    cpr::Multipart{
                        {"guild_id", ui->name_edit->text().toStdString().c_str()},
                        {"name", ui->name_edit->text().toStdString().c_str()},
                    });
        auto json_response = json::parse(response.text);

        if (response.status_code == 200){
            qDebug() << "created channel " << ui->name_edit->text();
            return 0;
        }
        else {
            QMessageBox::warning(nullptr, tr("Can't create new channel"), tr(json_response["message"].dump().c_str()));
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }
    //return 1;
    emit channel_created();
    close();
    return 1;
}


void Channel_Add::on_close_btn_clicked()
{
    close();
}

