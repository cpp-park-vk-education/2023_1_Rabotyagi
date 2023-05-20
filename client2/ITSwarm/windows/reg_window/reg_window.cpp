#include "reg_window.h"
#include "./ui_reg_window.h"
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

RegistrationWindow::RegistrationWindow(int* flag, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistrationWindow),
    _flag(flag)
{
    ui->setupUi(this);
    user_control = new UserControl(this);
    //connect(ui->registerButton, &QPushButton::clicked, this, &RegistrationWindow::registerUser);
//    connect(ui->goBackButton, &QPushButton::clicked, this, &QDialog::reject);
    connect(ui->goBackButton, &QPushButton::clicked, this, &RegistrationWindow::setFlagToLogin);
}

RegistrationWindow::~RegistrationWindow()
{
    delete ui;
    delete user_control;
}


void RegistrationWindow::on_registerButton_clicked(){
    QString username = ui->usernameEdit->text();
    QString email = ui->emailEdit->text();
    QString password = ui->passwordEdit->text();
    QString confirm_password = ui->confirmPasswordEdit->text();

    if (!username.isEmpty() && !password.isEmpty() && !confirm_password.isEmpty() && !email.isEmpty() && (password == confirm_password) ){
        int code = user_control->registerUser(username, password, email);

        if (code == 0) {
            *_flag = (int)States::to_main_window;
            close();
        } else if (code == 1) {
            // QMessageBox::warning(qobject_cast<QWidget *> (parent()), tr("Invalid registration"), tr("Server check not passed"));
            ui->usernameEdit->clear();
            ui->passwordEdit->clear();
            ui->emailEdit->clear();
            ui->confirmPasswordEdit->clear();
        }
    } else {
        ui->usernameEdit->clear();
        ui->passwordEdit->clear();
        ui->emailEdit->clear();
        ui->confirmPasswordEdit->clear();
    }
}

void RegistrationWindow::setFlagToLogin() {
    *_flag = (int)States::to_log_window;
    close();
}

void RegistrationWindow::closeEvent(QCloseEvent *event)
{
    if( event->spontaneous()){
        *_flag = (int)States::exit;
    }
}

void RegistrationWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        *_flag = (int)States::exit;
    }
}
