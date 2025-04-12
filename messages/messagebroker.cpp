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
        QList<ChatChannelPayload> parsed;

        for (const QJsonValue &value : channelsJson) {
            parsed.append(ChatChannelPayload(value.toObject()));
        }

        // Set default active channel if none is currently set
        if (m_activeChannel.id == -1 && !parsed.isEmpty()) {
            const ChatChannelPayload &first = parsed.first();
            setActiveChannel(first.id(), first.name());
            emit activeChannelChanged(first.name());
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
    }

    // TODO: more handlers here
    qDebug() << "MessageBroker: Unhandled message type:" << type;
}

void MessageBroker::setActiveChannel(int channelId, const QString &channelName)
{
    m_activeChannel.id = channelId;
    m_activeChannel.name = channelName;
    qDebug() << "[MessageBroker] Active channel set to:" << channelId << channelName;
}
