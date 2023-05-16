#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>

class Message
{
public:
    Message();
    Message(QString username, QString text);
    QString GetName() { return username; }
    QString GetText() { return text; }

private:
    QString username;
    QString text;
};

#endif // MESSAGE_H
