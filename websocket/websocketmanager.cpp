#include "websocketmanager.h"
#include <QDebug>
#include <QMetaType>
#include <QJsonDocument>

WebsocketManager::WebsocketManager(QObject *parent) : QObject{parent}
{
    qDebug() << "WebsocketManager: initiated";

    // Register the QAbstractSocket::SocketError type for queued connections.
    qRegisterMetaType<QAbstractSocket::SocketError>("QAbstractSocket::SocketError");


    // Connect the slots for the connected and disconnected events
    connect(&m_webSocket, &QWebSocket::connected, this, &WebsocketManager::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &WebsocketManager::onDisconnected);
    connect(&m_webSocket, &QWebSocket::errorOccurred, this, &WebsocketManager::onErrorOccurred);
    connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &WebsocketManager::onTextMessageReceived);
}

void WebsocketManager::initiateConnection(const DiscoveryPayload &payload, const QString &token)
{
    // TODO: Create connection
    m_webSocket.open(payload.chatEndpoint() + "?token=" + token);
}

void WebsocketManager::onConnected()
{
    qDebug() << "Connected to the chatserver";
    emit connected();
}

void WebsocketManager::onDisconnected()
{
    qDebug() << "Disconnected from the chatserver";
    emit disconnected();
}

void WebsocketManager::onErrorOccurred(QAbstractSocket::SocketError error)
{
    qDebug() << "WebSocket error occurred:" << error << m_webSocket.errorString();
    emit connectionError(m_webSocket.errorString());
}

void WebsocketManager::onTextMessageReceived(const QString &message)
{
    qDebug() << "WebsocketManageer: Message received:";
    handleIncomingMessage(message);
}

void WebsocketManager::handleIncomingMessage(const QString &message)
{
    QJsonParseError parseError;
    QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8(), &parseError);

    if (parseError.error != QJsonParseError::NoError) {
        qWarning() << "Failed to parse incoming message:" << parseError.errorString();
        return;
    }

    if (!doc.isObject()) {
        qWarning() << "Expected JSON object in message";
        return;
    }

    QJsonObject obj = doc.object();
    const QString type = obj.value("type").toString();

    if (type == "active_channels") {
        qDebug() << "[handleIncomingMessage] Detected active_channels message";

        const QJsonArray channelsArray = obj["payload"].toObject().value("channels").toArray();
        QList<ChatChannelPayload> parsedChannels;

        for (const QJsonValue &v : channelsArray) {
            QJsonObject chan = v.toObject();
            parsedChannels.append(ChatChannelPayload(chan));
        }

        emit activeChannelsReceived(parsedChannels);
    } else {
        qDebug() << "[handleIncomingMessage] Unknown or unhandled message type:" << type;
    }
}
