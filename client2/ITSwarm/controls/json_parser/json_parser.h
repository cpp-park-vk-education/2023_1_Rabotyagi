#include "message.h"
#include <string>
#include <QJsonObject>
#include <QJsonDocument>

using namespace UserMessage;

QString message_encode(Message& message);
QJsonObject message_decode(const QString& str);
Message json_to_message(QJsonObject& json);
