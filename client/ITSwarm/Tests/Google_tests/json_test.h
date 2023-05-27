#ifndef JSON_TEST_H
#define JSON_TEST_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "json_parser.h"
#include "message.h"
#include <QString>
using namespace testing;

TEST(PrepareTests, SimpleTest)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}

TEST(MessageTests, Constructor)
{
    std::string correct_content = "test message";
    unsigned int correct_owner_id = 1;
    UserMessage::Message message(1, "test message");
    EXPECT_EQ(message.owner_id, correct_owner_id);
    EXPECT_EQ(message.content, correct_content);
}

TEST(MessageTests, MultipleMessage)
{
    std::string correct_content = "test message\nin two lines";
    unsigned int correct_owner_id = 1;
    UserMessage::Message message(1, "test message\nin two lines");
    EXPECT_EQ(message.owner_id, correct_owner_id);
    EXPECT_EQ(message.content, correct_content);
}

TEST(MessageTests, MaxOwnerId)
{
    std::string correct_content = "";
    unsigned int correct_owner_id = UINT_MAX;
    UserMessage::Message message(UINT_MAX, "");
    EXPECT_EQ(message.owner_id, correct_owner_id);
    EXPECT_EQ(message.content, correct_content);
}


TEST(EncodeTests, EmptyMessage)
{
    UserMessage::Message message;
    message.created_at = "00:00:00";
    message.updated_at = message.created_at;
    QString correct_string = "{\"id\" : 0, \"owner_id\" : 0, \"channel_id\" : 0, \
\"content\" : \"\", \"created_at\" : \"00:00:00\", \"updated_at\" : \"00:00:00\"}";
    QString encoded_message = message_encode(message);
    EXPECT_EQ(encoded_message, correct_string);
}

TEST(EncodeTests, SimpleMessage)
{
    UserMessage::Message message(256, "test message");
    message.created_at = "00:00:00";
    message.updated_at = message.created_at;
    QString correct_string = "{\"id\" : 0, \"owner_id\" : 256, \"channel_id\" : 0, \
\"content\" : \"test message\", \"created_at\" : \"00:00:00\", \"updated_at\" : \"00:00:00\"}";
    QString encoded_message = message_encode(message);
    EXPECT_EQ(encoded_message, correct_string);
}

TEST(EncodeTests, MultipleMessage)
{
    UserMessage::Message message(256, "test message.\nSecond line\n\t.Third line.\n");
    message.created_at = "00:00:00";
    message.updated_at = message.created_at;
    QString correct_string = "{\"id\" : 0, \"owner_id\" : 256, \"channel_id\" : 0, \
\"content\" : \"test message.\nSecond line\n\t.Third line.\n\", \"created_at\" : \"00:00:00\", \"updated_at\" : \"00:00:00\"}";
    QString encoded_message = message_encode(message);
    EXPECT_EQ(encoded_message, correct_string);
}

TEST(DecodeTests, EmptyMessage)
{
    UserMessage::Message message;
    message.created_at = "00:00:00";
    message.updated_at = message.created_at;
    QString encoded_message = message_encode(message);
    QJsonObject decoded_json = message_decode(encoded_message);
    EXPECT_EQ(decoded_json["id"], 0);
    EXPECT_EQ(decoded_json["owner_id"], 0);
    EXPECT_EQ(decoded_json["channel_id"], 0);
    EXPECT_EQ(decoded_json["content"], "");
    EXPECT_EQ(decoded_json["created_at"], "00:00:00");
    EXPECT_EQ(decoded_json["updated_at"], "00:00:00");
}

TEST(DecodeTests, SimpleMessage)
{
    UserMessage::Message message(256, "test message");
    message.created_at = "00:00:00";
    message.updated_at = message.created_at;
    QString encoded_message = message_encode(message);
    QJsonObject decoded_json = message_decode(encoded_message);
    EXPECT_EQ(decoded_json["id"], 0);
    EXPECT_EQ(decoded_json["owner_id"], 256);
    EXPECT_EQ(decoded_json["channel_id"], 0);
    EXPECT_EQ(decoded_json["content"], "test message");
    EXPECT_EQ(decoded_json["created_at"], "00:00:00");
    EXPECT_EQ(decoded_json["updated_at"], "00:00:00");
}

TEST(DecodeTests, MultipleMessage)
{
    UserMessage::Message message(256, "test message.\nSecond line\n\t.Third line.\n");
    message.created_at = "00:00:00";
    message.updated_at = message.created_at;
    QString encoded_message = message_encode(message);
    QJsonObject decoded_json = message_decode(encoded_message);
    EXPECT_EQ(decoded_json["id"], 0);
    EXPECT_EQ(decoded_json["owner_id"], 256);
    EXPECT_EQ(decoded_json["channel_id"], 0);
    EXPECT_EQ(decoded_json["content"], "test message.\nSecond line\n\t.Third line.\n");
    EXPECT_EQ(decoded_json["created_at"], "00:00:00");
    EXPECT_EQ(decoded_json["updated_at"], "00:00:00");
}

TEST(JsonToMessage, emptyMessage)
{
    QJsonObject json;
    json.insert("id", QJsonValue::fromVariant(0));
    json.insert("owner_id", QJsonValue::fromVariant(0));
    json.insert("channel_id", QJsonValue::fromVariant(0));
    json.insert("content", QJsonValue::fromVariant(""));
    json.insert("created_at", QJsonValue::fromVariant("00:00:00"));
    json.insert("updated_at", QJsonValue::fromVariant("00:00:00"));
    UserMessage::Message message = json_to_message(json);
    EXPECT_EQ(message.id, 0);
    EXPECT_EQ(message.owner_id, 0);
    EXPECT_EQ(message.channel_id, 0);
    EXPECT_EQ(message.content, "");
    EXPECT_EQ(message.created_at, "00:00:00");
    EXPECT_EQ(message.updated_at, "00:00:00");
}

TEST(JsonToMessage, SimpleMessage)
{
    QJsonObject json;
    json.insert("id", QJsonValue::fromVariant(0));
    json.insert("owner_id", QJsonValue::fromVariant(256));
    json.insert("channel_id", QJsonValue::fromVariant(0));
    json.insert("content", QJsonValue::fromVariant("test message"));
    json.insert("created_at", QJsonValue::fromVariant("00:00:00"));
    json.insert("updated_at", QJsonValue::fromVariant("00:00:00"));
    UserMessage::Message message = json_to_message(json);
    EXPECT_EQ(message.id, 0);
    EXPECT_EQ(message.owner_id, 256);
    EXPECT_EQ(message.channel_id, 0);
    EXPECT_EQ(message.content, "test message");
    EXPECT_EQ(message.created_at, "00:00:00");
    EXPECT_EQ(message.updated_at, "00:00:00");
}

TEST(JsonToMessage, MultipleMessage)
{
    QJsonObject json;
    json.insert("id", QJsonValue::fromVariant(0));
    json.insert("owner_id", QJsonValue::fromVariant(256));
    json.insert("channel_id", QJsonValue::fromVariant(0));
    json.insert("content", QJsonValue::fromVariant("test message.\nSecond line\n\t.Third line.\n"));
    json.insert("created_at", QJsonValue::fromVariant("00:00:00"));
    json.insert("updated_at", QJsonValue::fromVariant("00:00:00"));
    UserMessage::Message message = json_to_message(json);
    EXPECT_EQ(message.id, 0);
    EXPECT_EQ(message.owner_id, 256);
    EXPECT_EQ(message.channel_id, 0);
    EXPECT_EQ(message.content, "test message.\nSecond line\n\t.Third line.\n");
    EXPECT_EQ(message.created_at, "00:00:00");
    EXPECT_EQ(message.updated_at, "00:00:00");
}
#endif // JSON_TEST_H
