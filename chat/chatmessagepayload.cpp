#include "chatmessagepayload.h"

ChatMessagePayload::ChatMessagePayload(const QJsonObject &json)
{
    m_id = json["id"].toInt(-1);
    m_cacheId = json["cacheID"].toInt(-1);
    m_ownerId = json["owner_id"].toString();
    m_username = json["username"].toString();
    m_channel = json["channel"].toString();
    m_message = json["message"].toString();
    m_authoredAt = QDateTime::fromString(json["authored_at"].toString(), Qt::ISODate);
}

int ChatMessagePayload::id() const
{
    return m_id;
}

void ChatMessagePayload::setId(int id)
{
    m_id = id;
}

int ChatMessagePayload::cacheId() const
{
    return m_cacheId;
}

void ChatMessagePayload::setCacheId(int id)
{
    m_cacheId = id;
}

QString ChatMessagePayload::ownerId() const
{
    return m_ownerId;
}

void ChatMessagePayload::setOwnerId(const QString &id)
{
    m_ownerId = id;
}

QString ChatMessagePayload::username() const
{
    return m_username;
}

void ChatMessagePayload::setUsername(const QString &name)
{
    m_username = name;
}

QString ChatMessagePayload::channel() const
{
    return m_channel;
}

void ChatMessagePayload::setChannel(const QString &channel)
{
    m_channel = channel;
}

QString ChatMessagePayload::message() const
{
    return m_message;
}

void ChatMessagePayload::setMessage(const QString &message)
{
    m_message = message;
}

QDateTime ChatMessagePayload::authoredAt() const
{
    return m_authoredAt;
}

void ChatMessagePayload::setAuthoredAt(const QDateTime &datetime)
{
    m_authoredAt = datetime;
}
