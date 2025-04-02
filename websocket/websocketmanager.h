#ifndef WEBSOCKETMANAGER_H
#define WEBSOCKETMANAGER_H

#include <QObject>
#include <QQmlEngine>
#include <QtWebSockets>
#include <QAbstractSocket>
#include "discovery/discoverypayload.h"

/* WebsocketManager manages the connection between the chat client
 * and the chat server. Messages will originate here.
*/
class WebsocketManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    WebsocketManager(QObject *parent = nullptr);

    Q_INVOKABLE void initiateConnection(const DiscoveryPayload &payload, const QString &token);

private slots:
    void onConnected();
    void onDisconnected();
    void onErrorOccurred(QAbstractSocket::SocketError error);

private:
    QWebSocket m_webSocket;
};

#endif // WEBSOCKETMANAGER_H
