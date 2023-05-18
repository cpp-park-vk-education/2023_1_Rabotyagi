#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QDialog>
#include "main_window.h"
#include "user_control.h"

namespace Ui {
class RegistrationWindow;
}

class RegistrationWindow : public QDialog
{
    Q_OBJECT

public:
    explicit RegistrationWindow(int* flag, QWidget *parent = nullptr);
    ~RegistrationWindow();

signals:
    void goBack();

private slots:
    //void registerUser();
    void on_registerButton_clicked();
//    void on_registrationButton_clicked();
//    void on_goBackButton_clicked();

private:
    Ui::RegistrationWindow *ui;
    int* _flag;
    UserControl *user_control;
};

#endif // REGISTRATIONWINDOW_H
