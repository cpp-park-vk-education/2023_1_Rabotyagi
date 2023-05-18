#include "contentwindow.h"
#include "messagecontrol.h"
#include "ui_contentwindow.h"
#include <QString>

ContentWindow::ContentWindow(std::shared_ptr<Client> client, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContentWindow),
    client(client)
{
    ui->setupUi(this);
    ui->searchButton->setIcon(QIcon(":/img/images/icons8-search-30.png"));
    ui->moreButton->setIcon(QIcon(":/img/images/icons8-more-24.png"));

    connect_to_message_control();

    //client = std::make_shared<Client>();
    //client = new Client();

    //connect(client.get(), &Client::slotReadyRead, this, &ContentWindow::slotUpdateMessages);
    connect(client.get(), &Client::newMessages, this, &ContentWindow::slotUpdateMessages);
}

ContentWindow::~ContentWindow()
{
    delete ui;
}


void ContentWindow::on_pushButton_clicked()
{
    QString text = ui->lineEdit->text();
    if (text.isEmpty())
        return;

    QString nickname = client->GetName();
    //client->SendToServer(nickname + ": " + text);
    client->SendToServer(text);
    ui->lineEdit->clear();
}


void ContentWindow::on_lineEdit_returnPressed()
{
    on_pushButton_clicked();
}

void ContentWindow::slotUpdateMessages()
{
    Message message(client->GetName(), client->GetMessage());
    message_control->AppendMessage(this, message);
    client->ClearMessage();
}

void ContentWindow::connect_to_message_control()
{
    message_control = std::make_shared<MessageControl>();
}


