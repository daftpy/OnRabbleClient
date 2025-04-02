#include "authcore.h"
#include <QDesktopServices>
#include <QCoreApplication>
#include <QDebug>

AuthCore::AuthCore(QObject *parent) : QObject{parent}
{
    qDebug() << "AuthCore: initialized";
}

void AuthCore::authenticate(const DiscoveryPayload &payload, TokenCallback callback)
{
    qDebug() << "Authenticating against" << payload.authEndpoint();

    // Reset the reply handler
    m_replyHandler.reset();
    // Create a new reply handler
    m_replyHandler = std::make_unique<QOAuthHttpServerReplyHandler>(1337, this);

    // Create the callback path
    m_replyHandler->setCallbackPath("/callback");

    // Set the auth and token endpoints
    m_authFlow.setAuthorizationUrl(payload.authEndpoint());
    m_authFlow.setAccessTokenUrl(payload.tokenEndpoint());
    m_authFlow.setClientIdentifier("ChatClient");
    m_authFlow.setScope(QStringLiteral("openid"));
    m_authFlow.setReplyHandler(m_replyHandler.get()); // assign the reply handler

    // Connect the signals and slots
    connect(&m_authFlow, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, this, &AuthCore::startAuthentication, Qt::UniqueConnection);
    connect(&m_authFlow, &QOAuth2AuthorizationCodeFlow::granted, this, &AuthCore::handleGranted, Qt::UniqueConnection);
    connect(&m_authFlow, &QOAuth2AuthorizationCodeFlow::error,this, &AuthCore::handleOAuthError, Qt::UniqueConnection);

    // Store the callback for later use
    m_callback = callback;

    // Start the process
    m_authFlow.grant();
}

void AuthCore::startAuthentication(const QUrl &url)
{
    QDesktopServices::openUrl(url);
}

void AuthCore::handleGranted()
{
    m_callback(m_authFlow.token(), QString());
    m_replyHandler.reset();
}

void AuthCore::handleOAuthError(const QString &error, const QString &errorDescription, const QUrl &uri)
{
    // Create a full error message
    QString fullError = QString("%1: %2 (More info: %3)").arg(error).arg(errorDescription).arg(uri.toString());
    qWarning() << "OAuth error:" << fullError;

    // Call the stored callback with an empty token and the error message
    if (m_callback) {
        m_callback(QString(), fullError);
        m_callback = nullptr;
    }

    // Optionally, reset or clean up the reply handler
    m_replyHandler.reset();
}
