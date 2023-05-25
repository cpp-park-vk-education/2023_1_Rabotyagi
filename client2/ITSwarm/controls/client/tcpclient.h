#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "iclient.h"
#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <memory>
#include "request.h"


class TCPClient: public QObject
{
Q_OBJECT

public:
    TCPClient();

    bool ConnectToServer(QString address, qint16 port) ;
    bool Disconnect();
    Request_impl GeneratePostRequest(QString message);
    Request_impl GenerateGetRequest();
    bool SendRequest(const Request_impl request);
    QString GetMessage() { return message; }
    void ClearMessage() { message.clear(); }

private:
    std::shared_ptr<QTcpSocket> socket;
    QByteArray data;
    QString message;
    qint16 next_block_size;

public slots:
    void slotReadyRead();

signals:
    void newMessages();

};

#endif // TCPCLIENT_H
