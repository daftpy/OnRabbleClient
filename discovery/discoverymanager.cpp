#include "discoverymanager.h"
#include <QDebug>

DiscoveryManager::DiscoveryManager(QObject *parent) : QObject{parent}
{
    qDebug() << "DiscoveryManager: initialized";
}

void DiscoveryManager::discover(const QString urlString)
{
    qDebug() << "DiscoveryManager: Starting discovery for" << urlString;

    // TODO: Discovery process
    QUrl url(urlString);
    m_discoveryCore.fetchServerMeta(url, [this](const DiscoveryPayload &payload, const QString &error) {
        if (!error.isEmpty()) {
            qWarning() << "DiscoveryManager: Discovery failed with error:" << error;
            emit discoveryFailed(error);
        } else {
            qDebug() << "DiscoveryManager: Discovery successful";
            emit discovered(payload);
        }
    });
}
