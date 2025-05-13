#ifndef DISCOVERYCORE_H
#define DISCOVERYCORE_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QUrl>
#include "messages/payloads/system/discoverypayload.h"

class DiscoveryCore : public QObject
{
    Q_OBJECT

public:
    explicit DiscoveryCore(QObject *parent = nullptr);

    void fetchServerMeta(const QUrl &url); // Starts discovery for a given URL

signals:
    void success(const DiscoveryPayload &payload); // Emitted on successful discovery
    void error(const QString &error);              // Emitted on failure (network or parse)

private:
    void handleReply();
    void clearCurrentReply();

    QNetworkAccessManager m_accessManager;
    QNetworkReply *m_currentReply{nullptr};
};

#endif // DISCOVERYCORE_H
