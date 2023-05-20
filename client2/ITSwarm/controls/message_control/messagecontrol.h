#ifndef MESSAGECONTROL_H
#define MESSAGECONTROL_H

#include "controls/data_types/message/message.h"

class ContentWindow;

class MessageControl
{
public:
    MessageControl();

    bool AppendMessage(ContentWindow* window, Message& message);

private:
    bool draw_text(ContentWindow* window, QString& text);
};

#endif // MESSAGECONTROL_H
