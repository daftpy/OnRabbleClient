#ifndef CHATCLIENTMANAGER_H
#define CHATCLIENTMANAGER_H

#include <QObject>
#include <QQmlEngine>
#include "discovery/discoverypayload.h"
#include "websocket/websocketmanager.h"
#include "messages/messagebroker.h"

class ChatClientManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    // Exposes the broker so QML components can get messages
    Q_PROPERTY(QObject* broker READ broker CONSTANT)
public:
    ChatClientManager(QObject *parent = nullptr);
    ChatClientManager(const DiscoveryPayload &payload, const QString &token, QObject *parent);

    Q_INVOKABLE void connectToServer();
    Q_INVOKABLE void setAccessToken(const QString &token);
    Q_INVOKABLE void setDiscoveryPayload(const DiscoveryPayload &payload);

    QObject* broker();

signals:
    void connected();
    void disconnected();
    void connectionError(const QString &message);

private:
    WebsocketManager m_websocketManager;
    MessageBroker m_messageBroker;
    QString m_accessToken;
    DiscoveryPayload m_payload;
};

#endif // CHATCLIENTMANAGER_H
