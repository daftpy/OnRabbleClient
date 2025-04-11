#ifndef MESSAGEBROKER_H
#define MESSAGEBROKER_H

#include <QObject>
#include <QQmlEngine>
#include "chat/chatchannelpayload.h"

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
    void activeChannelsReceived(const QList<ChatChannelPayload> &channels);
};

#endif // MESSAGEBROKER_H
