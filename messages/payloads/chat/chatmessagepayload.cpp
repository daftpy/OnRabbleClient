#include "chatmessagepayload.h"

/*!
    \class ChatMessagePayload
    \inmodule OnRabbleClient
    \brief Represents a single public chat message within the system.

    ChatMessagePayload encapsulates the properties of a chat message, including sender info,
    channel name, message body, and timestamp. It can be initialized from a QJsonObject and is
    exposed to QML via Q_GADGET and QML_VALUE_TYPE.
*/

/*!
    \fn ChatMessagePayload::ChatMessagePayload(const QJsonObject &json)
    \brief Constructs a ChatMessagePayload from a \a json object.
*/
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

/*!
    \property ChatMessagePayload::id
    \brief Returns the server-assigned unique ID for the message.
*/
int ChatMessagePayload::id() const
{
    return m_id;
}

/*!
    \fn void ChatMessagePayload::setId(int id)
    \brief Sets the unique message ID to \a id.

    \a id is the messages unique id
*/
void ChatMessagePayload::setId(int id)
{
    m_id = id;
}

/*!
    \property ChatMessagePayload::cacheId
    \brief Returns the optional client-side cache ID.
*/
int ChatMessagePayload::cacheId() const
{
    return m_cacheId;
}

/*!
    \fn void ChatMessagePayload::setCacheId(int id)
    \brief Sets the cache ID to \a id.

    \a id is the message's unique cache id
*/
void ChatMessagePayload::setCacheId(int id)
{
    m_cacheId = id;
}

/*!
    \property ChatMessagePayload::ownerId
    \brief Returns the user ID of the message sender.
*/
QString ChatMessagePayload::ownerId() const
{
    return m_ownerId;
}

/*!
    \fn void ChatMessagePayload::setOwnerId(const QString &id)
    \brief Sets the sender's user ID to \a id.

    \a id is the sender's unique user id
*/
void ChatMessagePayload::setOwnerId(const QString &id)
{
    m_ownerId = id;
}

/*!
    \property ChatMessagePayload::username
    \brief Returns the sender's username name.
*/
QString ChatMessagePayload::username() const
{
    return m_username;
}

/*!
    \fn void ChatMessagePayload::setUsername(const QString &name)
    \brief Sets the sender's display name to \a name.

    \a name is the senders username
*/
void ChatMessagePayload::setUsername(const QString &name)
{
    m_username = name;
}

/*!
    \property ChatMessagePayload::channel
    \brief Returns the name of the channel this message was posted in.
*/
QString ChatMessagePayload::channel() const
{
    return m_channel;
}

/*!
    \fn void ChatMessagePayload::setChannel(const QString &channel)
    \brief Sets the message's channel to \a channel.

    \a channel is the channel's name
*/
void ChatMessagePayload::setChannel(const QString &channel)
{
    m_channel = channel;
}

/*!
    \property ChatMessagePayload::message
    \brief Returns the body text of the chat message.
*/
QString ChatMessagePayload::message() const
{
    return m_message;
}

/*!
    \fn void ChatMessagePayload::setMessage(const QString &message)
    \brief Sets the message body text to \a message.

    \a message is the string of text that represents the message content
*/
void ChatMessagePayload::setMessage(const QString &message)
{
    m_message = message;
}

/*!
    \property ChatMessagePayload::authoredAt
    \brief Returns the timestamp when the message was authored.
*/
QDateTime ChatMessagePayload::authoredAt() const
{
    return m_authoredAt;
}

/*!
    \fn void ChatMessagePayload::setAuthoredAt(const QDateTime &datetime)
    \brief Sets the authored timestamp to \a datetime.

    \a datetime is the time the message was authored
*/
void ChatMessagePayload::setAuthoredAt(const QDateTime &datetime)
{
    m_authoredAt = datetime;
}
