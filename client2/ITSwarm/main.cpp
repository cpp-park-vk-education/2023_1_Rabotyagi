#include "main_window.h"
#include "loginwindow.hpp"
#include "reg_window.h"
#include "client.h"
#include <QApplication>
#include <QtCore/QSettings>
#include <stdexcept>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int flag = 256;
    std::shared_ptr<Client> client = std::make_shared<Client>();
    std::unique_ptr<LoginWindow> login = std::make_unique<LoginWindow>(&flag);
    std::unique_ptr<RegistrationWindow> reg = std::make_unique<RegistrationWindow>(&flag);
    std::unique_ptr<MainWindow> main = std::make_unique<MainWindow>(&flag);

    login->show();
    while (flag != -1 && flag != 1){
        switch (flag) {
            case (int)LoginWindow::States::to_main_window:
                main->show();
                break;
            case (int)LoginWindow::States::to_reg_window:
                reg->show();
                break;
            case (int)LoginWindow::States::error:
                throw std::runtime_error("Ппц");
                break;
        }
    }
    return a.exec();
}
