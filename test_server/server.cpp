#include "server.h"

Server::Server()
{
    if (this->listen(QHostAddress::Any, 2323))
    {
        qDebug() << "start";
    }
    else
    {
        qDebug() << "error";
    }

    next_block_size = 0;
}

void Server::SendToClient(QString message)
{
    data.clear();
    QDataStream out(&data, QIODevice::WriteOnly);

    out << qint16(0) << message;
    out.device()->seek(0);
    out << qint16(data.size() - sizeof(qint16));

    for (auto s: sockets)
    {
        s->write(data);
    }
}

void Server::incomingConnection(qintptr descriptor)
{
    //socket = std::make_shared<QTcpSocket>();
    socket = new QTcpSocket;
    socket->setSocketDescriptor(descriptor);
    connect(socket, &QTcpSocket::readyRead, this, &Server::slotReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &Server::deleteLater);

    sockets.push_back(socket);
    qDebug() << "client connected: " << descriptor;

    for (auto s: sockets)
    {
        qDebug() << "Descriptor: " << s->socketDescriptor();
    }
}

void Server::slotReadyRead()
{
    //socket.reset((QTcpSocket*)sender());
    socket = (QTcpSocket*)sender();
    QDataStream in(socket);
    if (in.status() == QDataStream::Ok)
    {

        qDebug() << "read...";
        /*QString str;
        in >> str;
        qDebug() << str;

        SendToClient(str);*/
        while (true)
        {
            if (next_block_size == 0)
            {
                qDebug() << "next block size = 0" ;

                if (socket->bytesAvailable() < 2)
                {
                    qDebug() << "available < 2 bytes";
                    break;
                }
                in >> next_block_size;
                qDebug() << "next block size = " << next_block_size;
            }

            if (socket->bytesAvailable() < next_block_size)
            {
                qDebug() << "data is incomplete";
                break;
            }

            QString str;
            in >> str;
            qDebug() << str;
            next_block_size = 0;

            SendToClient(str);
        }
    }
    else
    {
        qDebug() << "read error";
    }
}
