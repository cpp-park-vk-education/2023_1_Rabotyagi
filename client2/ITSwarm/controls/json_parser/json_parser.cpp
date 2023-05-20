#include "json_parser.h"

QString message_encode(Message& message)
{
    QString str = "{\"id\" : 0, \"owner_id\" : ";
    str += QString::number(message.owner_id) + ", \"channel_id\" : 0, " +
            "\"content\" : \"" + QString::fromStdString(message.content) + "\"" +
            ", \"created_at\" : \"" + QString::fromStdString(message.created_at) + "\"" +
            ", \"updated_at\" : \"" + QString::fromStdString(message.updated_at) + "\"}";

    return str;
}

QJsonObject message_decode(const QString& str)
{
    QJsonObject obj;
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());

    if (!doc.isNull())
    {
        if (doc.isObject())
        {
            obj = doc.object();
        }
        else
        {
            qDebug() << "Document is not an object";
        }
    }
    else
    {
        qDebug() << "Invalid JSON" << str;
    }
    return obj;
}

Message json_to_message(QJsonObject& json)
{
    Message msg;
    msg.id = json["id"].toInt();
    msg.owner_id = json["owner_id"].toInt();
    msg.channel_id = json["channel_id"].toInt();
    msg.content = (json["content"].toString()).toStdString();
    msg.created_at = (json["created_at"].toString()).toStdString();
    msg.updated_at = (json["updated_at"].toString()).toStdString();

    return msg;
}
