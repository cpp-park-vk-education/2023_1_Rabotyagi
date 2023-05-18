#include "channel.h"

Channel::Channel(QString name, ChannelType type): name(name), channel_type(type)
{
    created_at = QTime::currentTime();
    updated_at = created_at;
}
