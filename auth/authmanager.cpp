#include "authmanager.h"
#include "store/discoverystoremanager.h"
#include <QDebug>

/*!
    \class AuthManager
    \inmodule OnRabbleClient
    \brief Manages user authorization and access token retrieval.

    AuthManager orchestrates the authorization workflow using a DiscoveryPayload and AuthCore.
    It emits signals to notify QML or C++ components of key events during the authentication process,
    such as success, failure, or when the authorization URL is ready for display.

    \section1 Internal Members

    The following private member variables and functions are used internally by AuthManager and
    are referenced here for clarity. Documentation available in source code:

    \b Private \b Variables
    \list
        \li \b m_accessToken (\l QString) – Stores the current access token retrieved during the auth flow.
                               This token is non-empty only after a successful authorization.
    \endlist
*/

/*!
    \fn AuthManager::AuthManager(QObject *parent)
    \brief Constructs an AuthManager and connects to internal authorization signals.

    \a parent is the optional QObject parent.
*/
AuthManager::AuthManager(QObject *parent)
    : QObject{parent}
{
    qDebug() << "AuthManager: initialized";

    // Connect to the AuthCore's signal that emits when the authorization URL is generated.
    // This URL is intended to be loaded in a WebEngineView for user interaction.
    connect(&m_authCore, &AuthCore::authorizationUrlGenerated,
            this, &AuthManager::authorizationUrlAvailable);
}

/*!
    \fn void AuthManager::beginAuthorization(const DiscoveryPayload &payload)
    \brief Starts the authorization process using the given \a payload.

    Performs a health check on the authorization server before launching the auth flow.
    Emits \c authorizationSucceeded or \c authorizationErrorOccurred based on the result.
*/
void AuthManager::beginAuthorization(const DiscoveryPayload &payload)
{
    qDebug() << "AuthManager: beginAuthorization()";

    // Temp health check
    QUrl healthUrl(payload.healthUrl());

    // Ask AuthCore to perform the health check
    m_authCore.checkHealth(healthUrl, [this, payload](bool success, const QString &error) {
        if (!success) {
            qWarning() << "AuthManager: Keycloak health check failed -" << error;
            emit authorizationErrorOccurred("Unable to contact authorization server: " + error);
            return;
        }

        qDebug() << "AuthManager: Keycloak is healthy. Proceeding with auth.";
        m_authCore.startAuthorizationFlow(payload, [this, payload](const QString &token, const QString &error) {
            handleAuthorizationResult(token, error, payload);
        });
    });
}

/*!
    \fn void AuthManager::cancelAuthorization()
    \brief Cancels any ongoing authorization attempt.
*/
void AuthManager::cancelAuthorization()
{
    qDebug() << "AuthManager: cancelAuthorization()";
    m_authCore.cancelAuthorizationFlow();
}


bool AuthManager::isAuthenticated() const
{
    return !m_accessToken.isEmpty();
}

/*!
    \fn void AuthManager::handleAuthorizationResult(const QString &token, const QString &error, const DiscoveryPayload &payload)
    \brief Handles the result of the authorization attempt.

    Emits \c authorizationSucceeded if successful, otherwise emits \c authorizationErrorOccurred.

    \a token is the access token retrieved, or empty if authorization failed.
    \a error is the error message if one occurred.
    \a payload is the discovery data used for the authorization.
*/
void AuthManager::handleAuthorizationResult(const QString &token, const QString &error, const DiscoveryPayload &payload)
{
    if (!error.isEmpty()) {
        qWarning() << "AuthManager: authorization error -" << error;
        emit authorizationErrorOccurred(error);
        return;
    }

    // Save the token and notify listeners of successful authentication
    m_accessToken = token;
    qDebug() << "AuthManager: authorization succeeded. Access token -" << token << "for" << payload.chatEndpoint();

    DiscoveryStoreManager::getInstance()->addPayload(payload);
    DiscoveryStoreManager::getInstance()->save();
    emit authorizationSucceeded(payload, m_accessToken);
}

/*---------------------------- Signals ----------------------------*/
/*!
    \fn void AuthManager::authorizationErrorOccurred(const QString &error)
    \brief Emitted when an error occurs during the authorization process.

    \a error contains a human-readable explanation of what went wrong.
*/

/*!
    \fn void AuthManager::authorizationSucceeded(const DiscoveryPayload &payload, const QString &accessToken)
    \brief Emitted when authorization completes successfully.

    \a payload contains the discovery data used in the authentication.
    \a accessToken is the retrieved token for accessing authenticated services.
*/

/*!
    \fn void AuthManager::authorizationUrlAvailable(const QUrl &url)
    \brief Emitted when the authorization URL is ready to be shown to the user.

    \a url is the OAuth2 or Keycloak login page that should be loaded in a WebEngineView.
*/
