#ifndef CHANNELCONTROL_H
#define CHANNELCONTROL_H

#include "messagecontrol.h"

class ChannelControl
{
public:
    ChannelControl();

    bool SetActiveChannel();
    bool CreateChannel();
    bool DeleteChannel();

private:
    std::shared_ptr<MessageControl> message_control;
};

#endif // CHANNELCONTROL_H
