#include "contentwindow.h"
#include "controls/message_control/messagecontrol.h"
#include "ui_contentwindow.h"
#include <QString>
#include "json.hpp"
#include <cpr/cpr.h>
#include <iostream>
#include <QMessageBox>
#include "user_control.h"

using json = nlohmann::json;

/*ContentWindow::ContentWindow(std::shared_ptr<Client> client, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContentWindow),
    client(client)
{
    ui->setupUi(this);
    ui->searchButton->setIcon(QIcon(":/img/images/icons8-search-30.png"));
    ui->moreButton->setIcon(QIcon(":/img/images/icons8-more-24.png"));

    connect_to_message_control();

    connect(client.get(), &Client::newMessages, this, &ContentWindow::slotUpdateMessages);
}*/

void ContentWindow::ChangeActiveChannel(std::shared_ptr<Channel> channel)
{
    active_channel = channel;
    qDebug() << "ContentWindow: changed active_channel";
}

int ContentWindow::UpdateMessages(int channel_id)
{
    try
    {
        cpr::Response response = cpr::Get(
                    cpr::Url{"http://localhost:8000/api/v1/IChannel"},
                    cpr::Parameters{
                        {"guild_id", std::to_string(channel_id).c_str()}
                    });

        auto json_response = json::parse(response.text);

        if (response.status_code == 200){
            auto json_messages = json_response["messages"].get<json>();
            for (auto message = json_messages.begin(); message < json_messages.end(); ++message)
            {
                auto owner = (*message)["owner"].get<std::string>();
                auto content = (*message)["content"].get<std::string>();
                QString text = QString::fromStdString(owner) + ": " + QString::fromStdString(content);
                message_control->AppendMessage(this, text);
            }

        }
    }
    catch (const std::exception& e) {
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }

    return 0;
}

ContentWindow::ContentWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContentWindow)
//    client(client)
{
    ui->setupUi(this);
    ui->searchButton->setIcon(QIcon(":/img/images/icons8-search-30.png"));
    ui->moreButton->setIcon(QIcon(":/img/images/icons8-more-24.png"));

    connect_to_message_control();

//    connect(client.get(), &TCPClient::newMessages, this, &ContentWindow::slotUpdateMessages);
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
//    Request_impl request = client->GeneratePostRequest(text);
//    client->SendRequest(request);
    try {
        cpr::Response response = cpr::Post(
                    cpr::Url{"http://localhost:8000/api/v1/IMessage"},
                    cpr::Multipart{
                        {"content", text.toStdString().c_str()},
                        {"channel_id", UserManager::getInstance()->channel_id},
                        {"owner_id", UserManager::getInstance()->id}
                    });
        auto json_response = json::parse(response.text);

        if (response.status_code == 200){
            qDebug() << "message sended";
//            return 0;
        }
        else {
            QMessageBox::warning(nullptr, tr("Can't send message"), tr(json_response["message"].dump().c_str()));
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Request failed, error: " << e.what() << '\n';
    }
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
//    message_control->AppendMessage(this, client->GetMessage());
//    client->ClearMessage();
}

void ContentWindow::connect_to_message_control()
{
    message_control = std::make_shared<MessageControl>();
}


