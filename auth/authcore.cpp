#include "authcore.h"
#include <QDesktopServices>
#include <QCoreApplication>
#include <QDebug>

AuthCore::AuthCore(QObject *parent) : QObject{parent}
{

}

void AuthCore::authenticate(const DiscoveryPayload &payload, TokenCallback callback)
{
    qDebug() << "Authenticating against" << payload.authEndpoint();

    // Create the reply handler
    m_replyHandler = std::make_unique<QOAuthHttpServerReplyHandler>(1337, this);

    // Create the callback path
    m_replyHandler->setCallbackPath(QStringLiteral("/callback_%1").arg(QCoreApplication::applicationPid()));

    // Set the auth and token endpoints
    m_authFlow.setAuthorizationUrl(payload.authEndpoint());
    m_authFlow.setAccessTokenUrl(payload.tokenEndpoint());
    m_authFlow.setClientIdentifier("ChatClient");
    m_authFlow.setScope(QStringLiteral("openid"));
    m_authFlow.setReplyHandler(m_replyHandler.get()); // assign the reply handler

    // Connect the signals and slots
    connect(&m_authFlow, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, this, &AuthCore::startAuthentication, Qt::UniqueConnection);
    connect(&m_authFlow, &QOAuth2AuthorizationCodeFlow::granted, this, &AuthCore::handleGranted, Qt::UniqueConnection);

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
}
