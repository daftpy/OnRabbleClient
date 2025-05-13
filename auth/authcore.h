#ifndef AUTHCORE_H
#define AUTHCORE_H

#include <QObject>
#include <QOAuth2AuthorizationCodeFlow>
#include <QOAuthHttpServerReplyHandler>
#include <QNetworkAccessManager>
#include <QString>
#include <functional>
#include <memory>
#include "messages/payloads/system/discoverypayload.h"

// AuthCore manages the low-level OAuth2 authentication code flow logic.
// It encapsulates token exchange, redirect handling, and signal forwarding for UI interaction.
class AuthCore : public QObject
{
    Q_OBJECT

public:
    using HealthCheckCallback = std::function<void(bool success, const QString &error)>;
    using AuthenticationCallback = std::function<void(const QString &token, const QString &error)>;

    explicit AuthCore(QObject *parent = nullptr);
    ~AuthCore() = default;

    // Starts the authentication flow using the provided discovery payload.
    void startAuthenticationFlow(const DiscoveryPayload &payload, AuthenticationCallback callback);

    // Cancels the ongoing authentication attempt and clears state.
    void cancelAuthenticationFlow();

    // Checks the health of the Keycloak endpoint before starting authentication
    void checkHealth(const QUrl &url, HealthCheckCallback callback);

signals:
    // Emitted when an authentication URL is generated and should be shown to the user.
    void urlReady(const QUrl &url);

private slots:
    void onAuthenticationUrlRequested(const QUrl &url);
    void onGranted();
    void onErrorOccurred(const QString &error, const QString &errorDescription, const QUrl &uri);

private:
    QOAuth2AuthorizationCodeFlow m_authFlow;
    std::unique_ptr<QOAuthHttpServerReplyHandler> m_replyHandler;
    AuthenticationCallback m_callback;
    QNetworkAccessManager m_networkManager;
};

#endif // AUTHCORE_H
