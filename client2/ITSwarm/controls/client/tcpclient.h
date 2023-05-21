#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include "iclient.h"
#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <memory>

class TCPClient: public QObject
{
Q_OBJECT

public:
    TCPClient();

    bool ConnectToServer(QString address, qint16 port) ;
    bool Disconnect();
    //bool DisconnectFromServer()  {};
    bool Post(QString url, const QJsonObject& data, const QJsonObject& config) ;
    bool Get(QString url, const QJsonObject& config) ;
    QVector<QString> GetChannels(QString url, const QJsonObject& config) const ;
    QVector<QString> GetUsers(QString url, const QJsonObject& config) const ;
    //bool JoinChannel(const QString channel)  {};
    //bool LeaveChannel(const QString channel)  {};

    //~TCPClient();
private:
    std::shared_ptr<QTcpSocket> socket;
    //QTcpSocket* socket;

public slots:
    void slotReadyRead();

signals:
    void newMessages();

};

#endif // TCPCLIENT_H
