#ifndef CHATCLIENTMANAGER_H
#define CHATCLIENTMANAGER_H

#include <QObject>
#include <QQmlEngine>
#include "discovery/discoverypayload.h"
#include "websocket/websocketmanager.h"
#include "chat/chatchannelpayload.h"

class ChatClientManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    ChatClientManager(QObject *parent = nullptr);
    ChatClientManager(const DiscoveryPayload &payload, const QString &token, QObject *parent);

    Q_INVOKABLE void connectToServer();
    Q_INVOKABLE void setAccessToken(const QString &token);
    Q_INVOKABLE void setDiscoveryPayload(const DiscoveryPayload &payload);

signals:
    void connected();
    void disconnected();
    void connectionError(const QString &message);
    void activeChannelsReceived(const QList<ChatChannelPayload> &channels);

private:
    WebsocketManager m_websocketManager;
    QString m_accessToken;
    DiscoveryPayload m_payload;
};

#endif // CHATCLIENTMANAGER_H
