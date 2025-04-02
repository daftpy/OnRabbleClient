#include "authmanager.h"
#include <QDebug>

AuthManager::AuthManager(QObject *parent) : QObject{parent}
{
    qDebug() << "AuthManager: initialized";
}

void AuthManager::authenticate(const DiscoveryPayload &payload)
{
    // Attempt authentication
    qDebug() << "AuthManager: initiating authentication";
    m_authCore.authenticate(payload, [this, payload](const QString &token, const QString error)
    {
        // Handle the auth response
        handleAuthResponse(token, error, payload);
    });
}

void AuthManager::handleAuthResponse(const QString &token, const QString &error, const DiscoveryPayload &payload)
{
    // Check for errors
    if (!error.isEmpty())
    {
        qWarning() << "AuthManager: error -" << error;
        emit authenticationError(error);
        return;
    }
    // Update the token and authentication status
    m_accessToken = token;

    // Emit the updates
    qDebug() << "AuthManager: authentication successful. Access token -" << token << "for" << payload.chatEndpoint();
    emit authenticated(payload, m_accessToken);
}

QString AuthManager::accessToken() const
{
    return m_accessToken;
}
