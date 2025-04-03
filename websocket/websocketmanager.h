#ifndef WEBSOCKETMANAGER_H
#define WEBSOCKETMANAGER_H

#include <QObject>
#include <QQmlEngine>
#include <QtWebSockets>
#include <QAbstractSocket>
#include "discovery/discoverypayload.h"

// WebsocketManager manages the connection between the chat client
// and the chat server. Messages will originate here.
class WebsocketManager : public QObject
{
    Q_OBJECT
public:
    WebsocketManager(QObject *parent = nullptr);

    // Initiates the connection to the server
    Q_INVOKABLE void initiateConnection(const DiscoveryPayload &payload, const QString &token);

signals:
    // Signals for basic connection events, bubbles up to the ChatClientManager
    void connected();
    void disconnected();
    void connectionError(QString errorMessage);

private slots:
    // Catches signals from the QWebSocket
    void onConnected();
    void onDisconnected();
    void onErrorOccurred(QAbstractSocket::SocketError error);

private:
    QWebSocket m_webSocket;
};

#endif // WEBSOCKETMANAGER_H
