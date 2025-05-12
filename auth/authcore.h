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

// AuthCore manages the low-level OAuth2 authorization code flow logic.
// It encapsulates token exchange, redirect handling, and signal forwarding for UI interaction.
class AuthCore : public QObject
{
    Q_OBJECT

public:
    using HealthCheckCallback = std::function<void(bool success, const QString &error)>;
    // Callback type to return either a token or an error string.
    using AuthorizationCallback = std::function<void(const QString &token, const QString &error)>;

    explicit AuthCore(QObject *parent = nullptr);
    ~AuthCore() = default;

    // Starts the authorization flow using the provided discovery payload.
    void startAuthorizationFlow(const DiscoveryPayload &payload, AuthorizationCallback callback);

    // Cancels the ongoing authorization attempt and clears state.
    void cancelAuthorizationFlow();

    // Checks the health of the keycloak endpoint before starting authorization
    void checkHealth(const QUrl &url, HealthCheckCallback callback);

signals:
    // Emitted when an authorization URL is generated and should be shown to the user.
    void authorizationUrlGenerated(const QUrl &url);

private slots:
    // Internal slot called when an authorization URL needs to be displayed.
    void onAuthorizationUrlRequested(const QUrl &url);

    // Internal slot triggered when access is successfully granted.
    void onGranted();

    // Internal slot triggered when an error occurs in the OAuth flow.
    void onErrorOccurred(const QString &error, const QString &errorDescription, const QUrl &uri);

private:
    QOAuth2AuthorizationCodeFlow m_authFlow;  // Handles OAuth protocol logic.
    std::unique_ptr<QOAuthHttpServerReplyHandler> m_replyHandler;  // Handles localhost redirects.
    AuthorizationCallback m_callback;  // Stores the callback for authorization result.
    QNetworkAccessManager m_networkManager;
};

#endif // AUTHCORE_H
