#ifndef TST_MY_TEST_H
#define TST_MY_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "loginwindow.h"
#include "registrationwindow.h"
#include "usercontrol.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

using namespace testing;

TEST(my_suit, my_test)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}

TEST(my_suit, save_tokens_test) {
    // Arrange
    QString accessToken = "access_token";
    QString refreshToken = "refresh_token";
    UserControl userControl;

    // Act
    userControl.saveTokens(accessToken, refreshToken);

    // Assert
    QFile file("tokens.json");
    ASSERT_TRUE(file.open(QIODevice::ReadOnly | QIODevice::Text));
    QByteArray data = file.readAll();
    file.close();

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject json = doc.object();

    ASSERT_EQ(json["access_token"].toString(), accessToken);
    ASSERT_EQ(json["refresh_token"].toString(), refreshToken);
}

TEST(my_suit, login_test) {

    UserControl user_control;

    // Некорректный пароль (менее 6 символов)
    ASSERT_EQ(1, user_control.login("username", "pass", "someemail@gmail.com"));

    // Корректный пароль
    ASSERT_EQ(0, user_control.login("username", "password", "someemail@gmail.com"));
}

TEST(my_suit, register_test) {

    UserControl user_control;

    // Некорректный пароль (менее 6 символов)
    ASSERT_EQ(1, user_control.login("username", "pass", "someemail@gmail.com"));

    // Корректный пароль
    ASSERT_EQ(0, user_control.login("username", "password", "someemail@gmail.com"));
}

TEST(my_suit, decodeToken_test) {
    UserControl user_control;

    QByteArray encodedToken = "c775e7b757ede630cd0aa1113bd102661ab38829ca52a6422ab782862f268646";

    QByteArray decodedData;

    user_control.decodeToken(QString::fromUtf8(encodedToken), decodedData);

    EXPECT_EQ(decodedData, QByteArray("1234567890"));

}


TEST(my_suit, parseToken_test) {
    UserControl user_control;

    User expectedUser;

    expectedUser.id = 1;

    expectedUser.name = "SanExpet";

    expectedUser.password = "passworddrowssap";

    expectedUser.email = "alexkrasnoperov09@gmail.com";

    expectedUser.last_login = "2023-01-01 00:00:00";


    QByteArray encodedToken = "vg8ZOI8TP6565v+PLQbgX8ZC34VghUVBgiOAWw6rJx8=";

    User user;

    user_control.parseToken(QString::fromUtf8(encodedToken), user);

    EXPECT_EQ(user.id, expectedUser.id);

    EXPECT_EQ(user.name, expectedUser.name);

    EXPECT_EQ(user.password, expectedUser.password);

    EXPECT_EQ(user.email, expectedUser.email);

    EXPECT_EQ(user.last_login, expectedUser.last_login);

}

#endif // TST_MY_TEST_H
