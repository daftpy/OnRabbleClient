#include "privatemessagepayload.h"

/*!
    \class PrivateMessagePayload
    \inmodule OnRabbleClient
    \brief Represents a single private message exchanged between two users.
*/

/*!
    \fn PrivateMessagePayload::PrivateMessagePayload(const QJsonObject &json)
    \brief Constructs a PrivateMessagePayload from \a json object.
*/
PrivateMessagePayload::PrivateMessagePayload(const QJsonObject &json)
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
    \property PrivateMessagePayload::id
    \brief Returns the unique message ID.
*/
int PrivateMessagePayload::id() const
{
    return m_id;
}

/*!
    \fn void PrivateMessagePayload::setId(int id)
    \brief Sets the message ID to \a id.

    \a id is a unique message ID
*/
void PrivateMessagePayload::setId(int id)
{
    m_id = id;
}

/*!
    \property PrivateMessagePayload::ownerId
    \brief Returns the sender's user ID.
*/
QString PrivateMessagePayload::ownerId() const
{
    return m_ownerId;
}

/*!
    \fn void PrivateMessagePayload::setOwnerId(const QString &id)
    \brief Sets the sender's user ID to \a id.

    The \a id is the senders unique user ID
*/
void PrivateMessagePayload::setOwnerId(const QString &id)
{
    m_ownerId = id;
}

/*!
    \property PrivateMessagePayload::username
    \brief Returns the sender's display name.
*/
QString PrivateMessagePayload::username() const
{
    return m_username;
}

/*!
    \fn void PrivateMessagePayload::setUsername(const QString &username)
    \brief Sets the sender's display name to \a username.

    \a username is the sender's username
*/
void PrivateMessagePayload::setUsername(const QString &username)
{
    m_username = username;
}

/*!
    \property PrivateMessagePayload::recipientId
    \brief Returns the recipient's user ID.
*/
QString PrivateMessagePayload::recipientId() const
{
    return m_recipientId;
}

/*!
    \fn void PrivateMessagePayload::setRecipientId(const QString &recipientId)
    \brief Sets the recipient's user ID to \a recipientId.

    \a recipientId is the recipients unique user ID
*/
void PrivateMessagePayload::setRecipientId(const QString &recipientId)
{
    m_recipientId = recipientId;
}

/*!
    \property PrivateMessagePayload::recipient
    \brief Returns the recipient's display name.
*/
QString PrivateMessagePayload::recipient() const
{
    return m_recipient;
}

/*!
    \fn void PrivateMessagePayload::setRecipient(const QString &recipient)
    \brief Sets the recipient's display name to \a recipient.

    \a recipient is the recipient's username
*/
void PrivateMessagePayload::setRecipient(const QString &recipient)
{
    m_recipient = recipient;
}

/*!
    \property PrivateMessagePayload::message
    \brief Returns the body of the private message.
*/
QString PrivateMessagePayload::message() const
{
    return m_message;
}

/*!
    \fn void PrivateMessagePayload::setMessage(const QString &message)
    \brief Sets the message body to \a message.

    \a message is the text content of the private message
*/
void PrivateMessagePayload::setMessage(const QString &message)
{
    m_message = message;
}

/*!
    \property PrivateMessagePayload::authoredAt
    \brief Returns the timestamp when the message was authored.
*/
QDateTime PrivateMessagePayload::authoredAt() const
{
    return m_authoredAt;
}

/*!
    \fn void PrivateMessagePayload::setAuthoredAt(const QDateTime &datetime)
    \brief Sets the authored timestamp to \a datetime.

    \a datetime is the time the private message was authored
*/
void PrivateMessagePayload::setAuthoredAt(const QDateTime &datetime)
{
    m_authoredAt = datetime;
}
