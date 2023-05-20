#include "user_control.h"
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QSettings>
#include <QString>
#include <QCryptographicHash>



UserControl::UserControl(QObject *parent) : QObject(parent)
{

}


void UserControl::decodeToken(const QString& encryptedToken, QByteArray &decodedData) {
    QByteArray tokenBytes = encryptedToken.toUtf8();
    QByteArray hash = QCryptographicHash::hash(tokenBytes, QCryptographicHash::Sha256);
    decodedData = QByteArray::fromBase64(tokenBytes.remove(0, 32));
    decodedData = qUncompress(decodedData.remove(decodedData.length() - hash.length(), hash.length()));
}

void UserControl::parseToken(const QString& encryptedToken, User& user) {
    QByteArray decodedData;
    decodeToken(encryptedToken, decodedData);

    QJsonDocument jsonDoc = QJsonDocument::fromJson(decodedData);
    QJsonObject jsonObj = jsonDoc.object();

    user.id = jsonObj["id"].toInt();
    user.name = jsonObj["name"].toString().toStdString();
    user.password = jsonObj["password"].toString().toStdString();
    user.email = jsonObj["email"].toString().toStdString();
    user.last_login = jsonObj["last_login"].toString().toStdString();
}


int UserControl::login(const QString& username, const QString& password, const QString& email )
{
    if (password.length() >= 6){
         QString response = "{\"access_token\": \"eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ.8wZgcl0G0j1zG8vtKGY6oIJuKvQpNBKpCCx-GBWFWiA\", "
                            "\"refresh_token\": \"1234567890\"}";
         QJsonDocument jsonDoc = QJsonDocument::fromJson(response.toUtf8());
         QString accessToken = jsonDoc["access_token"].toString();
         QString refreshToken = jsonDoc["refresh_token"].toString();
         saveTokens(accessToken, refreshToken);
         parseToken(accessToken, user);
         return 0;
    } else {
        return 1;
    }



//    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
//    QUrl url("http://example.com/login");
//    QNetworkRequest request(url);
//    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

//    QJsonObject json;
//    json["username"] = username;
//    json["password"] = password;
//    QJsonDocument doc(json);
//    QByteArray data = doc.toJson();

//    //    Этот код отправляет POST-запрос на сервер с использованием QNetworkAccessManager и блокирует выполнение программы до тех пор,
//    //    пока ответ от сервера не будет получен. Закоментим его чтобы захардкодить ответ сервера для тестов.
//    QNetworkReply *reply = manager->post(request, data);
//    while (!reply->isFinished()) {
//     qApp->processEvents();
//    }

//    if (reply->error() == QNetworkReply::NoError) {
//     QByteArray response = reply->readAll();
//     QJsonDocument jsonDoc = QJsonDocument::fromJson(response);
//     QString accessToken = jsonDoc["access_token"].toString();
//     QString refreshToken = jsonDoc["refresh_token"].toString();
//     saveTokens(accessToken, refreshToken);
//     reply->deleteLater();
//     return 0;
//    } else {
//     reply->deleteLater();
//     return 1;
//    }
}

void UserControl::saveTokens(const QString &accessToken, const QString &refreshToken)
{
     QJsonObject json;
     json["access_token"] = accessToken;
     json["refresh_token"] = refreshToken;
     QJsonDocument doc(json);

     QFile file("tokens.json");
     if (file.open(QIODevice::WriteOnly)) {
         file.write(doc.toJson());
         file.close();
     }
}

int UserControl::registerUser(const QString& username, const QString& password, const QString& email)
{
    if (password.length() >= 6){
         QString response = "{\"access_token\": \"eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ.8wZgcl0G0j1zG8vtKGY6oIJuKvQpNBKpCCx-GBWFWiA\", "
                            "\"refresh_token\": \"1234567890\"}";
         QJsonDocument jsonDoc = QJsonDocument::fromJson(response.toUtf8());
         QString accessToken = jsonDoc["access_token"].toString();
         QString refreshToken = jsonDoc["refresh_token"].toString();
         saveTokens(accessToken, refreshToken);
         parseToken(accessToken, user);
         return 0;
    } else {
        return 1;
    }





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

