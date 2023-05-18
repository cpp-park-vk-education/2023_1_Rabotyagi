#ifndef CHANNELCONTROL_H
#define CHANNELCONTROL_H

#include "messagecontrol.h"
#include "contentwindow.h"

class ChannelControl
{
public:
    ChannelControl();

    bool SetActiveChannel();
    bool CreateChannel();
    bool DeleteChannel();

private:
    std::shared_ptr<ContentWindow> content_window;
};

#endif // CHANNELCONTROL_H
