#include "gitconnection.h"
#include "ui_gitconnection.h"
#include <QMessageBox>

GitConnection::GitConnection(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GitConnection)
{
    ui->setupUi(this);
    QDialog::setWindowTitle("Подключение к Git");
}

GitConnection::~GitConnection()
{
    delete ui;
}

bool GitConnection::authorization(QString login, QString password)
{
    return true;
}

void GitConnection::on_pushButton_clicked()
{
    QString login = ui->login->text();
    QString pass = ui->password->text();

    if (authorization(login, pass))
    {
        QMessageBox::information(this, "Git", "Успешное подключение.");
    }

    else
    {
        QMessageBox::information(this, "Git", "Подключение не выполнено. Пожалуйста, повторите попытку.");
    }
}

