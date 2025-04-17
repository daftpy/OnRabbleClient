#include "messagebroker.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>

MessageBroker::MessageBroker(QObject *parent)
    : QObject{parent}
{
    qDebug() << "MessageBroker: initialized";
}

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
        qDebug() << "MessageBroker: received active channels!";
        QJsonArray channelsJson = obj["payload"].toObject()["channels"].toArray();
        QList<ChannelPayload> parsed;

        for (const QJsonValue &value : channelsJson) {
            parsed.append(ChannelPayload(value.toObject()));
        }

        emit activeChannelsReceived(parsed);
        return;
    } else if (type == "bulk_chat_messages") {
        qDebug() << "MessageBroker: received bulk chat messages!";
        const QJsonArray msgArray = obj["payload"].toObject()["messages"].toArray();
        QList<ChatMessagePayload> parsed;

        for (const QJsonValue &value : msgArray) {
            if (!value.isObject()) continue;
            parsed.append(ChatMessagePayload(value.toObject()));
        }

        emit bulkChatMessagesReceived(parsed);
        return;
    } else if (type == "chat_message") {
        qDebug() << "MessageBroker: received single chat message!";
        const QJsonObject payload = obj["payload"].toObject();
        ChatMessagePayload chatMsg(payload);

        emit chatMessageReceived(chatMsg);  // reuse existing signal
        return;
    } else if (type == "connected_users") {
        qDebug() << "MessageBroker: received connected users!";
        QJsonArray usersArray = obj["payload"].toObject()["users"].toArray();
        QList<UserStatusPayload> parsed;

        for (const QJsonValue &value : usersArray) {
            if (!value.isObject()) continue;
            parsed.append(UserStatusPayload(value.toObject()));
        }

        emit connectedUsersReceived(parsed);
        return;
    }


    // TODO: more handlers here
    qDebug() << "MessageBroker: Unhandled message type:" << type;
}

void MessageBroker::sendChatMessage(const QString &message)
{
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8(), &parseError);

    if (parseError.error != QJsonParseError::NoError || !doc.isObject()) {
        qWarning() << "[MessageBroker] Invalid JSON payload:" << parseError.errorString();
        return;
    }

    const QJsonObject obj = doc.object();

    const QString channel = obj.value("channel").toString().trimmed();
    const QString text = obj.value("message").toString().trimmed();

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

    QJsonObject root {
        { "type", "chat_message" },
        { "channel", channel },
        { "message", text }
    };

    const QString serialized = QString::fromUtf8(QJsonDocument(root).toJson(QJsonDocument::Compact));
    qDebug() << "[MessageBroker] Forwarding chat message:" << serialized;

    emit outboundMessageReady(serialized);
}

void MessageBroker::sendPrivateChatMessage(const QString &message)
{
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8(), &parseError);

    if (parseError.error != QJsonParseError::NoError || !doc.isObject()) {
        qWarning() << "[MessageBroker] Invalid JSON payload:" << parseError.errorString();
        return;
    }

    const QJsonObject obj = doc.object();
    const QString recipient = obj.value("recipientId").toString().trimmed();
    const QString text = obj.value("message").toString().trimmed();

    if (recipient.isEmpty()) {
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

    QJsonObject root {
        { "type", "private_chat_message" },
        { "recipient_id", recipient },
        { "message", text }
    };

    const QString serialized = QString::fromUtf8(QJsonDocument(root).toJson(QJsonDocument::Compact));
    qDebug() << "[MessageBroker] Forwarding chat message:" << serialized;

    emit outboundMessageReady(serialized);
}
