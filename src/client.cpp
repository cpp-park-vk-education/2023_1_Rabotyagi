#include <QtNetwork>
#include "client.h"
#include "connection.h"
#include "peermanager.h"

Client::Client()
{
    peer_manager = new PeerManager(this);
    peer_manager->SetServerPort(server.serverPort());
    peer_manager->StartBroadcasting();

    connect(peer_manager, &PeerManager::new_connection, this, &Client::new_connection);
    connect(&server, &Server::new_connection, this, &Client::new_connection);
}

void Client::SendMessage(const QString &message)
{
    if (message.isEmpty())
        return;

    for (Connection* connection: std::as_const(peers))
        connection->SendMessage(message);
}

QString Client::NickName() const
{
    return peer_manager->UserName() + "@" + QHostInfo::localHostName() + ":" + QString::number(server.serverPort());
}

bool Client::HasConnection(const QHostAddress &sender_ip, int sender_port) const
{
    if (sender_port == -1)
        return peers.contains(sender_ip);

    if (!peers.contains(sender_ip))
        return false;

    const QList<Connection*> connections = peers.values(sender_ip);
    for (const Connection* connection : connections) {
        if (connection->peerPort() == sender_port)
            return true;
    }

    return false;
}

void Client::new_connection(Connection* connection)
{
    connection->SetGreetingMessage(peer_manager->UserName());

    connect(connection, &Connection::errorOccurred, this, &Client::connection_error);
    connect(connection, &Connection::disconnected, this, &Client::disconnected);
    connect(connection, &Connection::ready_for_use, this, &Client::ready_for_use);
}

void Client::ready_for_use()
{
    Connection* connection = qobject_cast<Connection*>(sender());
    if (!connection || HasConnection(connection->peerAddress(), connection->peerPort()))
        return;

    connect(connection,  &Connection::new_message,
            this, &Client::new_message);

    peers.insert(connection->peerAddress(), connection);
    QString nickname = connection->Name();
    if (!nickname.isEmpty())
        emit new_client(nickname);
}

void Client::disconnected()
{
    if (Connection* connection = qobject_cast<Connection*>(sender()))
        delete_connection(connection);
}

void Client::connection_error(QAbstractSocket::SocketError socket_error)
{
    if (Connection *connection = qobject_cast<Connection*>(sender()))
        delete_connection(connection);
}

void Client::delete_connection(Connection* connection)
{
    if (peers.contains(connection->peerAddress())) {
        peers.remove(connection->peerAddress());
        QString nickname = connection->Name();
        if (!nickname.isEmpty())
            emit client_quit(nickname);
    }
    connection->deleteLater();
}
