#ifndef CONTENTWINDOW_H
#define CONTENTWINDOW_H

#include "tcpclient.h"
#include <QWidget>
#include "controls/message_control/messagecontrol.h"
#include "controls/data_types/channel/channel.h"

namespace Ui {
class ContentWindow;
}

class ContentWindow : public QWidget
{
    Q_OBJECT

public:
    //explicit ContentWindow(std::shared_ptr<Client> client = nullptr, QWidget *parent = nullptr);
    explicit ContentWindow(std::shared_ptr<TCPClient> client = nullptr, QWidget *parent = nullptr);
    Ui::ContentWindow *ui;
    ~ContentWindow();

public slots:
    //void new_client(const QString& nickname);
    //void client_quit(const QString& nickname);
    //void append_message(const QString& text);
    void on_pushButton_clicked();
    void on_lineEdit_returnPressed();
    void slotUpdateMessages();


private:
    void connect_to_message_control();

    //std::shared_ptr<Client> client;
    std::shared_ptr<TCPClient> client;

    std::shared_ptr<MessageControl> message_control;
    std::shared_ptr<Channel> active_channel;
};

#endif // CONTENTWINDOW_H
