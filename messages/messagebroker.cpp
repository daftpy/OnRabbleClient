/*!
    \class MessageBroker
    \inmodule OnRabbleClient
    \brief Interprets and emits structured signals based on incoming JSON messages.

    The MessageBroker class handles inbound and outbound message processing for the chat system.
    It parses raw JSON messages from the server and emits strongly typed Qt signals
    which QML or C++ components can bind to.

    \sa QObject, QQmlEngine
*/
#include "messagebroker.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include "chat/privatechatmessagepayload.h"

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
    \brief Processes a raw JSON message from the server and emits the appropriate signal.

    This function parses the message type and dispatches the appropriate signal based on its contents.

    \a message is the JSON string received from the server.
*/
void MessageBroker::processMessage(const QString &message)
{
    // Parse the incoming JSON string
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

    // Handle different message types
    if (type == "active_channels") {
        qDebug() << "MessageBroker: received active channels!";
        QJsonArray channelsJson = obj["payload"].toObject()["channels"].toArray();
        QList<ChannelPayload> parsed;
        for (const QJsonValue &value : channelsJson)
            parsed.append(ChannelPayload(value.toObject()));
        emit activeChannelsReceived(parsed);
        return;
    }

    if (type == "bulk_chat_messages") {
        qDebug() << "MessageBroker: received bulk chat messages!";
        QJsonArray msgArray = obj["payload"].toObject()["messages"].toArray();
        QList<ChatMessagePayload> parsed;
        for (const QJsonValue &value : msgArray)
            if (value.isObject())
                parsed.append(ChatMessagePayload(value.toObject()));
        emit bulkChatMessagesReceived(parsed);
        return;
    }

    if (type == "chat_message") {
        qDebug() << "MessageBroker: received single chat message!";
        ChatMessagePayload chatMsg(obj["payload"].toObject());
        emit chatMessageReceived(chatMsg);
        return;
    }

    if (type == "connected_users") {
        qDebug() << "MessageBroker: received connected users!";
        QJsonArray usersArray = obj["payload"].toObject()["users"].toArray();
        QList<UserStatusPayload> parsed;
        for (const QJsonValue &value : usersArray)
            if (value.isObject())
                parsed.append(UserStatusPayload(value.toObject()));
        emit connectedUsersReceived(parsed);
        return;
    }

    if (type == "private_chat_message") {
        qDebug() << "MessageBroker: received private chat message!";
        PrivateChatMessagePayload privateMsg(obj["payload"].toObject());

        // Log detailed info about the private message
        qDebug() << "Private Message:"
                 << "From:" << privateMsg.username() << "(" << privateMsg.ownerId() << ")"
                 << "To:" << privateMsg.recipient() << "(" << privateMsg.recipientId() << ")"
                 << "Message:" << privateMsg.message()
                 << "At:" << privateMsg.authoredAt().toString(Qt::ISODate);

        emit privateChatMessageReceived(privateMsg);
        return;
    }

    if (type == "bulk_private_messages") {
        qDebug() << "MessageBroker: received bulk private messages!";
        QJsonArray msgArray = obj["payload"].toObject()["messages"].toArray();
        QList<PrivateChatMessagePayload> parsed;
        for (const QJsonValue &value : msgArray)
            if (value.isObject())
                parsed.append(PrivateChatMessagePayload(value.toObject()));
        emit bulkPrivateMessagesReceived(parsed);
        return;
    }

    if (type == "user_status") {
        qDebug() << "MessageBroker: received user status message!";
        UserStatusPayload userStatusPayload(obj["payload"].toObject());

        qDebug() << "User status message:"
                 << "User:" << userStatusPayload.username()
                 << "Connected:" << userStatusPayload.isConnected();

        emit userStatusUpdated(userStatusPayload);
        return;
    }

    // Unknown message type
    qDebug() << "MessageBroker: Unhandled message type:" << type;
}

/*!
    \fn void MessageBroker::sendChatMessage(const QString &message)
    \brief Validates and serializes a public chat message, then emits outboundMessageReady.

    \a message is the raw JSON input containing "channel" and "message".
*/
void MessageBroker::sendChatMessage(const QString &message)
{
    // Parse input JSON
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8(), &parseError);

    if (parseError.error != QJsonParseError::NoError || !doc.isObject()) {
        qWarning() << "[MessageBroker] Invalid JSON payload:" << parseError.errorString();
        return;
    }

    QJsonObject obj = doc.object();
    const QString channel = obj.value("channel").toString().trimmed();
    const QString text = obj.value("message").toString().trimmed();

    // Validate fields
    if (channel.isEmpty()) {
        qWarning() << "[MessageBroker] Missing or empty channel in payload.";
        return;
    }

    if (text.isEmpty()) {
        qWarning() << "[MessageBroker] Ignoring empty chat message.";
        return;
    }

    if (text.length() > 1000) {
        qWarning() << "[MessageBroker] Message too long. Rejecting.";
        return;
    }

    // Create outbound message
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
    \brief Validates and serializes a private chat message, then emits outboundMessageReady.

    \a message is the raw JSON input containing "recipientId" and "message".
*/
void MessageBroker::sendPrivateChatMessage(const QString &message)
{
    // Parse input JSON
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8(), &parseError);

    if (parseError.error != QJsonParseError::NoError || !doc.isObject()) {
        qWarning() << "[MessageBroker] Invalid JSON payload:" << parseError.errorString();
        return;
    }

    QJsonObject obj = doc.object();
    const QString recipient = obj.value("recipientId").toString().trimmed();
    const QString text = obj.value("message").toString().trimmed();

    // Validate fields
    if (recipient.isEmpty()) {
        qWarning() << "[MessageBroker] Missing recipientId in payload.";
        return;
    }

    if (text.isEmpty()) {
        qWarning() << "[MessageBroker] Ignoring empty private message.";
        return;
    }

    if (text.length() > 1000) {
        qWarning() << "[MessageBroker] Message too long. Rejecting.";
        return;
    }

    // Create outbound message
    QJsonObject root {
        { "type", "private_chat_message" },
        { "recipient_id", recipient },
        { "message", text }
    };

    const QString serialized = QString::fromUtf8(QJsonDocument(root).toJson(QJsonDocument::Compact));
    qDebug() << "[MessageBroker] Forwarding private message:" << serialized;
    emit outboundMessageReady(serialized);
}
