#ifndef MESSAGEBROKER_H
#define MESSAGEBROKER_H

#include <QObject>
#include <QQmlEngine>

#include "messages/payloads/system/channelpayload.h"
#include "chat/chatmessagemodel.h"
#include "chat/privatemessagemodel.h"
#include "messages/payloads/chat/chatmessagepayload.h"
#include "messages/payloads/chat/privatemessagepayload.h"
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
    PrivateMessageModel& privateMessageModel();

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
    void handlePrivateChatMessage(const PrivateMessagePayload &msg);
    void handleBulkChatMessages(const QList<ChatMessagePayload> &messages);
    void handleBulkPrivateMessages(const QList<PrivateMessagePayload> &messages);

    ChatMessageModel m_messageModel;
    PrivateMessageModel m_privateMessageModel;
};

#endif // MESSAGEBROKER_H
