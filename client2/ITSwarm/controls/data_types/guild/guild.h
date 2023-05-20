#ifndef GUILD_H
#define GUILD_H

#include <QTime>
#include <QString>
#include <QVector>
#include "controls/data_types/channel/channel.h"

class Guild
{
public:
    Guild(QString name);

private:
    unsigned int id;
    unsigned int owner_id;
    QString name;
    int user_count;
    QTime created_at;
    QVector<Channel> channels;
};

#endif // GUILD_H
