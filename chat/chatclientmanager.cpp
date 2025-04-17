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
    connect(&m_messageBroker, &MessageBroker::outboundMessageReady,
            &m_websocketManager, &WebsocketManager::sendChatMessage);

    connect(&m_messageBroker, &MessageBroker::chatMessageReceived,
            this, &ChatClientManager::handleChatMessage);

    connect(&m_messageBroker, &MessageBroker::bulkChatMessagesReceived,
            this, &ChatClientManager::handleBulkChatMessages);

    connect(&m_messageBroker, &MessageBroker::activeChannelsReceived,
            this, &ChatClientManager::handleActiveChannels);
}

// Creates a ChatClientManager with a payload and token set, ready to connect
ChatClientManager::ChatClientManager(const DiscoveryPayload &payload, const QString &token, QObject *parent)
    : QObject{parent}, m_accessToken(token), m_payload(payload), m_user(parseJwtClaims(token))
{
    qDebug() << "ChatClientManager: initialized with token";

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
    connect(&m_messageBroker, &MessageBroker::outboundMessageReady,
            &m_websocketManager, &WebsocketManager::sendChatMessage);

    connect(&m_messageBroker, &MessageBroker::chatMessageReceived,
            this, &ChatClientManager::handleChatMessage);

    connect(&m_messageBroker, &MessageBroker::bulkChatMessagesReceived,
            this, &ChatClientManager::handleBulkChatMessages);

    connect(&m_messageBroker, &MessageBroker::activeChannelsReceived,
            this, &ChatClientManager::handleActiveChannels);

    {
        logJwtClaims(token); // Logs the JWT payload for now
    }
}

// Initiates the connection to the server through the websocketManager
void ChatClientManager::connectToServer()
{
    m_websocketManager.initiateConnection(m_payload, m_accessToken);
}

// Sets the access token, used for accessing the chat server and obtaining basic user details
void ChatClientManager::setAccessToken(const QString &token)
{
    {
        logJwtClaims(token); // Logs the JWT payload for now
    }
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

QObject *ChatClientManager::messageModel()
{
    return &m_messageModel;
}

ClientUserPayload ChatClientManager::user()
{
    return m_user;
}

QObject *ChatClientManager::proxyForChannel(const QString &channelName) const
{
    return m_channelProxies.value(channelName, nullptr);
}

QObject *ChatClientManager::channelModel()
{
    return &m_channelModel;
}

QList<ChannelProxyModel *> ChatClientManager::channelProxyList() const
{
    QList<ChannelProxyModel*> list;

    // Collect keys (QString) and sort them deterministically (optional)
    QStringList keys = m_channelProxies.keys();
    std::sort(keys.begin(), keys.end(), [](const QString &a, const QString &b) {
        return a.localeAwareCompare(b) < 0;
    });

    // Create list in sorted order
    for (const QString &key : keys) {
        list.append(m_channelProxies.value(key));
    }

    return list;
}

void ChatClientManager::handleChatMessage(const ChatMessagePayload &msg)
{
    m_messageModel.appendMessage(msg);
}

void ChatClientManager::handleBulkChatMessages(const QList<ChatMessagePayload> &messages)
{
    for (const auto &msg : messages) {
        m_messageModel.appendMessage(msg);
    }
}

void ChatClientManager::handleActiveChannels(const QList<ChannelPayload> &channels)
{
    // Ensure
    QList<ChannelPayload> sortedChannels = channels;
    std::sort(sortedChannels.begin(), sortedChannels.end());

    emit activeChannelsReceived(sortedChannels);

    // Clear and set the channel list
    m_channelModel.clear();
    m_channelModel.addChannels(sortedChannels);

    // Create the proxy models to filter the chat messages
    QList<ChannelProxyModel*> proxyList;
    for (const auto &channel : sortedChannels) {
        const QString &name = channel.name();

        if (!m_channelProxies.contains(name)) {
            auto *proxy = new ChannelProxyModel(this);
            proxy->setSourceModel(&m_messageModel);
            proxy->setChannel(name);
            m_channelProxies.insert(name, proxy);
            qDebug() << "Created proxy model for channel:" << name;
        }

        auto *proxyModel = m_channelProxies.value(name);
        qDebug() << "Channel:" << name << "Filtered message count:" << proxyModel->rowCount();
        proxyList.append(proxyModel);
    }

    emit activeChannelsReady(proxyList);
}

QVariantMap ChatClientManager::parseJwtClaims(const QString &jwtToken)
{
    const QStringList parts = jwtToken.split('.');
    if (parts.size() != 3) {
        qWarning() << "[parseJwt] Invalid JWT format. Parts:" << parts.size();
        return {};
    }

    const QByteArray payloadData = QByteArray::fromBase64(parts[1].toUtf8(), QByteArray::Base64UrlEncoding);
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(payloadData, &error);

    if (error.error != QJsonParseError::NoError || !doc.isObject()) {
        qWarning() << "[parseJwt] Failed to parse JSON payload:" << error.errorString();
        return {};
    }

    return doc.object().toVariantMap();
}

void ChatClientManager::logJwtClaims(const QString &jwtToken)
{
    const QStringList parts = jwtToken.split('.');
    if (parts.size() != 3) {
        qWarning() << "[parseJwt] Invalid JWT format. Parts:" << parts.size();
        return;
    }

    QByteArray base64Payload = parts[1].toUtf8();
    QByteArray decodedPayload = QByteArray::fromBase64(base64Payload, QByteArray::Base64UrlEncoding);
    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(decodedPayload, &error);

    if (error.error != QJsonParseError::NoError || !doc.isObject()) {
        qWarning() << "[parseJwt] Failed to parse JSON payload:" << error.errorString();
        return;
    }

    const QVariantMap claims = doc.object().toVariantMap();
    qDebug() << "[parseJwt] JWT claims:";
    for (auto it = claims.begin(); it != claims.end(); ++it) {
        qDebug() << " •" << it.key() << ":" << it.value();
    }
}
