#include "./loginwindow.hpp"
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
#include <QtCore>
#include <QSettings>

LoginWindow::LoginWindow(int* flag, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow),
    _flag(flag)
{
    ui->setupUi(this);
//    registration_window = new RegistrationWindow(this);
    user_control = new UserControl();
    connect(ui->registrationButton, &QPushButton::clicked, this, &LoginWindow::setFlagToRegistration);
//    this->setWindowFlag(Qt::FramelessWindowHint);

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
    QString password = ui->passwordEdit->text();

    int code = user_control->login(username, password);
    if (code == 0) {
        *_flag = (int)States::to_main_window;
        close();
    } else if (code == 1) {
//        QMessageBox::warning(this, tr("Login Failed"), tr("Server check not passed"));
//        ui->usernameEdit->clear();
//        ui->passwordEdit->clear();
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

void LoginWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        *_flag = (int)States::exit;
    }
}

void LoginWindow::on_close_btn_clicked()
{
    *_flag = (int)States::exit;
    close();
}
