#ifndef CLIENTMANAGER_H
#define CLIENTMANAGER_H

#include <QObject>
#include <QQmlEngine>

#include "messages/payloads/system/discoverypayload.h"
#include "websocket/websocketmanager.h"
#include "messages/messagebroker.h"
#include "messages/payloads/system/clientuserpayload.h"
#include "chat/channelmessageproxymodel.h"
#include "chat/channelmodel.h"
#include "chat/privatemessageproxymodel.h"

class ClientManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(QObject* broker READ broker CONSTANT)
    Q_PROPERTY(ClientUserPayload user READ user CONSTANT)
    Q_PROPERTY(QObject* channelModel READ channelModel CONSTANT)
    Q_PROPERTY(QList<ChannelMessageProxyModel*> channelProxyList READ channelProxyList NOTIFY activeChannelsReady)
    Q_PROPERTY(QList<PrivateMessageProxyModel*> privateMessageProxyList READ privateMessageProxyList NOTIFY privateMessageProxyListChanged)

public:
    explicit ClientManager(QObject *parent = nullptr);
    ClientManager(const DiscoveryPayload &payload, const QString &token, QObject *parent);

    // Starts a WebSocket connection using current token and discovery payload
    Q_INVOKABLE void connectToServer();

    // Set or update access token and discovery metadata
    Q_INVOKABLE void setAccessToken(const QString &token);
    Q_INVOKABLE void setDiscoveryPayload(const DiscoveryPayload &payload);

    // Access broker, user, and shared channel model
    QObject* broker();
    ClientUserPayload user();
    QObject* channelModel();

    // Get or create proxy models for messages
    Q_INVOKABLE QObject* proxyForChannel(const QString &channelName) const;
    Q_INVOKABLE QObject* proxyForPrivateUser(const QString &userId);

    // Proxy model collections
    QList<ChannelMessageProxyModel*> channelProxyList() const;
    QList<PrivateMessageProxyModel*> privateMessageProxyList() const;

signals:
    void connected();
    void disconnected();
    void connectionError(const QString &message);

    void activeChannelsReceived(const QList<ChannelPayload> &channels);
    void activeChannelsReady(const QList<ChannelMessageProxyModel*> &proxies);
    void privateMessageProxyListChanged(const QList<PrivateMessageProxyModel*> &proxies);

private slots:
    // Called when new channel list is received
    void handleActiveChannels(const QList<ChannelPayload> &channels);

private:
    // JWT parsing utilities
    QVariantMap parseJwtClaims(const QString &jwtToken);
    void logJwtClaims(const QString &jwtToken);

    WebsocketManager m_websocketManager;
    MessageBroker m_messageBroker;

    ClientUserPayload m_user;
    QString m_accessToken;
    DiscoveryPayload m_payload;

    QHash<QString, ChannelMessageProxyModel*> m_channelProxies;
    QHash<QString, PrivateMessageProxyModel*> m_privateChatProxies;
    ChannelModel m_channelModel;
};

#endif // CLIENTMANAGER_H
