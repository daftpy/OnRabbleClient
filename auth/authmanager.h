#ifndef AUTHENTICATIONMANAGER_H
#define AUTHENTICATIONMANAGER_H

#include <QObject>
#include <QQmlEngine>
#include "authcore.h"
#include "messages/payloads/system/discoverypayload.h"

class AuthManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit AuthManager(QObject *parent = nullptr);
    ~AuthManager() = default;

    // Starts the authentication process using the provided discovery payload
    Q_INVOKABLE void startAuthentication(const DiscoveryPayload &payload);

    // Cancels any ongoing authentication attempt
    Q_INVOKABLE void cancelAuthentication();

    // Returns true if an authentication token has been acquired
    bool isAuthenticated() const;

signals:
    // Emitted when an error occurs during authentication
    void authenticationError(const QString &error);

    // Emitted when authentication completes successfully
    void authenticationSuccess(const DiscoveryPayload &payload, const QString &authToken);

    // Emitted when the authentication URL is ready to be shown to the user
    void authenticationUrlReady(const QUrl &url);

private:
    void handleAuthenticationResult(const QString &token, const QString &error, const DiscoveryPayload &payload);

    AuthCore m_authCore;
    QString m_authToken; // The authentication token used to access chat services
};

#endif // AUTHENTICATIONMANAGER_H
