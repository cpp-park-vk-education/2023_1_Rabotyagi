#ifndef CHANNELCONTROL_H
#define CHANNELCONTROL_H

#include "controls/message_control/messagecontrol.h"
#include "windows/content_widget/contentwindow.h"
//#include "channel.h"
#include "data_types.hpp"
#include <memory>

class ChannelSidebar;

class ChannelControl
{
public:
    ChannelControl();

    bool SetActiveChannel(ChannelSidebar* channel_sidebar, std::shared_ptr<Channel> channel);
    bool CreateChannel();
    bool DeleteChannel();

////private:
    //std::shared_ptr<ContentWindow> content_window;

};

#endif // CHANNELCONTROL_H
