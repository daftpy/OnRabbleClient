#ifndef MESSAGEBROKER_H
#define MESSAGEBROKER_H

#include <QObject>
#include <QQmlEngine>

#include "chat/channelpayload.h"
#include "chat/chatmessagepayload.h"
#include "chat/privatechatmessagepayload.h"
#include "user/userstatuspayload.h"

class MessageBroker : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit MessageBroker(QObject *parent = nullptr);

    void processMessage(const QString &message);

public slots:
    void sendChatMessage(const QString &message);
    void sendPrivateChatMessage(const QString &message);

signals:
    void activeChannelsReceived(const QList<ChannelPayload> &channels);
    void activeChannelChanged(const QString &name);
    void bulkChatMessagesReceived(const QList<ChatMessagePayload> &messages);
    void chatMessageReceived(const ChatMessagePayload &message);
    void bulkPrivateMessagesReceived(const QList<PrivateChatMessagePayload> &messages);
    void privateChatMessageReceived(const PrivateChatMessagePayload &message);
    void connectedUsersReceived(QList<UserStatusPayload> users);
    void userStatusUpdated(const UserStatusPayload &payload);
    void outboundMessageReady(const QString &message);
};

#endif // MESSAGEBROKER_H
