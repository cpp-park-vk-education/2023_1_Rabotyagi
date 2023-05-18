#ifndef CHANNEL_H
#define CHANNEL_H

#include <QString>
#include <QTime>
#include <QString>
#include <QVector>

enum class ChannelType
{
    Message,
    Voice
};

class Channel
{
public:
    Channel(QString name, ChannelType type): name(name), channel_type(type)
    {
        created_at = QTime::currentTime();
        updated_at = created_at;
    }
    QString GetName() { return name; }
    ChannelType GetChannelType() { return channel_type; }
    QTime GetCreationTime() { return created_at; }
    QTime GetUpdatetime() { return updated_at; }
    QVector<QString> GetMessages() { return messages; }

private:
    int id;
    QString name;
    ChannelType channel_type;
    QTime created_at;
    QTime updated_at;
    QVector<QString> messages;

};

#endif // CHANNEL_H
