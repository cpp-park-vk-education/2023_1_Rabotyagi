#include "contentwindow.h"
#include "controls/message_control/messagecontrol.h"
#include "ui_contentwindow.h"
#include <QString>
#include "json_parser.h"

ContentWindow::ContentWindow(std::shared_ptr<Client> client, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContentWindow),
    client(client)
{
    ui->setupUi(this);
    ui->searchButton->setIcon(QIcon(":/img/images/icons8-search-30.png"));
    ui->moreButton->setIcon(QIcon(":/img/images/icons8-more-24.png"));

    connect_to_message_control();

    connect(client.get(), &Client::newMessages, this, &ContentWindow::slotUpdateMessages);
}

void ContentWindow::ChangeActiveChannel(std::shared_ptr<Channel> channel)
{
    active_channel = channel;
    qDebug() << "ContentWindow: changed active_channel";
}

/*ContentWindow::ContentWindow(std::shared_ptr<TCPClient> client, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContentWindow),
    client(client)
{
    ui->setupUi(this);
    ui->searchButton->setIcon(QIcon(":/img/images/icons8-search-30.png"));
    ui->moreButton->setIcon(QIcon(":/img/images/icons8-more-24.png"));

    connect_to_message_control();

    connect(client.get(), &TCPClient::newMessages, this, &ContentWindow::slotUpdateMessages);
}*/

ContentWindow::~ContentWindow()
{
    delete ui;
}


void ContentWindow::on_pushButton_clicked()
{
    QString text = ui->lineEdit->text();
    if (text.isEmpty())
        return;
    Message msg(client->GetId(), text.toStdString());
    QString encoded_msg = message_encode(msg);
    client->SendToServer(encoded_msg);
    ui->lineEdit->clear();
}

//void ContentWindow::on_pushButton_clicked()
//{
//    QString text = ui->lineEdit->text();
//    if (text.isEmpty())
//        return;
//    Message msg(client->GetId(), text.toStdString());
//    QString encoded_msg = message_encode(msg);
//    client->SendToServer(encoded_msg);
//    ui->lineEdit->clear();
//}


void ContentWindow::on_lineEdit_returnPressed()
{
    on_pushButton_clicked();
}

void ContentWindow::slotUpdateMessages()
{
    message_control->AppendMessage(this, client->GetMessage());
    client->ClearMessage();
}

void ContentWindow::connect_to_message_control()
{
    message_control = std::make_shared<MessageControl>();
}


