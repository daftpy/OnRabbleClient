#ifndef DISCOVERYMANAGER_H
#define DISCOVERYMANAGER_H

#include <QObject>
#include <QQmlEngine>
#include "messages/payloads/system/discoverypayload.h"
#include "discoverycore.h"

// Handles initiating a discovery attempt from QML or other client code.
// Emits signals for success (discovered) or failure (discoveryFailed).
class DiscoveryManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit DiscoveryManager(QObject *parent = nullptr);

    // Begins the discovery process for the given URL string.
    Q_INVOKABLE void discover(const QString urlString);

signals:

    // Emitted when discovery succeeds with a valid payload.
    void discoverySuccess(const DiscoveryPayload &payload);

    // Emitted if discovery fails, providing an error string.
    void discoveryFailed(const QString &error);

    void testSignal();

private:
    DiscoveryCore m_discoveryCore; // Does the actual network request and parsing
};

#endif // DISCOVERYMANAGER_H
