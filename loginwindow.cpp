#include "loginwindow.h"
#include "mainwindow.h"
#include "ui_loginwindow.h"
#include "usercontrol.h"
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QSettings>

LoginWindow::LoginWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    registration_window = new RegistrationWindow(this);
    user_control = new UserControl();

    // Connect the showRegistrationWindow slot to the registerButton clicked signal
    connect(ui->registrationButton, &QPushButton::clicked, this, &LoginWindow::openRegistrationWindow);

    // Connect the goBack signal from the registration window to the show() slot of the login window
    connect(registration_window, &RegistrationWindow::goBack, this, &LoginWindow::show);

//    connect(ui->loginButton, &QPushButton::clicked, this, &LoginWindow::login);
}

LoginWindow::~LoginWindow()
{
    delete ui;
    delete registration_window;
    delete user_control;
}

void LoginWindow::on_loginButton_clicked(){
    QString username = ui->usernameEdit->text();
    QString email = ui->emailEdit->text();
    QString password = ui->passwordEdit->text();

    int code = user_control->login(username, password, email);
    if (code == 0) {
        MainWindow *mainWindow = new MainWindow;
        mainWindow->show();
        close();
    } else if (code == 1) {
        QMessageBox::warning(this, tr("Login Failed"), tr("Server check not passed"));
        ui->usernameEdit->clear();
        ui->passwordEdit->clear();
        ui->emailEdit->clear();
    }
}

void LoginWindow::openRegistrationWindow()
{
    registration_window->show();
    hide();
}
