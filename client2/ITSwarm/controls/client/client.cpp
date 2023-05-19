#include "client.h"
#include <QIODevice>

Client::Client()
{
    socket = new QTcpSocket;
    socket->connectToHost("127.0.0.1", 8000);

    connect(socket, &QTcpSocket::readyRead, this, &Client::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &Client::deleteLater);

    next_block_size = 0;
    qDebug() << "Client successfully created: " << socket->socketDescriptor();

    std::srand(std::time(nullptr));
    SetName("User" + QString::number(std::rand() % 1000));
}

void Client::SendToServer(QString text)
{
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);

    out << qint16(0) << text;
    out.device()->seek(0);
    out << qint16(data.size() - sizeof(qint16));
    socket->write(data);
}

void Client::slotReadyRead()
{
    QDataStream in(socket);

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
