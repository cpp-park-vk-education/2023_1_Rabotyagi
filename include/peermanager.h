#ifndef PEERMANAGER_H
#define PEERMANAGER_H

#include <QObject>
#include <QByteArray>
#include <QList>
#include <QObject>
#include <QTimer>
#include <QUdpSocket>

class Client;
class Connection;

class PeerManager : public QObject
{
    Q_OBJECT
public:
    PeerManager(Client* client);

    void SetServerPort(int port);
    QString UserName() const;
    void StartBroadcasting();
    bool IsLocalHostAddress(const QHostAddress &address) const;

signals:
    void new_connection(Connection* connection);

private slots:
    void send_broadcast_datagram();
    void read_broadcast_datagram();

private:
    void update_addresses();

    Client* client;
    QList<QHostAddress> broadcast_addresses;
    QList<QHostAddress> ip_addresses;
    QUdpSocket udp_socket;
    QTimer broadcast_timer;
    QString username;
    int server_port;
};

#endif // PEERMANAGER_H
