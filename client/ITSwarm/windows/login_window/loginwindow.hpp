#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>
#include "../../controls/user_control/user_control.h"
#include <QLineEdit>
#include <QCloseEvent>
#include <QKeyEvent>

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
        to_reg_window = 2,
        to_log_window = 3,
        exit = 4
    };

    explicit LoginWindow(int* flag, QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    //void login();
    //void openRegistrationWindow();
    void setFlagToRegistration();
    void on_loginButton_clicked();
    void closeEvent(QCloseEvent* event);
    void keyPressEvent(QKeyEvent *event);
public slots:
    //void saveTokens(const QString &accessToken, const QString &refreshToken);

private:
    Ui::LoginWindow *ui;
    int* _flag;
    UserControl* user_control;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
public:

};

#endif // LOGINWINDOW_H
