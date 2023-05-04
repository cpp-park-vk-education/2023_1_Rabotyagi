#include "peermanager.h"
#include "connection.h"
#include "client.h"
#include <QtNetwork>

const qint32 BROADCAST_INTERVAL = 2000;
const unsigned int BROADCAST_PORT = 45000;

PeerManager::PeerManager(Client* client)
    : QObject(client)
{
    this->client = client;

    static const char* EnvVariables[] = {"USERNAME", "USER", "USERDOMAIN",
                                        "HOSTNAME", "DOMAINNAME"};

    for (const char* varname: EnvVariables)
    {
        username = qEnvironmentVariable(varname);
        if (!username.isNull())
            break;
    }

    if (username.isEmpty())
        username = "Неизвестный пользователь";

    update_addresses();
    server_port = 0;

    udp_socket.bind(QHostAddress::Any, BROADCAST_PORT, QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);
    connect(&udp_socket, &QUdpSocket::readyRead, this, &PeerManager::send_broadcast_datagram);

    broadcast_timer.setInterval(BROADCAST_INTERVAL);
    connect(&broadcast_timer, &QTimer::timeout, this, &PeerManager::send_broadcast_datagram);
}

void PeerManager::SetServerPort(int port)
{
    server_port = port;
}

QString PeerManager::UserName() const
{
    return username;
}

void PeerManager::StartBroadcasting()
{
    broadcast_timer.start();
}

bool PeerManager::IsLocalHostAddress(const QHostAddress& address) const
{
    for (const QHostAddress& local_address: ip_addresses)
    {
        if (address.isEqual(local_address))
            return true;
    }

    return false;
}

void PeerManager::send_broadcast_datagram()
{
    QByteArray datagram;
    {
        QCborStreamWriter writer(&datagram);
        writer.startArray(2);
        writer.append(username);
        writer.append(server_port);
        writer.endArray();
    }

    bool valid_broadcast_addresses = true;
    for (const QHostAddress& address: std::as_const(broadcast_addresses))
    {
        if (udp_socket.writeDatagram(datagram, address, BROADCAST_PORT) == -1)
        {
            valid_broadcast_addresses = false;
        }
    }

    if (!valid_broadcast_addresses)
        update_addresses();
}

void PeerManager::read_broadcast_datagram()
{
    while (udp_socket.hasPendingDatagrams()) {
            QHostAddress senderIp;
            quint16 senderPort;
            QByteArray datagram;
            datagram.resize(udp_socket.pendingDatagramSize());
            if (udp_socket.readDatagram(datagram.data(), datagram.size(),
                                             &senderIp, &senderPort) == -1)
                continue;

            int sender_server_port;
            {
                QCborStreamReader reader(datagram);
                if (reader.lastError() != QCborError::NoError || !reader.isArray())
                    continue;
                if (!reader.isLengthKnown() || reader.length() != 2)
                    continue;

                reader.enterContainer();
                if (reader.lastError() != QCborError::NoError || !reader.isString())
                    continue;
                while (reader.readString().status == QCborStreamReader::Ok)
                {
                    ;
                }

                if (reader.lastError() != QCborError::NoError || !reader.isUnsignedInteger())
                    continue;
                sender_server_port = reader.toInteger();
            }

            if (IsLocalHostAddress(senderIp) && sender_server_port == server_port)
                continue;

            if (!client->HasConnection(senderIp)) {
                Connection *connection = new Connection(this);
                emit new_connection(connection);
                connection->connectToHost(senderIp, sender_server_port);
            }
        }
}

void PeerManager::update_addresses()
{
    broadcast_addresses.clear();
    ip_addresses.clear();
    const QList<QNetworkInterface> interfaces = QNetworkInterface::allInterfaces();
    for (const QNetworkInterface& interface: interfaces)
    {
        const QList<QNetworkAddressEntry> entries = interface.addressEntries();
        for (const QNetworkAddressEntry &entry : entries)
        {
            QHostAddress broadcast_address = entry.broadcast();
            if (broadcast_address != QHostAddress::Null && entry.ip() != QHostAddress::LocalHost)
            {
                broadcast_addresses << broadcast_address;
                ip_addresses << entry.ip();
            }
        }
    }
}
