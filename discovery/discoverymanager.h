#ifndef DISCOVERYMANAGER_H
#define DISCOVERYMANAGER_H

#include <QObject>
#include <QQmlEngine>
#include "messages/payloads/system/discoverypayload.h"
#include "discoverycore.h"

class DiscoveryManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    DiscoveryManager(QObject *parent = nullptr);

    // Starts the discovery process, retrieving a DiscoveryPayload
    Q_INVOKABLE void discover(const QString urlString);

signals:
    // Informs of a succesful or failed discovery process
    void discovered(const DiscoveryPayload &payload);
    void discoveryFailed(const QString &error);

private:
    DiscoveryCore m_discoveryCore;
};

#endif // DISCOVERYMANAGER_H
