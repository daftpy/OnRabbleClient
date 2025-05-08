#include "discoverymanager.h"
#include <QDebug>

/*!
    \class DiscoveryManager
    \inmodule OnRabbleClient
    \brief Provides a high-level interface for initiating discovery requests.

    The DiscoveryManager is responsible for initiating the server discovery process using a URL.
    It emits signals to indicate success or failure. It wraps DiscoveryCore to perform
    the actual network request and JSON parsing.
*/

/*---------------------------- Signals ----------------------------*/
/*!
    \fn void DiscoveryManager::discoverySuccess(const DiscoveryPayload &payload)
    \brief Emitted when the discovery process completes successfully.

    This signal is emitted after a successful request to a discovery endpoint.
    The \a payload contains the server's metadata used to configure the client.
*/

/*!
    \fn void DiscoveryManager::discoveryFailed(const QString &error)
    \brief Emitted when discovery fails due to a network or parsing error.

    This signal is emitted when the discovery request cannot complete successfully.
    The \a error string describes the reason for the failure (e.g., connection refused or invalid format).
*/

/*----------------------- Member Functions ------------------------*/
/*!
    \fn DiscoveryManager::DiscoveryManager(QObject *parent)
    \brief Constructs the DiscoveryManager.

    \a parent is the optional QObject parent.
*/
DiscoveryManager::DiscoveryManager(QObject *parent) : QObject{parent}
{
    qDebug() << "DiscoveryManager: initialized";
}

/*!
    \fn void DiscoveryManager::discover(const QString urlString)
    \brief Begins the discovery process using the given \a urlString.
*/
void DiscoveryManager::discover(const QString urlString)
{
    qDebug() << "DiscoveryManager: Starting discovery for" << urlString;

    QUrl url(urlString);
    m_discoveryCore.fetchServerMeta(url, [this](const DiscoveryPayload &payload, const QString &error) {
        if (!error.isEmpty()) {
            qWarning() << "DiscoveryManager: Discovery failed with error:" << error;
            emit discoveryFailed(error);
        } else {
            qDebug() << "DiscoveryManager: Discovery successful";
            emit discoverySuccess(payload);
        }
    });
}
