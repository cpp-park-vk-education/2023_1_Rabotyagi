#ifndef MESSAGECONTROL_H
#define MESSAGECONTROL_H

#include "data_types.hpp"
#include <QString>

class ContentWindow;

class MessageControl
{
public:
    MessageControl();

    bool AppendMessage(ContentWindow* window, QString message);

private:
    bool draw_text(ContentWindow* window, QString& text);
};

#endif // MESSAGECONTROL_H
