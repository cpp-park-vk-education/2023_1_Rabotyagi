#include "registrationwindow.h"
#include "ui_registrationwindow.h"
#include "loginwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QSettings>

RegistrationWindow::RegistrationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RegistrationWindow)
{
    ui->setupUi(this);
    connect(ui->registerButton, &QPushButton::clicked, this, &RegistrationWindow::registerUser);
    connect(ui->goBackButton, &QPushButton::clicked, this, &QDialog::reject);
}

RegistrationWindow::~RegistrationWindow()
{
    delete ui;
}


void RegistrationWindow::registerUser()
{
//     QString response = "{\"access_token\": \"eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ.8wZgcl0G0j1zG8vtKGY6oIJuKvQpNBKpCCx-GBWFWiA\", "
//                        "\"refresh_token\": \"1234567890\"}";
//     QJsonDocument jsonDoc = QJsonDocument::fromJson(response.toUtf8());
//     QString accessToken = jsonDoc["access_token"].toString();
//     QString refreshToken = jsonDoc["refresh_token"].toString();
//     LoginWindow loginWindow;
//     loginWindow.saveTokens(accessToken, refreshToken);
//     accept();



//    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
//    QUrl url("http://example.com/register");
//    QNetworkRequest request(url);
//    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
//    QJsonObject json;
//    json["username"] = ui->usernameEdit->text();
//    json["password"] = ui->passwordEdit->text();
//    QJsonDocument doc(json);
//    QByteArray data = doc.toJson();

//    QNetworkReply *reply = manager->post(request, data);
//    while (!reply->isFinished()) {
//        qApp->processEvents();
//    }

//    if (reply->error() == QNetworkReply::NoError) {
//        QByteArray response = reply->readAll();
//        QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
//        QString accessToken = jsonDoc["access_token"].toString();
//        QString refreshToken = jsonDoc["refresh_token"].toString();
//        LoginWindow loginWindow;
//        loginWindow.saveTokens(accessToken, refreshToken);
//        accept();
//    } else {
//        QMessageBox::warning(this, tr("Registration Failed"), tr("Username already exists."));
//    }

//    reply->deleteLater();
}
