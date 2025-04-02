#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H
#include <QObject>
#include <QQmlEngine>
#include "authcore.h"
#include "discoverypayload.h"

class AuthManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    explicit AuthManager(QObject *parent = nullptr);

    // Provides the authentication status
    bool isAuthenticated() const;

    // Provides the access token used to connect to the chatserver
    QString accessToken() const;

    // Starts the authentication process
    Q_INVOKABLE void authenticate(const DiscoveryPayload &payload);

signals:
    // Informs when an authentication error occurs
    void authenticationError(const QString &error);

    // Informs when the authentication process is done and a discovery payload was
    // used to succesfully collect an access token
    void authenticated(const DiscoveryPayload &payload, QString m_accessToken);

private:
    // Handles the authenticatin response
    void handleAuthResponse(const QString &token, const QString &error, const DiscoveryPayload &payload);

    AuthCore m_authCore;
    QString m_accessToken;
};

#endif // AUTHMANAGER_H
