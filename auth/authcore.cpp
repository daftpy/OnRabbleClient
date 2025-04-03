#include "authcore.h"
#include <QDebug>

AuthCore::AuthCore(QObject *parent) : QObject{parent}
{
    qDebug() << "AuthCore: initialized";
}

// Starts the OAuth2 authorization code flow using the provided payload and callback.
void AuthCore::startAuthorizationFlow(const DiscoveryPayload &payload, AuthorizationCallback callback)
{
    qDebug() << "Starting authorization flow for:" << payload.authEndpoint();

    // Ensure any previous reply handler is reset
    m_replyHandler.reset();
    m_replyHandler = std::make_unique<QOAuthHttpServerReplyHandler>(1337, this);
    m_replyHandler->setCallbackPath("/callback");

    // Configure OAuth2 endpoints and client info
    m_authFlow.setAuthorizationUrl(payload.authEndpoint());
    m_authFlow.setTokenUrl(payload.tokenEndpoint());
    m_authFlow.setClientIdentifier("ChatClient");
    m_authFlow.setRequestedScopeTokens({"openid"});
    m_authFlow.setReplyHandler(m_replyHandler.get());

    // Connect internal flow events to our slots
    connect(&m_authFlow, &QOAuth2AuthorizationCodeFlow::granted, this, &AuthCore::onGranted, Qt::UniqueConnection);
    connect(&m_authFlow, &QOAuth2AuthorizationCodeFlow::serverReportedErrorOccurred, this, &AuthCore::onErrorOccurred, Qt::UniqueConnection);
    connect(&m_authFlow, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, this, &AuthCore::onAuthorizationUrlRequested, Qt::UniqueConnection);

    // Save callback for completion or failure
    m_callback = callback;

    // Begin authorization
    m_authFlow.grant();
}

// Triggered when the authorization URL should be captured by the WebEngineView
void AuthCore::onAuthorizationUrlRequested(const QUrl &url)
{
    qDebug() << "Authorization URL generated:" << url;
    emit authorizationUrlGenerated(url);
}

// Called when the user has successfully authorized and we have a token.
void AuthCore::onGranted()
{
    if (m_callback) {
        m_callback(m_authFlow.token(), QString());  // success, no error
        m_callback = nullptr;
    }
    m_replyHandler.reset();  // Clean up the HTTP handler
}

// Called when an error occurred during the OAuth flow.
void AuthCore::onErrorOccurred(const QString &error, const QString &errorDescription, const QUrl &uri)
{
    QString fullError = QString("%1: %2 (More info: %3)").arg(error, errorDescription, uri.toString());
    qWarning() << "OAuth error:" << fullError;

    if (m_callback) {
        m_callback(QString(), fullError);  // no token, return error
        m_callback = nullptr;
    }
    m_replyHandler.reset();
}

// Cancels the flow in progress and resets internal state.
void AuthCore::cancelAuthorizationFlow()
{
    qDebug() << "Authorization flow canceled";

    // If listening, close the reply handler
    if (m_replyHandler && m_replyHandler->isListening()) {
        m_replyHandler->close(); // Ensure it stops listening before we reset
    }

    m_callback = nullptr;
    m_replyHandler.reset();
    m_authFlow.setToken(QString());
}

// Optional method to support custom redirect routing if using a URI scheme.
void AuthCore::handleRedirectedUrl(const QUrl &url)
{
    Q_UNUSED(url);
    // Implement later if needed (e.g. for QOAuthUriSchemeReplyHandler)
}
