#ifndef MESSAGEBROKER_H
#define MESSAGEBROKER_H

#include <QObject>
#include <QQmlEngine>
#include "chat/chatchannelpayload.h"
#include "chat/chatmessagepayload.h"

struct ActiveChannel {
    int id = -1;
    QString name;
};

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
    void setActiveChannel(int channelId, const QString &channelName);

signals:
    // Emitted when a list of active channels is received from the server
    void activeChannelsReceived(const QList<ChatChannelPayload> &channels);
    void activeChannelChanged(const QString &name);
    void bulkChatMessagesReceived(const QList<ChatMessagePayload> &messages);


private:
    ActiveChannel m_activeChannel;
};

#endif // MESSAGEBROKER_H
