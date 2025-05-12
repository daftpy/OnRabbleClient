#include "clientmanager.h"
#include <QDebug>

/*!
    \class ClientManager
    \inmodule OnRabbleClient
    \brief Manages client-side connection, session state, and proxy model wiring.

    \section1 Overview
    ClientManager sets up the WebSocket connection, manages user identity via JWT,
    routes messages through the MessageBroker, and provides access to chat models
    and filtered proxies for QML.

    \div {class="internal"}
    \section2 Internal Members

        The following private member variables and utility functions are used internally
        by ClientManager and are referenced here for developer clarity. Full documentation
        is available in the source file:

        \b Private \b Variables
        \list
            \li \tt{m_websocketManager (WebsocketManager)} – Maintains the active WebSocket connection and emits raw messages.
            \li \tt{m_messageBroker (\l MessageBroker)} – Parses and dispatches incoming/outgoing structured chat messages.
            \li \tt{m_user (\l ClientUserPayload)} – Holds decoded user information from the JWT token.
            \li \tt{m_accessToken (\l QString)} – The current JWT access token for this session.
            \li \tt{m_payload (\l DiscoveryPayload)} – Connection metadata such as server URLs.
            \li \tt{m_channelProxies (\l{QHash}<\l{QString}, ChannelProxyModel*>)} – Proxies for filtering public chat messages by channel.
            \li \tt{m_privateChatProxies (\l{QHash}<\l{QString}, PrivateChatMessageProxyModel*>)} – Proxies for filtering private messages by user.
            \li \tt{m_channelModel (ChannelModel)} – Maintains the list of all known channels.
        \endlist

        \b Internal \b Functions
        \list
            \li \tt{parseJwtClaims(\l{QString})} – Parses a JWT token and returns its claims as a QVariantMap.
            \li \tt{logJwtClaims(\l{QString})} – Logs the contents of a JWT to the debug console.
            \li \tt{handleActiveChannels(\l{QList}<\l{ChannelPayload}>)} – Initializes proxies and populates the channel model from server data.
        \endlist
    \enddiv
*/

/*!
    \fn ClientManager::ClientManager(QObject *parent)
    \brief Constructs a ClientManager instance with no token or payload.

    This is the default constructor for QML and requires \c setDiscoveryPayload(payload) and \c setAccessToken(token)
    to be called before \c connectToServer().

    \a parent is the optional parent object.
*/
ClientManager::ClientManager(QObject *parent)
    : QObject{parent}
{
    qDebug() << "ClientManager: initialized";

    connect(&m_websocketManager, &WebsocketManager::connected, this, &ClientManager::connected);
    connect(&m_websocketManager, &WebsocketManager::disconnected, this, &ClientManager::disconnected);
    connect(&m_websocketManager, &WebsocketManager::connectionError, this, &ClientManager::connectionError);

    connect(&m_websocketManager, &WebsocketManager::textMessageReceived,
            &m_messageBroker, &MessageBroker::processMessage);
    connect(&m_messageBroker, &MessageBroker::outboundMessageReady,
            &m_websocketManager, &WebsocketManager::sendChatMessage);

    connect(&m_messageBroker, &MessageBroker::activeChannelsReceived,
            this, &ClientManager::handleActiveChannels);
}

/*!
    \fn ClientManager::ClientManager(const DiscoveryPayload &payload, const QString &token, QObject *parent)
    \brief Constructs a ClientManager with an access token and discovery payload.

    \a payload is used to configure connection endpoints.
    \a token is a JWT used to derive the current user identity.
    \a parent is the optional QObject parent.
*/
ClientManager::ClientManager(const DiscoveryPayload &payload, const QString &token, QObject *parent)
    : QObject{parent}, m_accessToken(token), m_payload(payload), m_user(parseJwtClaims(token))
{
    qDebug() << "ClientManager: initialized with token";

    connect(&m_websocketManager, &WebsocketManager::connected, this, &ClientManager::connected);
    connect(&m_websocketManager, &WebsocketManager::disconnected, this, &ClientManager::disconnected);
    connect(&m_websocketManager, &WebsocketManager::connectionError, this, &ClientManager::connectionError);

    connect(&m_websocketManager, &WebsocketManager::textMessageReceived,
            &m_messageBroker, &MessageBroker::processMessage);
    connect(&m_messageBroker, &MessageBroker::outboundMessageReady,
            &m_websocketManager, &WebsocketManager::sendChatMessage);

    connect(&m_messageBroker, &MessageBroker::activeChannelsReceived,
            this, &ClientManager::handleActiveChannels);

    logJwtClaims(token);
}

/*!
    \fn void ClientManager::connectToServer()
    \brief Connects to the WebSocket server using the current discovery payload and access token.
*/
void ClientManager::connectToServer()
{
    m_websocketManager.initiateConnection(m_payload, m_accessToken);
}

/*!
    \fn void ClientManager::setAccessToken(const QString &token)
    \brief Updates the internal access token and logs decoded claims.

    \a token is the new JWT to use for authentication and user identification.
*/
void ClientManager::setAccessToken(const QString &token)
{
    logJwtClaims(token);
    m_accessToken = token;
}

/*!
    \fn void ClientManager::setDiscoveryPayload(const DiscoveryPayload &payload)
    \brief Updates the internal discovery configuration.

    \a payload provides updated server endpoint information.
*/
void ClientManager::setDiscoveryPayload(const DiscoveryPayload &payload)
{
    m_payload = payload;
}

/*!
    \property ClientManager::broker
    \brief Returns the internal MessageBroker responsible for routing and parsing messages.
*/
QObject *ClientManager::broker()
{
    return &m_messageBroker;
}

/*!
    \property ClientManager::user
    \brief Returns parsed user information extracted from the access token.
*/
ClientUserPayload ClientManager::user()
{
    return m_user;
}

/*!
    \fn QObject* ClientManager::proxyForChannel(const QString &channelName) const
    \brief Returns a proxy model that filters chat messages by public channel.

    The proxy filters the global chat message model to only include messages
    associated with the given \a channelName.

    Returns \c nullptr if no proxy has been created yet for the channel.
*/
QObject *ClientManager::proxyForChannel(const QString &channelName) const
{
    return m_channelProxies.value(channelName, nullptr);
}

/*!
    \fn QObject* ClientManager::proxyForPrivateUser(const QString &userId)
    \brief Returns a proxy model that filters private chat messages exchanged with a specific user.

    The proxy filters the full private chat message model to only include messages
    between the current user and the specified \a userId. If a proxy does not already exist,
    it is created and configured automatically.

    Returns a pointer to the proxy model for the given user.
*/
QObject *ClientManager::proxyForPrivateUser(const QString &userId)
{
    if (m_privateChatProxies.contains(userId)) {
        return m_privateChatProxies.value(userId);
    }

    auto *proxy = new PrivateChatMessageProxyModel(this);
    proxy->setSourceModel(&m_messageBroker.privateMessageModel());
    proxy->setMyUserId(m_user.id());
    proxy->setTargetUserId(userId);

    m_privateChatProxies.insert(userId, proxy);
    qDebug() << "[ChatClientManager] Created PrivateChatMessageProxyModel for user:" << userId;
    emit privateChatMessageProxyListChanged(privateChatMessageProxyList());
    return proxy;
}

/*!
    \property ClientManager::channelModel
    \brief Returns the ChannelModel instance representing all known channels.
*/
QObject *ClientManager::channelModel()
{
    return &m_channelModel;
}

/*!
    \property ClientManager::channelProxyList
    \brief Returns a locale-aware sorted list of all available channel proxies.
*/
QList<ChannelProxyModel *> ClientManager::channelProxyList() const
{
    QList<ChannelProxyModel*> list;
    QStringList keys = m_channelProxies.keys();
    std::sort(keys.begin(), keys.end(), [](const QString &a, const QString &b) {
        return a.localeAwareCompare(b) < 0;
    });
    for (const QString &key : keys) {
        list.append(m_channelProxies.value(key));
    }
    return list;
}

/*!
    \property ClientManager::privateChatMessageProxyList
    \brief Returns all private chat proxies that have been created.
*/
QList<PrivateChatMessageProxyModel *> ClientManager::privateChatMessageProxyList() const
{
    return m_privateChatProxies.values();
}

/*!
    \fn void ClientManager::handleActiveChannels(const QList<ChannelPayload> &channels)
    \brief Populates the channel model and creates proxies for each channel in \a channels.
*/
void ClientManager::handleActiveChannels(const QList<ChannelPayload> &channels)
{
    QList<ChannelPayload> sortedChannels = channels;
    std::sort(sortedChannels.begin(), sortedChannels.end());

    emit activeChannelsReceived(sortedChannels);
    m_channelModel.clear();
    m_channelModel.addChannels(sortedChannels);

    QList<ChannelProxyModel*> proxyList;
    for (const auto &channel : sortedChannels) {
        const QString &name = channel.name();

        if (!m_channelProxies.contains(name)) {
            auto *proxy = new ChannelProxyModel(this);
            proxy->setSourceModel(&m_messageBroker.messageModel());
            proxy->setChannel(name);
            m_channelProxies.insert(name, proxy);
            qDebug() << "Created proxy model for channel:" << name;
        }

        proxyList.append(m_channelProxies.value(name));
    }

    emit activeChannelsReady(proxyList);
}

/*!
    \fn QVariantMap ClientManager::parseJwtClaims(const QString &jwtToken)
    \brief Parses a JWT and returns the decoded payload section as a QVariantMap.

    \a jwtToken is the JWT string to decode.
    Returns an empty map if the token is invalid or cannot be decoded.
*/
QVariantMap ClientManager::parseJwtClaims(const QString &jwtToken)
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

/*!
    \fn void ClientManager::logJwtClaims(const QString &jwtToken)
    \brief Decodes and logs all claims found in \a jwtToken.

    The claims are printed to the debug console for inspection.
*/
void ClientManager::logJwtClaims(const QString &jwtToken)
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

/*---------------------------- Signals ----------------------------*/
/*!
    \fn void ClientManager::connected()
    \brief This signal is emitted when a connection to the chat server is successfully established.

    This indicates that the WebSocket handshake and authentication flow completed successfully.
*/

/*!
    \fn void ClientManager::disconnected()
    \brief This signal is emitted when the chat server connection is closed.

    This could be due to a user action, a dropped network connection, or a server-initiated disconnect.
*/

/*!
    \fn void ClientManager::connectionError(const QString &message)
    \brief This signal is emitted when an error occurs during connection.

    \a message contains the error description, suitable for display in the UI.
*/

/*!
    \fn void ClientManager::activeChannelsReceived(const QList<ChannelPayload> &channels)
    \brief This signal is emitted when the list of active channels is received from the server.

    The \a channels list contains metadata about each available channel. This data is used to populate
    models and proxies in the chat UI.
*/

/*!
    \fn void ClientManager::activeChannelsReady(const QList<ChannelProxyModel*> &proxies)
    \brief This signal is emitted when proxies for the active channels have been created and configured.

    \a proxies contains a list of ready-to-use `ChannelProxyModel` instances, one per active channel.
*/

/*!
    \fn void ClientManager::privateChatMessageProxyListChanged(const QList<PrivateChatMessageProxyModel*> &proxies)
    \brief This signal is emitted when the list of private chat proxies changes.

    This occurs when a new proxy for a private conversation is created.
    \a proxies is the full updated list of proxies.
*/
