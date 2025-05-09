#ifndef WEBSOCKETMANAGER_H
#define WEBSOCKETMANAGER_H

#include <QObject>
#include <QQmlEngine>
#include <QtWebSockets>
#include <QAbstractSocket>
#include "messages/payloads/system/discoverypayload.h"

// WebsocketManager manages the connection between the chat client
// and the chat server. Messages will originate here.
class WebsocketManager : public QObject
{
    Q_OBJECT
public:
    WebsocketManager(QObject *parent = nullptr);

    // Initiates the connection to the server
    Q_INVOKABLE void initiateConnection(const DiscoveryPayload &payload, const QString &token);

    /**
     * @brief Sends a message over the active WebSocket connection.
     * Logs a warning if not connected.
     */
    void sendChatMessage(const QString &message);

signals:
    // Signals for basic connection events, bubbles up to the ChatClientManager
    void connected();
    void disconnected();
    void connectionError(QString errorMessage);
    void textMessageReceived(const QString &message);

private slots:
    // Catches signals from the QWebSocket
    void onConnected();
    void onDisconnected();
    void onErrorOccurred(QAbstractSocket::SocketError error);
    void onTextMessageReceived(const QString &message);

private:
    void handleIncomingMessage(const QString &message);

    QWebSocket m_webSocket;
};

#endif // WEBSOCKETMANAGER_H
