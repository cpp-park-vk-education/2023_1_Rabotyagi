#include "main_window.h"
#include "loginwindow.hpp"
#include "reg_window.h"
//#include "client.h"
#include <QApplication>
#include <QtCore/QSettings>
#include <stdexcept>
#include <QFile>
#include "user_control.h"

int init_app_settings() {
    QSettings settings("ITSwarm.ini", QSettings::IniFormat);
    auto username = settings.value("username").toString();
    auto password = settings.value("password").toString();
    if (username != "" && password != ""){
        auto control = UserControl();
        int result = control.login(username, password);
        return result;
    }
    return 1;
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/style.css");
    file.open(QFile::ReadOnly);
    a.setStyleSheet(file.readAll());

    UserManager::getInstance();

    int result = init_app_settings();

    int flag = 3;

    if (result == 0)
        flag = -1;


    std::unique_ptr<LoginWindow> login = std::make_unique<LoginWindow>(&flag);
    std::unique_ptr<RegistrationWindow> reg = std::make_unique<RegistrationWindow>(&flag);
    std::unique_ptr<MainWindow> main = std::make_unique<MainWindow>(&flag);

    while (flag != -1){
        if (flag == 1)
        {
            main->show();
            break;
        }
        switch (flag) {
            case (int)LoginWindow::States::to_log_window:
                login->show();
                break;
            case (int)LoginWindow::States::to_reg_window:
                reg->show();
                break;
            case (int)LoginWindow::States::error:
                throw std::runtime_error("Ппц");
                break;
            case (int)LoginWindow::States::exit:
                exit(0);
                break;
        }
        QCoreApplication::processEvents();
    }

    main->show();
    return a.exec();
}
