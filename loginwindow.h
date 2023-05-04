#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include "registrationwindow.h"
#include "mainwindow.h"
#include <jwt.h>
#include <QLineEdit>
namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog {
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void login();
    void openRegistrationWindow();
public slots:
    void saveTokens(const QString &accessToken, const QString &refreshToken);

private:
    Ui::LoginWindow *ui;
    RegistrationWindow *registration_window;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
};

#endif // LOGINWINDOW_H
