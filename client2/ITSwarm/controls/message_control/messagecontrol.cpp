#include "windows/content_widget/contentwindow.h"
#include "controls/message_control/messagecontrol.h"
#include "ui_contentwindow.h"
#include "controls/data_types/message/message.h"

MessageControl::MessageControl()
{

}

bool MessageControl::AppendMessage(ContentWindow* window, Message& message)
{
    if (message.GetName().isEmpty() || message.GetText().isEmpty())
        return false;

    QString text = message.GetName() + ": " + message.GetText();
    draw_text(window, text);
    return true;
}

bool MessageControl::draw_text(ContentWindow *window, QString &text)
{
    if (text.isEmpty())
        return false;
    window->ui->textBrowser->append(text);
    return true;
}
