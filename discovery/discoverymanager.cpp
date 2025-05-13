#include "discoverymanager.h"
#include <QDebug>

/*!
    \class DiscoveryManager
    \inmodule OnRabbleClient
    \brief Provides a high-level interface for initiating discovery requests.

    The DiscoveryManager is responsible for initiating the server discovery process using a URL.
    It emits signals to indicate success or failure. It wraps DiscoveryCore to perform
    the actual network request and JSON parsing.

    \note The DiscoveryManager is intended to be used from QML and exposes a \c discover() method
    that takes a string-formatted URL. When the request finishes, it emits either
    \c discoverySuccess or \c discoveryFailed depending on the result.

    \sa DiscoveryCore, DiscoveryPayload, DiscoveryPage
*/

/*!
    \fn DiscoveryManager::DiscoveryManager(QObject *parent)
    \brief Constructs the DiscoveryManager.

    \a parent is the optional QObject parent.

    Sets up internal signal connections between DiscoveryCore and this manager.
*/
DiscoveryManager::DiscoveryManager(QObject *parent)
    : QObject{parent}
{
    qDebug() << "DiscoveryManager: initialized";

    // Connect DiscoveryCore's internal signals to the public interface of the manager
    connect(&m_discoveryCore, &DiscoveryCore::success,
            this, &DiscoveryManager::discoverySuccess);

    connect(&m_discoveryCore, &DiscoveryCore::error,
            this, &DiscoveryManager::discoveryFailed);
}

/*!
    \fn void DiscoveryManager::discover(const QString urlString)
    \brief Begins the discovery process using the given \a urlString.

    This method initiates a network request to the provided URL string,
    attempting to retrieve and parse discovery metadata from a remote chat server.

    Upon success, the \l discoverySuccess signal is emitted with the resulting
    \l DiscoveryPayload. If an error occurs, the \l discoveryFailed signal is emitted
    with a description of the failure.

    \note Only one request is active at a time. Calling this while a previous
    request is ongoing will cancel the prior request.
*/
void DiscoveryManager::discover(const QString urlString)
{
    qDebug() << "DiscoveryManager: Starting discovery for" << urlString;
    QUrl url(urlString);
    m_discoveryCore.fetchServerMeta(url);
}

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
