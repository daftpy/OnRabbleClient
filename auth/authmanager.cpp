#include "authmanager.h"
#include "store/discoverystoremanager.h"
#include <QDebug>

AuthManager::AuthManager(QObject *parent)
    : QObject{parent}
{
    qDebug() << "AuthManager: initialized";

    // Connect to the AuthCore's signal that emits when the authorization URL is generated.
    // This URL is intended to be loaded in a WebEngineView for user interaction.
    connect(&m_authCore, &AuthCore::authorizationUrlGenerated,
            this, &AuthManager::authorizationUrlAvailable);
}

// Begins the authorization process using the given discovery payload.
// The result will be returned asynchronously via signals.
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

    // Delegate the authorization to AuthCore, and provide a callback
    // m_authCore.startAuthorizationFlow(payload, [this, payload](const QString &token, const QString &error) {
    //     handleAuthorizationResult(token, error, payload);
    // });
}

// Cancels any in-progress authorization attempt.
void AuthManager::cancelAuthorization()
{
    qDebug() << "AuthManager: cancelAuthorization()";
    m_authCore.cancelAuthorizationFlow();
}

// Returns true if an access token is available.
bool AuthManager::isAuthenticated() const
{
    return !m_accessToken.isEmpty();
}

// Handles the outcome of the authorization attempt.
// Emits either the success or error signal based on the result.
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
