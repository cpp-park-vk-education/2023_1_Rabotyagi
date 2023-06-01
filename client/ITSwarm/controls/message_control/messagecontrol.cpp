#include "windows/content_widget/contentwindow.h"
#include "controls/message_control/messagecontrol.h"
#include "ui_contentwindow.h"
#include "data_types.hpp"
#include "QColor"

MessageControl::MessageControl()
{

}

bool MessageControl::AppendMessage(ContentWindow* window, QString message)
{
    //if (message.GetName().isEmpty() || message.GetText().isEmpty())
        //return false;

    //QString text = message.GetName() + ": " + message.GetText();
    window->ui->textBrowser->textColor();
    window->ui->textBrowser->setFontFamily("Inter");
    window->ui->textBrowser->setFontWeight(400);
    window->ui->textBrowser->setFontPointSize(16);
    draw_text(window, message);
    return true;
}

bool MessageControl::draw_text(ContentWindow* window, QString &text)
{
    if (text.isEmpty())
        return false;

    window->ui->textBrowser->append(text);
    return true;
}
