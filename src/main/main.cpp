#include "mainwindow.h"
#include "client.h"
#include <QApplication>
#include <QtCore/QSettings>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    std::shared_ptr<Client> client = std::make_shared<Client>();
    //Client client;
    MainWindow w(client);
    w.show();
    return a.exec();
}
