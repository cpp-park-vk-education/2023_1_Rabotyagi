#include "server.h"
#include "connection.h"
#include <QtNetwork>


Server::Server(QObject *parent)
    : QTcpServer{parent}
{
    listen(QHostAddress::Any);
}

void Server::incomingConnection(qintptr socket_descriptor)
{
    Connection* connection = new Connection(socket_descriptor, this);
    emit new_connection(connection);
}
