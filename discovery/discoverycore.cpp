#include "discoverycore.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QDebug>

/*!
    \class DiscoveryCore
    \inmodule OnRabbleClient
    \brief Performs low-level HTTP discovery and JSON parsing.

    DiscoveryCore is responsible for making an HTTP GET request to a chat server's discovery
    endpoint, parsing the JSON response into a \l DiscoveryPayload, and emitting the result
    via signals. Only one request is active at any time; repeated calls cancel the previous one.

    \div {class="internal"}
    \section2 Internal Members

        These members are maintained internally by \c DiscoveryCore and are not intended
        for external use. They are documented here for developer clarity.

        \b Private \b Variables
        \list
            \li \tt{m_accessManager (\l QNetworkAccessManager)} – Handles asynchronous HTTP requests for discovery.
            \li \tt{m_currentReply (\l QNetworkReply*)} – Tracks the active network request so it can be canceled or cleared.
        \endlist

        \b Internal \b Functions
        \list
            \li \tt{handleReply()} – Processes the HTTP response and emits either a success or error signal.
            \li \tt{clearCurrentReply()} – Resets and cleans up the current network reply.
        \endlist
    \enddiv

    \sa DiscoveryPayload, DiscoveryPage
*/

/*!
    \fn DiscoveryCore::DiscoveryCore(QObject *parent)
    \brief Constructs the DiscoveryCore.

    \a parent is the optional parent object for ownership and signal propagation.
*/
DiscoveryCore::DiscoveryCore(QObject *parent)
    : QObject(parent)
{
}

/*!
    \fn void DiscoveryCore::fetchServerMeta(const QUrl &url)
    \brief Initiates a discovery request to the given \a url.

    Cancels any previous request in progress. Emits \l success with a parsed
    \l DiscoveryPayload on success or \l error with a descriptive message on failure.

    \sa DiscoveryPayload
*/
void DiscoveryCore::fetchServerMeta(const QUrl &url)
{
    if (m_currentReply) {
        m_currentReply->abort();
        m_currentReply->deleteLater();
        m_currentReply = nullptr;
    }

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    m_currentReply = m_accessManager.get(request);

    connect(m_currentReply, &QNetworkReply::finished, this, &DiscoveryCore::handleReply);
}

/*!
    \internal
    \brief Processes the reply from the discovery request and emits the appropriate signal.
*/
void DiscoveryCore::handleReply()
{
    if (!m_currentReply)
        return;

    QNetworkReply *reply = m_currentReply;
    m_currentReply = nullptr;

    qDebug() << "Reply received for" << reply->url().toString();

    if (reply->error() != QNetworkReply::NoError) {
        QString err = reply->errorString();
        qWarning() << "Discovery error:" << err;
        emit error(err);
        reply->deleteLater();
        return;
    }

    QByteArray responseData = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);

    if (!jsonDoc.isNull() && jsonDoc.isObject()) {
        DiscoveryPayload payload(jsonDoc.object());
        qDebug() << "Discovery successful for" << reply->url().toString();
        emit success(payload);
    } else {
        QString err = "Invalid or bad JSON response";
        qWarning() << err;
        emit error(err);
    }

    reply->deleteLater();
}
