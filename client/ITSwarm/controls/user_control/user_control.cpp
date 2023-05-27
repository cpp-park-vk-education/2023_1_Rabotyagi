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
#include "json.hpp"
#include "HTTPRequest.hpp"
#include "data_types.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <cpr/cpr.h>
#include <user.hpp>

using json = nlohmann::json;

UserControl::UserControl(QObject *parent) : QObject(parent)
{

}

std::shared_ptr<User> fill_user(int id, std::string name, std::string password, std::string email, std::string last_login) {
    auto user = std::make_shared<User>();
    UserManager::instance()->id = id;
    UserManager::instance()->name = name;
    UserManager::instance()->email = email;
    UserManager::instance()->password = password;
    UserManager::instance()->last_login = last_login;

    return user;
}

int UserControl::login(const QString& username, const QString& password)
{
    try {
        cpr::Response response = cpr::Get(
                    cpr::Url{"http://localhost:8000/api/v1/IUser"},
                    cpr::Parameters{
                        {"username", username.toStdString().c_str()},
                        {"password", password.toStdString().c_str()}
                    });
        auto json_response = json::parse(response.text);

        if (response.status_code == 200){
            auto user = fill_user(
                std::atoi(json_response["id"].dump().c_str()),
                json_response["name"].dump(),
                json_response["email"].dump(),
                json_response["password"].dump(),
                json_response["last_login"].dump());
            return 0;
        }
        else {
            QMessageBox::warning(nullptr, tr("Ошибка авторизации"), tr(json_response["message"].dump().c_str()));
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }
    return 1;
}

int UserControl::registerUser(const QString& username, const QString& password, const QString& email)
{
    try {
        cpr::Response response = cpr::Post(
                    cpr::Url{"http://localhost:8000/api/v1/IUser"},
                    cpr::Multipart{
                        {"username", username.toStdString().c_str()},
                        {"password", password.toStdString().c_str()},
                        {"email", email.toStdString().c_str()},
                    });

        auto json_response = json::parse(response.text);

        if (response.status_code == 200){
            auto user = fill_user(
                std::atoi(json_response["id"].dump().c_str()),
                json_response["name"].dump(),
                json_response["email"].dump(),
                json_response["password"].dump(),
                json_response["last_login"].dump());
            return 0;
        }
        else {
            QMessageBox::warning(nullptr, tr("Login Failed"), tr(json_response["message"].dump().c_str()));
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }
    return 1;

//    client.SendToServer(request.dump);
//    QString replie = client.get_message();
//    replie.toStdString();
//    request.load_from_string(replie);
//    if ( request["meta"]["status"] == 200 ) {
//        fill_user(request["params"]["id"], request["params"]["username"], request["params"]["email"], request["params"]["password"], request["params"]["last_login"] );
//        return 0;
//    } else {
//        return 1;
//    }

//    if (password.length() >= 6){
//         QString response = "{\"access_token\": \"eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJzdWIiOiIxMjM0NTY3ODkwIiwibmFtZSI6IkpvaG4gRG9lIiwiaWF0IjoxNTE2MjM5MDIyfQ.8wZgcl0G0j1zG8vtKGY6oIJuKvQpNBKpCCx-GBWFWiA\", "
//                            "\"refresh_token\": \"1234567890\"}";
//         QJsonDocument jsonDoc = QJsonDocument::fromJson(response.toUtf8());
//         QString accessToken = jsonDoc["access_token"].toString();
//         QString refreshToken = jsonDoc["refresh_token"].toString();
//         saveTokens(accessToken, refreshToken);
//         parseToken(accessToken, user);
//         return 0;
//    } else {
//        return 1;
//    }
}

