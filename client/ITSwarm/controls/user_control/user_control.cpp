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
#include "data_types.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <cpr/cpr.h>

using json = nlohmann::json;

std::shared_ptr<User> UserManager::instance = 0;
UserControl::UserControl(QObject *parent) : QObject(parent)
{

}

//void fill_user(std::shared_ptr<User>& user, int id, std::string name, std::string password, std::string email, std::string last_login) {
//    user->id = id;
//    user->name = name;
//    user->email = email;
//    user->password = password;
//    user->last_login = last_login;
//}

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
            UserManager::fill_user(
                std::atoi(json_response["id"].dump().c_str()),
                json_response["name"].dump(),
                json_response["email"].dump(),
                json_response["password"].dump(),
                json_response["last_login"].dump());
            QSettings settings("ITSwarm.ini", QSettings::IniFormat);
            settings.setValue("username", json_response["name"].get<std::string>().c_str());
            settings.setValue("password", json_response["password"].get<std::string>().c_str());
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
            UserManager::fill_user(
                std::atoi(json_response["id"].dump().c_str()),
                json_response["name"].dump(),
                json_response["email"].dump(),
                json_response["password"].dump(),
                json_response["last_login"].dump());
            QSettings settings("ITSwarm.ini", QSettings::IniFormat);
            settings.setValue("username", json_response["name"].get<std::string>().c_str());
            settings.setValue("password", json_response["password"].get<std::string>().c_str());
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
}

