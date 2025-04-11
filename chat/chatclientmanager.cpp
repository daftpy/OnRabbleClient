#include "chatclientmanager.h"
#include <QDebug>

// Creates a ChatClientManager with no payload or token set
ChatClientManager::ChatClientManager(QObject *parent) : QObject{parent}
{
    qDebug() << "ChatClientManager: initialized";

    // Connect the WebsocketManager and ChatClientManager connections
    connect(&m_websocketManager, &WebsocketManager::connected,
            this, &ChatClientManager::connected);
    connect(&m_websocketManager, &WebsocketManager::disconnected,
            this, &ChatClientManager::disconnected);
    connect(&m_websocketManager, &WebsocketManager::connectionError,
            this, &ChatClientManager::connectionError);

    // Connect the WebsocketManager to the MessageBroker
    connect(&m_websocketManager, &WebsocketManager::textMessageReceived,
            &m_messageBroker, &MessageBroker::processMessage);
}

// Creates a ChatClientManager with a payload and token set, ready to connect
ChatClientManager::ChatClientManager(const DiscoveryPayload &payload, const QString &token, QObject *parent)
    : QObject{parent}, m_accessToken(token), m_payload(payload)
{
    qDebug() << "ChatClientManager: initialized";

    // Connect the WebsocketManager and ChatClientManager connections
    connect(&m_websocketManager, &WebsocketManager::connected,
            this, &ChatClientManager::connected);
    connect(&m_websocketManager, &WebsocketManager::disconnected,
            this, &ChatClientManager::disconnected);
    connect(&m_websocketManager, &WebsocketManager::connectionError,
            this, &ChatClientManager::connectionError);

    // Connect the WebsocketManager to the MessageBroker
    connect(&m_websocketManager, &WebsocketManager::textMessageReceived,
            &m_messageBroker, &MessageBroker::processMessage);
}

// Initiates the connection to the server through the websocketManager
void ChatClientManager::connectToServer()
{
    m_websocketManager.initiateConnection(m_payload, m_accessToken);
}

// Sets the access token, used for accessing the chat server and obtaining basic user details
void ChatClientManager::setAccessToken(const QString &token)
{
    m_accessToken = token;
}

// Sets the discovery payload which contains the critical endpoints for the server
void ChatClientManager::setDiscoveryPayload(const DiscoveryPayload &payload)
{
    m_payload = payload;
}

QObject *ChatClientManager::broker()
{
    return &m_messageBroker;
}
