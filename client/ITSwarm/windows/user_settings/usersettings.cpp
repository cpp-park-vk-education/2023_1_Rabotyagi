#include "usersettings.h"
#include "ui_usersettings.h"
#include "useroptions.h"

UserSettings::UserSettings(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UserSettings)
{
    ui->setupUi(this);
    ui->pushButton->setIcon(QIcon(":/img/images/user_settings.png"));
}

UserSettings::~UserSettings()
{
    delete ui;
}

void UserSettings::on_pushButton_clicked()
{
    std::shared_ptr<UserOptions> user_options = std::make_shared<UserOptions>(this);
    user_options->setModal(true);
    user_options->exec();
}

