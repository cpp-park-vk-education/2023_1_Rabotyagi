#include "./loginwindow.hpp"
#include "../main_window/main_window.h"
#include "ui_loginwindow.h"
#include "../../controls/user_control/user_control.h"
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QSettings>
#include <QCloseEvent>

LoginWindow::LoginWindow(int* flag, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow),
    _flag(flag)
{
    ui->setupUi(this);
//    registration_window = new RegistrationWindow(this);
    user_control = new UserControl();
    connect(ui->registrationButton, &QPushButton::clicked, this, &LoginWindow::setFlagToRegistration);

    //connect(ui->registrationButton, &QPushButton::clicked, this, &LoginWindow::openRegistrationWindow);

    //connect(registration_window, &RegistrationWindow::goBack, this, &LoginWindow::show);

//    connect(ui->loginButton, &QPushButton::clicked, this, &LoginWindow::login);
}

LoginWindow::~LoginWindow()
{
    delete ui;
    delete user_control;
}

void LoginWindow::on_loginButton_clicked(){
    QString username = ui->usernameEdit->text();
    QString email = ui->emailEdit->text();
    QString password = ui->passwordEdit->text();

    int code = user_control->login(username, password, email);
    if (code == 0) {
        *_flag = (int)States::to_main_window;
        close();
    } else if (code == 1) {
        QMessageBox::warning(this, tr("Login Failed"), tr("Server check not passed"));
        ui->usernameEdit->clear();
        ui->passwordEdit->clear();
        ui->emailEdit->clear();
    }
}


void LoginWindow::setFlagToRegistration() {
    *_flag = (int)States::to_reg_window;
    close();
}


void LoginWindow::closeEvent(QCloseEvent *event)
{
    if( event->spontaneous()){
        *_flag = (int)States::exit;
    }
}
