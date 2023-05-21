#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QTime>

namespace UserMessage{

enum class MessageType{
    Simple,
    NewParticipant,
    ParticipantLeave
};

struct Message
{
    Message();
    Message(unsigned int owner_id, std::string text, MessageType type = MessageType::Simple);
    //MessageType message_type=
    unsigned int id=0;
    unsigned int owner_id=0;
    unsigned int channel_id=0;
    std::string content="";
    std::string created_at="";
    std::string updated_at="";
};

}

#endif // MESSAGE_H
