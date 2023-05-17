#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QVector>

class Server: public QTcpServer
{
Q_OBJECT

public:
    Server();
    //std::shared_ptr<QTcpSocket> socket;
    QTcpSocket* socket;
private:
    //QVector<std::shared_ptr<QTcpSocket>> sockets;
    QVector<QTcpSocket*> sockets;
    QByteArray data;
    quint16 next_block_size;

    void SendToClient(QString message);

public slots:
    void incomingConnection(qintptr descriptor);
    void slotReadyRead();
};

#endif // SERVER_H
