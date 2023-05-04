#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QAbstractSocket>
#include <QHostAddress>
#include "server.h"

class PeerManager;

class Client : public QObject
{
Q_OBJECT

public:
    explicit Client();

    void SendMessage(const QString &message);
    QString NickName() const;
    bool HasConnection(const QHostAddress &sender_ip, int sender_port = -1) const;

signals:
    void new_message(const QString& from, const QString& message);
    void new_client(const QString& nickname);
    void client_quit(const QString& nickname);

private slots:
    void new_connection(Connection* connection);
    void connection_error(QAbstractSocket::SocketError socket_error);
    void disconnected();
    void ready_for_use();

private:
    void delete_connection(Connection* connection);

    PeerManager* peer_manager;
    Server server;
    QMultiHash<QHostAddress, Connection* > peers;
};

#endif // CLIENT_H
