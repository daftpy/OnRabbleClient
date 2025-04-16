#ifndef CHATCLIENTMANAGER_H
#define CHATCLIENTMANAGER_H

#include <QObject>
#include <QQmlEngine>
#include "discovery/discoverypayload.h"
#include "websocket/websocketmanager.h"
#include "messages/messagebroker.h"
#include "client/clientuserpayload.h"
#include "chatmessagemodel.h"
#include "channelproxymodel.h"
#include "channelmodel.h"

/**
 * @brief The ChatClientManager class manages the client-side chat session.
 *
 * This class is responsible for handling the lifecycle of the connection to the chat server,
 * including secure WebSocket communication, message handling, and exposing user identity and message broker objects to QML.
 *
 * It acts as the central coordinator between the authentication token, server payload, message handling, and user context.
 */
class ChatClientManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    /**
     * @brief Provides access to the message broker for QML components.
     */
    Q_PROPERTY(QObject* broker READ broker CONSTANT)

    /**
     * @brief Provides the parsed user payload based on the access token.
     */
    Q_PROPERTY(ClientUserPayload user READ user CONSTANT)

    /**
     * @brief Provides access to the ChatMessageModel.
     */
    Q_PROPERTY(QObject* messageModel READ messageModel CONSTANT)

    /**
     * @brief Provides access to thee ChannelMessageModel.
     */
    Q_PROPERTY(QObject* channelModel READ channelModel CONSTANT)

public:
    /**
     * @brief Constructs a ChatClientManager with no payload or token set.
     * @param parent The parent QObject.
     */
    ChatClientManager(QObject *parent = nullptr);

    /**
     * @brief Constructs a ChatClientManager with an initial payload and access token.
     * @param payload The discovery payload providing server endpoints.
     * @param token The access token (JWT) for authentication.
     * @param parent The parent QObject.
     */
    ChatClientManager(const DiscoveryPayload &payload, const QString &token, QObject *parent);

    /**
     * @brief Initiates the connection to the chat server.
     */
    Q_INVOKABLE void connectToServer();

    /**
     * @brief Updates the access token used to authenticate with the server.
     * @param token A new JWT access token.
     */
    Q_INVOKABLE void setAccessToken(const QString &token);

    /**
     * @brief Updates the discovery payload that contains server endpoint information.
     * @param payload The new discovery payload.
     */
    Q_INVOKABLE void setDiscoveryPayload(const DiscoveryPayload &payload);

    /**
     * @brief Returns a pointer to the internal message broker for signal-based message handling.
     * @return QObject pointer to the message broker.
     */
    QObject* broker();

    /**
     * @brief Returns a pointer to the internal ChatMessageModel to expose for us in QML views.
     * @return QObject pointer to the chat message model.
     */
    QObject* messageModel();

    /**
     * @brief Returns the parsed user information from the current access token.
     * @return The ClientUserPayload containing user metadata and roles.
     */
    ClientUserPayload user();

    Q_INVOKABLE QObject* proxyForChannel(const QString &channelName) const;

    QObject* channelModel();

signals:
    /**
     * @brief Emitted when the connection to the server is successfully established.
     */
    void connected();

    /**
     * @brief Emitted when the connection to the server is closed or interrupted.
     */
    void disconnected();

    /**
     * @brief Emitted when a connection error occurs.
     * @param message A descriptive error message.
     */
    void connectionError(const QString &message);

    /**
     * @brief Emitted when a list of active channels is created and proxies initialized.
     *        Useful for QML components like a channel list or tab view.
     */
    Q_SIGNAL void activeChannelsReceived(const QList<ChannelPayload> &channels);

    /**
     * @brief Emitted when a list of active channels is created and proxies initialized.
     *        Useful for QML components like a channel list or tab view.
     */
    Q_SIGNAL void activeChannelsReady(const QList<ChannelProxyModel*> &proxies);

private slots:
    /**
     * @brief Handles a single chat message received from the server.
     * @param msg The chat message payload containing sender, channel, and message content.
     */
    void handleChatMessage(const ChatMessagePayload &msg);

    /**
     * @brief Handles a list of chat messages received in bulk from the server.
     * @param messages A list of chat message payloads.
     */
    void handleBulkChatMessages(const QList<ChatMessagePayload> &messages);

    /**
     * @brief Handles the activeChannelsReceived signal and creates proxy models for each channel.
     * @param channels The list of active channels provided by the server.
     */
    void handleActiveChannels(const QList<ChannelPayload> &channels);

private:
    /**
     * @brief Parses JWT token claims into a QVariantMap.
     * @param jwtToken The JWT token string.
     * @return A map of claims extracted from the token payload.
     */
    QVariantMap parseJwtClaims(const QString &jwtToken);

    /**
     * @brief Logs all claims from the JWT for debugging purposes.
     * @param jwtToken The JWT token string.
     */
    void logJwtClaims(const QString &jwtToken);

    WebsocketManager m_websocketManager;   ///< Handles WebSocket lifecycle and communication.
    MessageBroker m_messageBroker;         ///< Dispatches and routes incoming messages to appropriate consumers.
    ClientUserPayload m_user;              ///< Contains the currently authenticated user's identity and roles.
    QString m_accessToken;                 ///< Current JWT token used for authentication.
    DiscoveryPayload m_payload;            ///< Server endpoint payload retrieved from discovery.
    ChatMessageModel m_messageModel;       ///< The container for chat messages from the chat server.

    QHash<QString, ChannelProxyModel*> m_channelProxies;
    ChannelModel m_channelModel;
};

#endif // CHATCLIENTMANAGER_H
