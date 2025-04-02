#ifndef AUTHCORE_H
#define AUTHCORE_H
#include <QObject>
#include <QOAuth2AuthorizationCodeFlow>
#include <QOAuthHttpServerReplyHandler>
#include <QString>
#include <functional>
#include <memory>
#include "discovery/discoverypayload.h"

class AuthCore : public QObject
{
public:
    // The callback type for authentication results
    using TokenCallback = std::function<void(const QString &token, const QString error)>;

    explicit AuthCore(QObject *parent = nullptr);
    ~AuthCore() = default;

    // Starts the authentication process with the given discovery payload
    void authenticate(const DiscoveryPayload &payload, TokenCallback callback);

private slots:
    void startAuthentication(const QUrl &url);
    void handleGranted();

private:
    QOAuth2AuthorizationCodeFlow m_authFlow;
    std::unique_ptr<QOAuthHttpServerReplyHandler> m_replyHandler{nullptr};
    TokenCallback m_callback;
};

#endif // AUTHCORE_H
