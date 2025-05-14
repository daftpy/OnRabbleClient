#include "authmanager.h"
#include "store/discoverystoremanager.h"
#include <QDebug>

/*!
    \class AuthManager
    \inmodule OnRabbleClient
    \brief Manages user authentication and access token retrieval.

    AuthenticationManager orchestrates the authentication workflow using a DiscoveryPayload and AuthCore.
    It emits signals to notify QML or C++ components of key events during the authentication process,
    such as success, failure, or when the authentication URL is ready for display.

    \section1 Internal Members

    \div {class="internal"}
    \section2 Internal Members

        The following private member variables are used internally
        by AuthManager and are referenced here for developer clarity. Full documentation
        is available in the source file:

        \b Private \b Variables
        \list
            \li \tt{m_authCore (\l{AuthCore})} - Manages the low-level OAuth2 authentication code flow logic.
            \li \tt{m_authToken (\l{QString})} – Stores the current token retrieved during the authentication flow.
        \endlist
    \enddiv

    \sa AuthCore, AuthBrowserPage
*/

AuthManager::AuthManager(QObject *parent)
    : QObject{parent}
{
    qDebug() << "AuthManager: initialized";

    connect(&m_authCore, &AuthCore::urlReady,
            this, &AuthManager::authenticationUrlReady);
}

void AuthManager::startAuthentication(const DiscoveryPayload &payload)
{
    qDebug() << "AuthManager: startAuthentication()";

    QUrl healthUrl(payload.healthUrl());

    m_authCore.checkHealth(healthUrl, [this, payload](bool success, const QString &error) {
        if (!success) {
            qWarning() << "AuthManager: health check failed -" << error;
            emit authenticationError("Unable to contact authentication server: " + error);
            return;
        }

        qDebug() << "AuthManager: server healthy. Starting flow.";
        m_authCore.startAuthenticationFlow(payload, [this, payload](const QString &token, const QString &error) {
            handleAuthenticationResult(token, error, payload);
        });
    });
}

void AuthManager::cancelAuthentication()
{
    qDebug() << "AuthManager: cancelAuthentication()";
    m_authCore.cancelAuthenticationFlow();
}

bool AuthManager::isAuthenticated() const
{
    return !m_authToken.isEmpty();
}

void AuthManager::handleAuthenticationResult(const QString &token, const QString &error, const DiscoveryPayload &payload)
{
    if (!error.isEmpty()) {
        qWarning() << "AuthManager: authentication error -" << error;
        emit authenticationError(error);
        return;
    }

    m_authToken = token;
    qDebug() << "AuthManager: authentication succeeded. Token -" << token << "for" << payload.chatEndpoint();

    DiscoveryStoreManager::getInstance()->addPayload(payload);
    DiscoveryStoreManager::getInstance()->save();
    emit authenticationSuccess(payload, m_authToken);
}

/*!
    \fn void AuthManager::authenticationError(const QString &error)
    \brief Emitted when an error occurs during the authentication process.

    \a error contains a human-readable explanation of the failure.
*/

/*!
    \fn void AuthManager::authenticationSuccess(const DiscoveryPayload &payload, const QString &authToken)
    \brief Emitted when authentication completes successfully.

    \a payload is the discovery data used in the authentication.
    \a authToken is the token used to access chat services.
*/

/*!
    \fn void AuthManager::authenticationUrlReady(const QUrl &url)
    \brief Emitted when the authentication login URL is available.

    The \a url is intended to be loaded in a WebEngineView so the user can
    complete the login process. This signal originates from the internal AuthCore
    component and is emitted once a valid authentication flow has begun.

    \sa AuthBrowserPage, AuthCore
*/

