#ifndef USERCONTROL_H
#define USERCONTROL_H
#include "data_types.hpp"
#include <QObject>

class UserControl : public QObject
{
    Q_OBJECT

public:
    explicit UserControl(QObject *parent = nullptr);
public slots:
//    void decodeToken(const QString& encryptedToken, QByteArray &decodedData);
//    void parseToken(const QString& encryptedToken, User& user);
//    void saveTokens(const QString &accessToken, const QString &refreshToken);
    int registerUser(const QString& username, const QString& password, const QString& email);
    int login(const QString& username, const QString& password, const QString& email);
private:
};

#endif // USERCONTROL_H
