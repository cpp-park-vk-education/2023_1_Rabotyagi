#ifndef TST_MY_TEST_H
#define TST_MY_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "../../../client2/ITSwarm/windows/login_window/loginwindow.hpp"
#include "../../../client2/ITSwarm/windows/reg_window/reg_window.h"
#include "../../../client2/ITSwarm/controls/user_control/user_control.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QTest>
#include <QCloseEvent>

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

//ДЛЯ СЛЕДУЮЩИХ ТЕСТОВ Я ДЕЛАЛ PUBLIC ТЕСТИРУЕМЫЕ МЕТОДЫ

// закрыть окно через панель
TEST(my_suit, closeEvent)
{
    int flag = 0;
    LoginWindow window(&flag);

    QCloseEvent* event = new QCloseEvent(QCloseEvent::Close);

    window.closeEvent(event);

    EXPECT_EQ(flag, (int)States::exit);
}

//закрыть окно через escape
TEST(LoginWindowTest, keyPressEvent)
{
    int flag = 0;
    LoginWindow window(&flag);

    QKeyEvent* event = new QKeyEvent(QEvent::KeyPress, Qt::Key_Escape, Qt::NoModifier);

    window.keyPressEvent(event);

    EXPECT_EQ(flag, (int)States::exit);
}


TEST(my_suit, loginButton)
{
    int flag = 3;
    LoginWindow loginWindow(&flag);

    // Тест логина
    loginWindow.ui->usernameEdit->setText("username");
    loginWindow.ui->passwordEdit->setText("password");

    // Убедимся, что индикатор состояния не изменился до нажатия на кнопку
    EXPECT_EQ(flag, 0);

    // Нажимаем кнопку и проверяем, что индикатор изменился на нужный
    QTest::mouseClick(loginWindow.ui->loginButton, Qt::LeftButton);
    EXPECT_EQ(flag, (int)LoginWindow::States::to_main_window);
}

TEST(my_suit, regButton)
{
    int flag = 2;
    LoginWindow regWindow(&flag);

    // Тест логина
    regWindow.ui->usernameEdit->setText("username");
    regWindow.ui->passwordEdit->setText("password");
    regWindow.ui->emailEdit->setText("email@gmail.com");
    regWindow.ui->confirmPasswordEdit->setText("password");

    // Убедимся, что индикатор состояния не изменился до нажатия на кнопку
    EXPECT_EQ(flag, 0);

    // Нажимаем кнопку и проверяем, что индикатор изменился на нужный
    QTest::mouseClick(regWindow.ui->registerButton, Qt::LeftButton);
    EXPECT_EQ(flag, (int)RegistrationWindow::States::to_main_window);
}

#endif // TST_MY_TEST_H
