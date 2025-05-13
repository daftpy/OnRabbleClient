/*!
    \class AuthCore
    \inmodule OnRabbleClient
    \brief Handles the low-level OAuth2 logic for user authentication.

    AuthCore wraps the Qt OAuth2 framework to drive user authentication via the OAuth2 authorization code flow.
    It handles URL redirection, token acquisition, and error propagation. It is intended to be used
    internally by a higher-level authentication manager.

    \section1 Internal Members

    The following private members and slots are internal mechanisms used by AuthCore and not exposed
    to higher-level components:

    \b Private \b Variables
    \list
        \li \tt{m_authFlow (\l QOAuth2AuthorizationCodeFlow)} – Manages the OAuth2 grant flow and token state.
        \li \tt{m_replyHandler (\l QOAuthHttpServerReplyHandler)} – Listens on localhost for redirect responses.
        \li \tt{m_callback (\l AuthenticationCallback)} – Function to invoke when authentication completes or fails.
        \li \tt{m_networkManager (\l QNetworkAccessManager)} – Used to perform a simple health check before authentication begins.
    \endlist

    \b Internal \b Slots
    \list
        \li \tt{onAuthenticationUrlRequested()} – Emits a signal to show the login page in a browser.
        \li \tt{onGranted()} – Called when an access token is received successfully.
        \li \tt{onErrorOccurred()} – Called when OAuth2 encounters an error.
    \endlist
*/

#include "authcore.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>

/*!
    \fn AuthCore::AuthCore(QObject *parent)
    \brief Constructs the AuthCore instance.

    \a parent is the optional parent object.
*/
AuthCore::AuthCore(QObject *parent) : QObject{parent}
{
    qDebug() << "AuthCore: initialized";
}

/*!
    \fn void AuthCore::startAuthenticationFlow(const DiscoveryPayload &payload, AuthenticationCallback callback)
    \brief Starts the OAuth2 authentication code flow using the provided \a payload and \a callback.

    This configures OAuth URLs, sets up a localhost reply handler, and begins the login process.
*/
void AuthCore::startAuthenticationFlow(const DiscoveryPayload &payload, AuthenticationCallback callback)
{
    qDebug() << "Starting authentication flow for:" << payload.authEndpoint();

    m_replyHandler.reset();
    m_replyHandler = std::make_unique<QOAuthHttpServerReplyHandler>(1337, this);
    m_replyHandler->setCallbackPath("/callback");

    m_authFlow.setAuthorizationUrl(payload.authEndpoint());
    m_authFlow.setTokenUrl(payload.tokenEndpoint());
    m_authFlow.setClientIdentifier("ChatClient");
    m_authFlow.setRequestedScopeTokens({"openid"});
    m_authFlow.setReplyHandler(m_replyHandler.get());

    connect(&m_authFlow, &QOAuth2AuthorizationCodeFlow::granted, this, &AuthCore::onGranted, Qt::UniqueConnection);
    connect(&m_authFlow, &QOAuth2AuthorizationCodeFlow::serverReportedErrorOccurred, this, &AuthCore::onErrorOccurred, Qt::UniqueConnection);
    connect(&m_authFlow, &QOAuth2AuthorizationCodeFlow::authorizeWithBrowser, this, &AuthCore::onAuthenticationUrlRequested, Qt::UniqueConnection);

    m_callback = callback;
    m_authFlow.grant();
}

/*!
    \internal
    \fn void AuthCore::onAuthenticationUrlRequested(const QUrl &url)
    \brief Emits the authentication URL that should be opened in a WebEngineView.

    \a url is the auth_url from the authentication server.
*/
void AuthCore::onAuthenticationUrlRequested(const QUrl &url)
{
    qDebug() << "Authentication URL generated:" << url;
    emit urlReady(url);
}

/*!
    \internal
    \fn void AuthCore::onGranted()
    \brief Called when the OAuth2 flow successfully completes.

    Emits the token using the previously saved callback, then cleans up state.
*/
void AuthCore::onGranted()
{
    if (m_callback) {
        m_callback(m_authFlow.token(), QString());  // success, no error
        m_callback = nullptr;
    }
    m_replyHandler.reset();  // Clean up the HTTP handler
}

/*!
    \internal
    \fn void AuthCore::onErrorOccurred(const QString &error, const QString &errorDescription, const QUrl &uri)
    \brief Called when the OAuth2 flow encounters an error.

    The error is passed back through the callback.

    \a error is the type of error.
    \a errorDescription is a human-readable explanation.
    \a uri is the full URL from the server if available.
*/
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

/*!
    \fn void AuthCore::cancelAuthenticationFlow()
    \brief Cancels any in-progress authentication attempt and resets internal state.
*/
void AuthCore::cancelAuthenticationFlow()
{
    qDebug() << "Authentication flow canceled";

    if (m_replyHandler && m_replyHandler->isListening()) {
        m_replyHandler->close();
    }

    m_callback = nullptr;
    m_replyHandler.reset();
    m_authFlow.setToken(QString());
}

/*!
    \fn void AuthCore::checkHealth(const QUrl &url, HealthCheckCallback callback)
    \brief Pings the given \a url and calls \a callback with the result.

    Used to ensure the authentication server is reachable before launching the login flow.
*/
void AuthCore::checkHealth(const QUrl &url, HealthCheckCallback callback)
{
    QNetworkRequest request(url);
    QNetworkReply *reply = m_networkManager.get(request);

    connect(reply, &QNetworkReply::finished, this, [reply, callback]() {
        reply->deleteLater();

        if (reply->error() != QNetworkReply::NoError) {
            callback(false, reply->errorString());
            return;
        }

        int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        if (statusCode >= 200 && statusCode < 300) {
            callback(true, {});
        } else {
            callback(false, QString("Unexpected status code: %1").arg(statusCode));
        }
    });
}
