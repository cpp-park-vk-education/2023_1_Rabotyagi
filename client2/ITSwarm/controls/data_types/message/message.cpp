#include "message.h"
#include "QTime"

UserMessage::Message::Message()
{

}

UserMessage::Message::Message(unsigned int owner_id, std::string text): owner_id(owner_id), content(text)
{
    created_at = QTime::currentTime().toString().toStdString();
    updated_at = created_at;
}
