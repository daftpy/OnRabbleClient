#ifndef MESSAGEBROKER_H
#define MESSAGEBROKER_H

#include <QObject>
#include <QQmlEngine>

#include "messages/payloads/channelpayload.h"
#include "chat/chatmessagemodel.h"
#include "chat/privatechatmessagemodel.h"
#include "messages/payloads/chatmessagepayload.h"
#include "messages/payloads/privatechatmessagepayload.h"
#include "messages/payloads/system/userstatuspayload.h"

class MessageBroker : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit MessageBroker(QObject *parent = nullptr);

    // Parses raw JSON server message and dispatches to appropriate handler
    void processMessage(const QString &message);

    // Access to the raw public and private message models
    ChatMessageModel& messageModel();
    PrivateChatMessageModel& privateMessageModel();

public slots:
    // Emits a serialized chat or private chat message to the server
    void sendChatMessage(const QString &message);
    void sendPrivateChatMessage(const QString &message);

signals:
    // Emitted when structured payloads are parsed from server messages
    void activeChannelsReceived(const QList<ChannelPayload> &channels);
    void connectedUsersReceived(QList<UserStatusPayload> users);
    void userStatusUpdated(const UserStatusPayload &payload);
    void outboundMessageReady(const QString &message);

private:
    // Internal message handlers
    void handleChatMessage(const ChatMessagePayload &msg);
    void handlePrivateChatMessage(const PrivateChatMessagePayload &msg);
    void handleBulkChatMessages(const QList<ChatMessagePayload> &messages);
    void handleBulkPrivateMessages(const QList<PrivateChatMessagePayload> &messages);

    ChatMessageModel m_messageModel;
    PrivateChatMessageModel m_privateMessageModel;
};

#endif // MESSAGEBROKER_H
