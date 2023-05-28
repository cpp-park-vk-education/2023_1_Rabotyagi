#ifndef USERCONTROL_H
#define USERCONTROL_H
#include "data_types.hpp"
#include <QObject>
#include "json.hpp"
#include <QSettings>


class UserControl : public QObject
{
    Q_OBJECT

public:
    explicit UserControl(QObject *parent = nullptr);
    int save_settings();
    nlohmann::json load_settings();
public slots:
//    void decodeToken(const QString& encryptedToken, QByteArray &decodedData);
//    void parseToken(const QString& encryptedToken, User& user);
//    void saveTokens(const QString &accessToken, const QString &refreshToken);
    int registerUser(const QString& username, const QString& password, const QString& email);
    int login(const QString& username, const QString& password);
private:

};

enum LoginProcessStatus {
    OK = 0,
    WrongUsername = 1,
    WrongPassword = 2
};

class UserManager {
private:
    static std::shared_ptr<User> instance;
    static std::shared_ptr<QSettings> settings;
    UserManager() {}
    UserManager(const UserManager&);
    UserManager& operator=( UserManager& );
public:
    static std::shared_ptr<User> getInstance() {
        if (!instance)
            instance = std::make_shared<User>();
        return instance;
    }

    static std::shared_ptr<QSettings> getSettings() {
        if (!settings)
            settings = std::make_shared<QSettings>("ITSwarm.ini", QSettings::IniFormat);
        return settings;
    }

    static void fill_user(int id, std::string name, std::string password, std::string email, std::string last_login) {
        if (!instance)
            getInstance();

        instance->id = id;
        instance->name = name;
        instance->email = email;
        instance->password = password;
        instance->last_login = last_login;
    }

//    static void clear_user(){
//        if (!instance)
//            getInstance();

//        inst
//    }
};
#endif // USERCONTROL_H
