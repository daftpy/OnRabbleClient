#include "privatechatmessagepayload.h"

/*!
    \class PrivateChatMessagePayload
    \inmodule OnRabbleClient
    \brief Represents a single private message exchanged between two users.
*/

/*!
    \fn PrivateChatMessagePayload::PrivateChatMessagePayload(const QJsonObject &json)
    \brief Constructs a PrivateChatMessagePayload from \a json object.
*/
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

/*!
    \fn int PrivateChatMessagePayload::id() const
    \brief Returns the unique message ID.
*/
int PrivateChatMessagePayload::id() const
{
    return m_id;
}

/*!
    \fn void PrivateChatMessagePayload::setId(int id)
    \brief Sets the message ID to \a id.

    \a id is a unique message ID
*/
void PrivateChatMessagePayload::setId(int id)
{
    m_id = id;
}

/*!
    \fn QString PrivateChatMessagePayload::ownerId() const
    \brief Returns the sender's user ID.
*/
QString PrivateChatMessagePayload::ownerId() const
{
    return m_ownerId;
}

/*!
    \fn void PrivateChatMessagePayload::setOwnerId(const QString &id)
    \brief Sets the sender's user ID to \a id.

    The \a id is the senders unique user ID
*/
void PrivateChatMessagePayload::setOwnerId(const QString &id)
{
    m_ownerId = id;
}

/*!
    \fn QString PrivateChatMessagePayload::username() const
    \brief Returns the sender's display name.
*/
QString PrivateChatMessagePayload::username() const
{
    return m_username;
}

/*!
    \fn void PrivateChatMessagePayload::setUsername(const QString &username)
    \brief Sets the sender's display name to \a username.

    \a username is the sender's username
*/
void PrivateChatMessagePayload::setUsername(const QString &username)
{
    m_username = username;
}

/*!
    \fn QString PrivateChatMessagePayload::recipientId() const
    \brief Returns the recipient's user ID.
*/
QString PrivateChatMessagePayload::recipientId() const
{
    return m_recipientId;
}

/*!
    \fn void PrivateChatMessagePayload::setRecipientId(const QString &recipientId)
    \brief Sets the recipient's user ID to \a recipientId.

    \a recipientId is the recipients unique user ID
*/
void PrivateChatMessagePayload::setRecipientId(const QString &recipientId)
{
    m_recipientId = recipientId;
}

/*!
    \fn QString PrivateChatMessagePayload::recipient() const
    \brief Returns the recipient's display name.
*/
QString PrivateChatMessagePayload::recipient() const
{
    return m_recipient;
}

/*!
    \fn void PrivateChatMessagePayload::setRecipient(const QString &recipient)
    \brief Sets the recipient's display name to \a recipient.

    \a recipient is the recipient's username
*/
void PrivateChatMessagePayload::setRecipient(const QString &recipient)
{
    m_recipient = recipient;
}

/*!
    \fn QString PrivateChatMessagePayload::message() const
    \brief Returns the body of the private message.
*/
QString PrivateChatMessagePayload::message() const
{
    return m_message;
}

/*!
    \fn void PrivateChatMessagePayload::setMessage(const QString &message)
    \brief Sets the message body to \a message.

    \a message is the text content of the private message
*/
void PrivateChatMessagePayload::setMessage(const QString &message)
{
    m_message = message;
}

/*!
    \fn QDateTime PrivateChatMessagePayload::authoredAt() const
    \brief Returns the timestamp when the message was authored.
*/
QDateTime PrivateChatMessagePayload::authoredAt() const
{
    return m_authoredAt;
}

/*!
    \fn void PrivateChatMessagePayload::setAuthoredAt(const QDateTime &datetime)
    \brief Sets the authored timestamp to \a datetime.

    \a datetime is the time the private message was authored
*/
void PrivateChatMessagePayload::setAuthoredAt(const QDateTime &datetime)
{
    m_authoredAt = datetime;
}
