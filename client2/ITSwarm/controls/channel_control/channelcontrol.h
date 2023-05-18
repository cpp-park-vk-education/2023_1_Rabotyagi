#ifndef CHANNELCONTROL_H
#define CHANNELCONTROL_H

#include "controls/message_control/messagecontrol.h"
#include "windows/content_widget/contentwindow.h"

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
