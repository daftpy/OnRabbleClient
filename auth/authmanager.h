#ifndef AUTHMANAGER_H
#define AUTHMANAGER_H

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

    // Begins the authorization process using the provided discovery payload
    Q_INVOKABLE void beginAuthorization(const DiscoveryPayload &payload);

    // Cancels the ongoing authorization process
    Q_INVOKABLE void cancelAuthorization();

    // Returns true if authenticated
    bool isAuthenticated() const;

signals:
    // Emitted when an authorization error occurs
    void authorizationErrorOccurred(const QString &error);

    // Emitted when authorization succeeds
    void authorizationSucceeded(const DiscoveryPayload &payload, const QString &accessToken);

    // Emitted when the authorization URL is ready to be shown
    void authorizationUrlAvailable(const QUrl &url);

private:
    void handleAuthorizationResult(const QString &token, const QString &error, const DiscoveryPayload &payload);

    AuthCore m_authCore;
    QString m_accessToken;
};

#endif // AUTHMANAGER_H
