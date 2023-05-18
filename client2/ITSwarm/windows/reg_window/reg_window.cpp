#include "reg_window.h"
#include "./ui_reg_window.h"
#include "../login_window/loginwindow.hpp"
#include "../main_window/main_window.h"
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QSettings>

RegistrationWindow::RegistrationWindow(int* flag, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistrationWindow),
    _flag(flag)
{
    ui->setupUi(this);
    user_control = new UserControl(this);
    //connect(ui->registerButton, &QPushButton::clicked, this, &RegistrationWindow::registerUser);
    connect(ui->goBackButton, &QPushButton::clicked, this, &QDialog::reject);
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

    if (!username.isEmpty() && !password.isEmpty() && !confirm_password.isEmpty() && (password == confirm_password) ){
        int code = user_control->registerUser(username, password, email);

        if (code == 0) {
            MainWindow *mainWindow = new MainWindow(_flag);
            mainWindow->show();
            close();
        } else if (code == 1) {
            QMessageBox::warning(this, tr("Invalid registration"), tr("Server check not passed"));
            ui->usernameEdit->clear();
            ui->passwordEdit->clear();
        }
    } else {
        QMessageBox::warning(this, tr("Invalid fields values"), tr("Some fialds are empty or password and conf password are not the same") );
        ui->usernameEdit->clear();
        ui->passwordEdit->clear();
    }
}
