#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include "../reg_window/reg_window.h"
#include "../main_window/main_window.h"
#include "../../controls/user_control/user_control.h"
//#include <jwt.h>
#include <QLineEdit>
#include "./loginwindow.h"
#include "../main_window/main_window.h"
#include "ui_loginwindow.h"
#include "../../controls/user_control/user_control.h"
#include <QMessageBox>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QSettings>
namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog {
    Q_OBJECT

public:
    enum class States {
        crit_error = -1,
        error = 0,
        to_main_window = 1,
        to_reg_window = 2

    };

    explicit LoginWindow(int& flag, QWidget *parent = nullptr) :
        QDialog(parent),
        ui(new Ui::LoginWindow)
    {
        ui->setupUi(this);
//        registration_window = new RegistrationWindow(this);
        user_control = new UserControl();

        // Connect the showRegistrationWindow slot to the registerButton clicked signal
//        connect(ui->registrationButton, &QPushButton::clicked, this, &LoginWindow::openRegistrationWindow);

        // Connect the goBack signal from the registration window to the show() slot of the login window
//        connect(registration_window, &RegistrationWindow::goBack, this, &LoginWindow::show);

    //    connect(ui->loginButton, &QPushButton::clicked, this, &LoginWindow::login);
    }
    ~LoginWindow() {
        delete ui;
//        delete registration_window;
        delete user_control;
    };

private slots:
    //void login();
    void on_loginButton_clicked();
public slots:
    //void saveTokens(const QString &accessToken, const QString &refreshToken);

private:
    int* _flag;
    Ui::LoginWindow *ui;
    UserControl* user_control;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
};

#endif // LOGINWINDOW_H
