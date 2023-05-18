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
    int flag = 3;
    std::unique_ptr<LoginWindow> login = std::make_unique<LoginWindow>(&flag);
    std::unique_ptr<RegistrationWindow> reg = std::make_unique<RegistrationWindow>(&flag);
    std::unique_ptr<MainWindow> main = std::make_unique<MainWindow>(&flag);

    //login->show();
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
            /*case (int)LoginWindow::States::to_main_window:
                qDebug() << "Open mainwindow";
                main->show();
                break;*/
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
    return a.exec();
}
