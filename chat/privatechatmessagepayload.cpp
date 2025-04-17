#include "privatechatmessagepayload.h"

PrivateChatMessagePayload::PrivateChatMessagePayload(const QJsonObject &json)
{
    m_id = json["id"].toInt(-1);
    m_ownerId = json["owner_id"].toString();
    m_username = json["username"].toString();
    m_recipientId = json["recipient_id"].toString();
    m_recipient = json["recipient"].toString();
    m_message = json["message"].toString();
    m_authoredAt = QDateTime::fromString(json["authored_at"].toString(), Qt::ISODate);
}

int PrivateChatMessagePayload::id() const
{
    return m_id;
}

void PrivateChatMessagePayload::setId(int id)
{
    m_id = id;
}

QString PrivateChatMessagePayload::ownerId() const
{
    return m_ownerId;
}

void PrivateChatMessagePayload::setOwnerId(const QString &id)
{
    m_ownerId = id;
}

QString PrivateChatMessagePayload::username() const
{
    return m_username;
}

void PrivateChatMessagePayload::setUsername(const QString &username)
{
    m_username = username;
}

QString PrivateChatMessagePayload::recipientId() const
{
    return m_recipientId;
}

void PrivateChatMessagePayload::setRecipientId(const QString &recipientId)
{
    m_recipientId = recipientId;
}

QString PrivateChatMessagePayload::recipient() const
{
    return m_recipient;
}

void PrivateChatMessagePayload::setRecipient(const QString &recipient)
{
    m_recipient = recipient;
}

QString PrivateChatMessagePayload::message() const
{
    return m_message;
}

void PrivateChatMessagePayload::setMessage(const QString &message)
{
    m_message = message;
}

QDateTime PrivateChatMessagePayload::authoredAt() const
{
    return m_authoredAt;
}

void PrivateChatMessagePayload::setAuthoredAt(const QDateTime &datetime)
{
    m_authoredAt = datetime;
}
