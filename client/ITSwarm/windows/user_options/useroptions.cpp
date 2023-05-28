#include "useroptions.h"
#include "ui_useroptions.h"
#include "user_control.h"
#include <QString>

UserOptions::UserOptions(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserOptions)
{
    ui->setupUi(this);
}

UserOptions::~UserOptions()
{
    delete ui;
}

void UserOptions::on_create_btn_clicked()
{
    auto settings = UserManager::getSettings();
    settings->remove(QString("username"));
    settings->remove(QString("password"));
    this->close();
}

