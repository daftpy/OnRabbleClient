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
    m_webSocket.open(payload.chatEndpoint() + "?token=" + token);
}

void WebsocketManager::sendChatMessage(const QString &message)
{
    if (m_webSocket.isValid() && m_webSocket.state() == QAbstractSocket::ConnectedState) {
        qDebug() << "Sending chat message:" << message;
        m_webSocket.sendTextMessage(message);
    } else {
        qWarning() << "WebSocket not connected. Message not sent.";
    }
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
    qDebug() << "WebsocketManager: Message received.";
    emit textMessageReceived(message);
}

