#ifndef DISCOVERYCORE_H
#define DISCOVERYCORE_H
#include <QString>
#include <QNetworkAccessManager>
#include <functional>
#include "discoverypayload.h"

class DiscoveryCore
{
public:
    using DiscoveryCallback = std::function<void(const DiscoveryPayload &payload, const QString error)>;

    DiscoveryCore() = default;

    // Starts the process of fetching the server meta from a given url
    void fetchServerMeta(const QUrl &url, DiscoveryCallback callback);

private:
    void handleReply(QNetworkReply *reply, const QUrl &url, DiscoveryCallback callback);

    QNetworkAccessManager m_accessManager;
};

#endif // DISCOVERYCORE_H
