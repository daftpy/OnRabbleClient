#ifndef DISCOVERYPAYLOAD_H
#define DISCOVERYPAYLOAD_H

#include <QMetaType>
#include <QString>
#include <QJsonObject>
#include <QtQml/qqmlregistration.h>

// Represents the server configuration returned during a discovery request,
// including endpoint URLs and display information.
class DiscoveryPayload
{
    Q_GADGET
    Q_PROPERTY(QString serverName READ serverName WRITE setServerName)          // Display name for the server
    Q_PROPERTY(QString serverId READ serverId WRITE setServerId)                // Unique server identifier
    Q_PROPERTY(QString authEndpoint READ authEndpoint WRITE setAuthEndpoint)    // URL for authentication
    Q_PROPERTY(QString tokenEndpoint READ tokenEndpoint WRITE setTokenEndpoint) // URL to exchange code for token
    Q_PROPERTY(QString chatEndpoint READ chatEndpoint WRITE setChatEndpoint)    // URL for WebSocket connection
    Q_PROPERTY(QString healthUrl READ healthUrl WRITE setHealthUrl)             // Healthcheck endpoint
    QML_VALUE_TYPE(discoveryPayload)

public:
    DiscoveryPayload() = default; // Default constructor

    // Constructs from a JSON object
    explicit DiscoveryPayload(const QJsonObject &json);

    // Constructs from individual fields
    DiscoveryPayload(const QString &name, const QString &serverId,
                     const QString &authEndpoint, const QString &tokenEndpoint,
                     const QString chatEndpoint, const QString healthUrl);

    QString serverName() const;
    void setServerName(const QString &serverName);

    QString serverId() const;
    void setServerId(const QString &serverId);

    QString authEndpoint() const;
    void setAuthEndpoint(const QString &endpoint);

    QString tokenEndpoint() const;
    void setTokenEndpoint(const QString &endpoint);

    QString chatEndpoint() const;
    void setChatEndpoint(const QString &endpoint);

    QString healthUrl() const;
    void setHealthUrl(const QString &url);

private:
    QString m_serverName;       // Server name
    QString m_serverId;         // Unique server Id
    QString m_authEndpoint;     // Server authentication endpoint
    QString m_tokenEndpoint;    // Server token exchange endpoint
    QString m_chatEndpoint;     // Chat websocket endpoint
    QString m_healthUrl;        // Health check endpoint
};

Q_DECLARE_METATYPE(DiscoveryPayload)

#endif // DISCOVERYPAYLOAD_H
