#include "tcpclient.h"
#include <QtNetwork>
#include <QIODevice>
#include "request.h"

TCPClient::TCPClient()
{

}

bool TCPClient::ConnectToServer(QString url, qint16 port)
{
    socket = std::make_shared<QTcpSocket>();

    if (socket->state() == QAbstractSocket::UnconnectedState)
        socket->connectToHost(url, port);
    if(!socket->waitForConnected(1000))
    {
        qDebug() << "Can't connect to server";
        return false;
    }

    connect(socket.get(), &QTcpSocket::readyRead, this, &TCPClient::slotReadyRead);
    connect(socket.get(), &QTcpSocket::disconnected, this, &TCPClient::deleteLater);

    qDebug() << "Client successfully created: " << socket->socketDescriptor();
    return true;
}

Request_impl TCPClient::GeneratePostRequest(QString message)
{
    //Request_impl request();
    //request.message = message;
}

bool TCPClient::SendRequest(Request_impl request)
{
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);

    out << qint16(0) << QString::fromStdString(request.dump());
    out.device()->seek(0);
    out << qint16(data.size() - sizeof(qint16));
    socket->write(data);

    return true;
}



void TCPClient::slotReadyRead()
{
    QDataStream in(socket.get());

    if (in.status() == QDataStream::Ok)
    {
        while (true)
        {
            if (next_block_size == 0)
            {
                if (socket->bytesAvailable() < 2)
                    break;

                in >> next_block_size;
            }

            if (socket->bytesAvailable() < next_block_size)
            {
                break;
            }

            in >> message;
            next_block_size = 0;
        }
        emit newMessages();
    }
    else
    {
        message = "read error";
    }
}





