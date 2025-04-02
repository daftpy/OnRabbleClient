#include "discoverycore.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>

void DiscoveryCore::fetchServerMeta(const QUrl &url, DiscoveryCallback callback)
{
    // Create the request and set the headers
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    // Get the response
    QNetworkReply *reply = m_accessManager.get(request);

    QObject::connect(reply, &QNetworkReply::finished, [this, reply, url, callback]() {
        handleReply(reply, url, callback);
    });
}

void DiscoveryCore::handleReply(QNetworkReply *reply, const QUrl &url, DiscoveryCallback callback)
{
    // TODO: implement a handler
    qDebug() << "Reply received for" << url.toString();
    // Check if a network error occurred.
    if (reply->error() != QNetworkReply::NoError) {
        QString err = reply->errorString();
        qWarning() << "Discovery error:" << err;
        // Call the callback with an empty payload and the error string.
        callback(DiscoveryPayload(), err);
        reply->deleteLater();
        return;
    }

    // Read the entire response.
    QByteArray responseData = reply->readAll();

    // Parse the JSON document.
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    if (!jsonDoc.isNull() && jsonDoc.isObject()) {
        QJsonObject jsonObj = jsonDoc.object();

        // Create a DiscoveryPayload using the extracted fields.
        DiscoveryPayload payload(jsonObj);

        qDebug() << "Discovery successful for" << url.toString();
        // Call the callback with the payload and an empty error.
        callback(payload, QString());
    } else {
        QString err = "Invalid or bad JSON response";
        qWarning() << err;
        // Call the callback with an empty payload and the error message.
        callback(DiscoveryPayload(), err);
    }
    reply->deleteLater();
}
