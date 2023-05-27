#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QDialog>
#include "../../controls/user_control/user_control.h"
#include "QKeyEvent"

namespace Ui {
class RegistrationWindow;
}

class RegistrationWindow : public QDialog
{
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
    explicit RegistrationWindow(int* flag, QWidget *parent = nullptr);
    ~RegistrationWindow();

signals:
    void goBack();

private slots:
    //void registerUser();
    void on_registerButton_clicked();
    void setFlagToLogin();
    void closeEvent(QCloseEvent* event);
    void keyPressEvent(QKeyEvent *event);
//    void on_goBackButton_clicked();
//    void on_registrationButton_clicked();
//    void on_goBackButton_clicked();
    bool passwordCheck(const QString& pass);
    bool regDataCorrect(const QString& username, const QString& email, const QString& pass, const QString& confirm_pass);

private:
    Ui::RegistrationWindow *ui;
    int* _flag;
    UserControl *user_control;
};

#endif // REGISTRATIONWINDOW_H
