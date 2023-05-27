#ifndef ICLIENT_H
#define ICLIENT_H

#include <QVector>
#include <QString>
#include <QObject>
#include <QJsonObject>
#include <QAbstractItemModel>

class IClient: public QObject
{

public:
    IClient();

    virtual bool ConnectToServer(QString address, qint16 port) = 0;
    virtual bool DisconnectFromServer() = 0;
    virtual bool Post(QString url, const QJsonObject& data, const QJsonObject& config) = 0;
    virtual bool Get(QString url, const QJsonObject& config) = 0;
    virtual QVector<QString> GetChannels(QString url, const QJsonObject& config) const = 0;
    virtual QVector<QString> GetUsers(QString url, const QJsonObject& config) const = 0;
    virtual bool JoinChannel(const QString channel) = 0;
    virtual bool LeaveChannel(const QString channel) = 0;

    virtual ~IClient();
};

#endif // ICLIENT_H
