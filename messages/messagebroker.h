#ifndef MESSAGEBROKER_H
#define MESSAGEBROKER_H

#include <QObject>
#include <QQmlEngine>
#include "chat/channelpayload.h"
#include "chat/chatmessagepayload.h"
#include "user/userstatuspayload.h"
#include "chat/privatechatmessagepayload.h"

// MessageBroker is responsible for interpreting incoming JSON messages
// and dispatching structured signals that other components can subscribe to.
class MessageBroker : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit MessageBroker(QObject *parent = nullptr);

    // Processes a JSON message from the server
    // and emits structured signals based on the message type
    void processMessage(const QString &message);

signals:
    // Emitted when a list of active channels is received from the server
    void activeChannelsReceived(const QList<ChannelPayload> &channels);
    void activeChannelChanged(const QString &name);
    void bulkChatMessagesReceived(const QList<ChatMessagePayload> &messages);
    void chatMessageReceived(const ChatMessagePayload &message);
    void privateChatMessageReceived(const PrivateChatMessagePayload &message);

    void outboundMessageReady(const QString &message);

    void connectedUsersReceived(QList<UserStatusPayload> users);

    void bulkPrivateMessagesReceived(const QList<PrivateChatMessagePayload> &messages);

public slots:
    /**
     * @brief Sends a raw message to the server.
     * This is intended to be connected to WebsocketManager.
     */
    void sendChatMessage(const QString &message);

    void sendPrivateChatMessage(const QString &message);
};

#endif // MESSAGEBROKER_H
