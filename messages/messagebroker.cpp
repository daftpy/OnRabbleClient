#include "messagebroker.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

/*!
    \class MessageBroker
    \inmodule OnRabbleClient
    \brief Interprets and emits structured signals based on incoming JSON messages.

    The MessageBroker class handles inbound and outbound message processing for the chat system.
    It parses raw JSON messages from the server and emits strongly typed Qt signals
    which QML or C++ components can bind to.

    \section1 Internal Members

    The following private member variables and functions are used internally by MessageBroker and
    are referenced here for clarity. Full documentation is available in the source file:

    \b Private \b Functions
    \list
        \li \tt{handleChatMessage(\l{ChatMessagePayload})} – adds
            a chat message to the message model.
        \li \tt{handleBulkChatMessages(\l{QList}<\l{ChatMessagePayload}>)} – adds multiple
            chat messages to the message model.
        \li \tt{handlePrivateChatMessage(\l{PrivateChatMessagePayload})} – adds a private chat
            message to the private chat message model.
        \li \tt{handleBulkPrivateChatMessages(\l{QList}<\l{PrivateChatMessagePayload}>)} – adds
            multiple private chat message to the private chat message model.
    \endlist

    \sa QObject, QQmlEngine
*/

/*!
    \fn MessageBroker::MessageBroker(QObject *parent)
    \brief Constructs a new MessageBroker instance.

    \a parent is the optional parent QObject.
*/
MessageBroker::MessageBroker(QObject *parent)
    : QObject{parent}
{
    qDebug() << "MessageBroker: initialized";
}

/*!
    \fn void MessageBroker::processMessage(const QString &message)
    \brief Parses and dispatches a raw JSON message from the server.

    The message type is used to determine the appropriate internal handler or signal.

    \a message is the JSON string received from the WebSocket.
*/
void MessageBroker::processMessage(const QString &message)
{
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8(), &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "MessageBroker: Failed to parse message:" << parseError.errorString();
        return;
    }

    if (!doc.isObject()) {
        qWarning() << "MessageBroker: Invalid message format (expected object)";
        return;
    }

    const QJsonObject obj = doc.object();
    const QString type = obj.value("type").toString();

    if (type == "active_channels") {
        QJsonArray channelsJson = obj["payload"].toObject()["channels"].toArray();
        QList<ChannelPayload> parsed;
        for (const QJsonValue &value : channelsJson)
            parsed.append(ChannelPayload(value.toObject()));
        emit activeChannelsReceived(parsed);
        return;
    }

    if (type == "bulk_chat_messages") {
        QJsonArray msgArray = obj["payload"].toObject()["messages"].toArray();
        QList<ChatMessagePayload> parsed;
        for (const QJsonValue &value : msgArray)
            if (value.isObject())
                parsed.append(ChatMessagePayload(value.toObject()));
        handleBulkChatMessages(parsed);
        return;
    }

    if (type == "chat_message") {
        ChatMessagePayload chatMsg(obj["payload"].toObject());
        handleChatMessage(chatMsg);
        return;
    }

    if (type == "connected_users") {
        QJsonArray usersArray = obj["payload"].toObject()["users"].toArray();
        QList<UserStatusPayload> parsed;
        for (const QJsonValue &value : usersArray)
            if (value.isObject())
                parsed.append(UserStatusPayload(value.toObject()));
        emit connectedUsersReceived(parsed);
        return;
    }

    if (type == "private_chat_message") {
        PrivateChatMessagePayload privateMsg(obj["payload"].toObject());

        qDebug() << "Private Message:"
                 << "From:" << privateMsg.username() << "(" << privateMsg.ownerId() << ")"
                 << "To:" << privateMsg.recipient() << "(" << privateMsg.recipientId() << ")"
                 << "Message:" << privateMsg.message()
                 << "At:" << privateMsg.authoredAt().toString(Qt::ISODate);

        handlePrivateChatMessage(privateMsg);
        return;
    }

    if (type == "bulk_private_messages") {
        QJsonArray msgArray = obj["payload"].toObject()["messages"].toArray();
        QList<PrivateChatMessagePayload> parsed;
        for (const QJsonValue &value : msgArray)
            if (value.isObject())
                parsed.append(PrivateChatMessagePayload(value.toObject()));
        handleBulkPrivateMessages(parsed);
        return;
    }

    if (type == "user_status") {
        UserStatusPayload userStatusPayload(obj["payload"].toObject());

        qDebug() << "User status message:"
                 << "User:" << userStatusPayload.username()
                 << "Connected:" << userStatusPayload.isConnected();

        emit userStatusUpdated(userStatusPayload);
        return;
    }

    qDebug() << "MessageBroker: Unhandled message type:" << type;
}

/*!
    \fn ChatMessageModel& MessageBroker::messageModel()
    \brief Returns the unfiltered model of all public chat messages.
*/
ChatMessageModel& MessageBroker::messageModel()
{
    return m_messageModel;
}

/*!
    \fn PrivateChatMessageModel& MessageBroker::privateMessageModel()
    \brief Returns the unfiltered model of all private chat messages.
*/
PrivateChatMessageModel& MessageBroker::privateMessageModel()
{
    return m_privateMessageModel;
}

/*!
    \fn void MessageBroker::sendChatMessage(const QString &message)
    \brief Validates and serializes a public chat message.

    Emits \c outboundMessageReady if the payload is valid.

    \a message is a JSON string with keys "channel" and "message".
*/
void MessageBroker::sendChatMessage(const QString &message)
{
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8(), &parseError);

    if (parseError.error != QJsonParseError::NoError || !doc.isObject()) {
        qWarning() << "[MessageBroker] Invalid JSON payload:" << parseError.errorString();
        return;
    }

    QJsonObject obj = doc.object();
    const QString channel = obj.value("channel").toString().trimmed();
    const QString text = obj.value("message").toString().trimmed();

    if (channel.isEmpty() || text.isEmpty() || text.length() > 1000) {
        qWarning() << "[MessageBroker] Invalid chat message. Channel or message missing, or too long.";
        return;
    }

    QJsonObject root {
        { "type", "chat_message" },
        { "channel", channel },
        { "message", text }
    };

    const QString serialized = QString::fromUtf8(QJsonDocument(root).toJson(QJsonDocument::Compact));
    qDebug() << "[MessageBroker] Forwarding chat message:" << serialized;
    emit outboundMessageReady(serialized);
}

/*!
    \fn void MessageBroker::sendPrivateChatMessage(const QString &message)
    \brief Validates and serializes a private chat message.

    Emits \c outboundMessageReady if the payload is valid.

    \a message is a JSON string with keys "recipientId" and "message".
*/
void MessageBroker::sendPrivateChatMessage(const QString &message)
{
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8(), &parseError);

    if (parseError.error != QJsonParseError::NoError || !doc.isObject()) {
        qWarning() << "[MessageBroker] Invalid JSON payload:" << parseError.errorString();
        return;
    }

    QJsonObject obj = doc.object();
    const QString recipient = obj.value("recipientId").toString().trimmed();
    const QString text = obj.value("message").toString().trimmed();

    if (recipient.isEmpty() || text.isEmpty() || text.length() > 1000) {
        qWarning() << "[MessageBroker] Invalid private message. Recipient or message missing, or too long.";
        return;
    }

    QJsonObject root {
        { "type", "private_chat_message" },
        { "recipient_id", recipient },
        { "message", text }
    };

    const QString serialized = QString::fromUtf8(QJsonDocument(root).toJson(QJsonDocument::Compact));
    qDebug() << "[MessageBroker] Forwarding private message:" << serialized;
    emit outboundMessageReady(serialized);
}

/*!
    \fn void MessageBroker::handleChatMessage(const ChatMessagePayload &msg)
    \brief Appends a single public chat message to the model.

    \a msg is the deserialized chat message payload.
*/
void MessageBroker::handleChatMessage(const ChatMessagePayload &msg)
{
    m_messageModel.appendMessage(msg);
}

/*!
    \fn void MessageBroker::handlePrivateChatMessage(const PrivateChatMessagePayload &msg)
    \brief Appends a single private chat message to the model.

    \a msg is the deserialized private message payload.
*/
void MessageBroker::handlePrivateChatMessage(const PrivateChatMessagePayload &msg)
{
    qDebug() << "[MessageBroker] Appending private Message:"
             << "From:" << msg.username()
             << "(" << msg.ownerId() << ")"
             << "To:" << msg.recipient()
             << "(" << msg.recipientId() << ")"
             << "Message:" << msg.message()
             << "At:" << msg.authoredAt().toString(Qt::ISODate);
    m_privateMessageModel.appendMessage(msg);
}

/*!
    \fn void MessageBroker::handleBulkChatMessages(const QList<ChatMessagePayload> &messages)
    \brief Appends a batch of public chat messages to the model.

    \a messages List of deserialized chat messages.
*/
void MessageBroker::handleBulkChatMessages(const QList<ChatMessagePayload> &messages)
{
    for (const auto &msg : messages) {
        m_messageModel.appendMessage(msg);
    }
}

/*!
    \fn void MessageBroker::handleBulkPrivateMessages(const QList<PrivateChatMessagePayload> &messages)
    \brief Appends a batch of private chat messages to the model.

    \a messages List of deserialized private messages.
*/
void MessageBroker::handleBulkPrivateMessages(const QList<PrivateChatMessagePayload> &messages)
{
    qDebug() << "Bulk private messages received";
    for (const auto &msg : messages) {
        m_privateMessageModel.appendMessage(msg);
    }
}

/*---------------------------- Signals ----------------------------*/
/*!
    \fn void MessageBroker::activeChannelsReceived(const QList<ChannelPayload> &channels)
    \brief This signal is emitted when the server sends a list of active public channels.

    The \a channels list contains metadata for each public channel,
    used to populate models and configure proxies.
*/

/*!
    \fn void MessageBroker::connectedUsersReceived(QList<UserStatusPayload> users)
    \brief This signal is emitted when a list of currently connected users is received.

    \a users contains the user IDs and connection states at the time of receipt.
*/

/*!
    \fn void MessageBroker::userStatusUpdated(const UserStatusPayload &payload)
    \brief This signal is emitted when a single user's connection status changes.

    The \a payload includes the user’s ID, name, and updated connection state (online/offline).
*/

/*!
    \fn void MessageBroker::outboundMessageReady(const QString &message)
    \brief This signal is emitted when a validated and serialized message is ready to be sent to the server.

    The \a message is a compact JSON string to be passed directly to the WebSocket.
*/
