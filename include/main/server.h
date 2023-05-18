#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>

class Connection;

class Server : public QTcpServer
{
Q_OBJECT

public:
    explicit Server(QObject *parent = nullptr);

signals:
    void new_connection(Connection* connection);

protected:
    void incomingConnection(qintptr socket_descriptor) override;
};

#endif // SERVER_H
