#include "usersettings.h"
#include "ui_usersettings.h"
#include "useroptions.h"
#include "user_control.h"
#include <QString>

UserSettings::UserSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserSettings)
{
    ui->setupUi(this);
    ui->pushButton->setIcon(QIcon(":/img/images/user_settings.png"));
    update_user();
}

UserSettings::~UserSettings()
{
    delete ui;
}

void UserSettings::update_user()
{
    ui->nickname->setText(UserManager::getInstance()->name.c_str());
}

void UserSettings::on_pushButton_clicked()
{
    std::shared_ptr<UserOptions> user_options = std::make_shared<UserOptions>(this);
    user_options->setModal(true);
    user_options->exec();
}

