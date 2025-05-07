#ifndef DISCOVERYPAYLOAD_H
#define DISCOVERYPAYLOAD_H
#include <QMetaType>
#include <QString>
#include <QJsonObject>
#include <QtQml/qqmlregistration.h>

/* DiscoveryPayload declares the structure of the response received from a succesful discovery process
 * where the auth, token, and chat endpoints, as well as a server name, are retrieved from a
 * discovery endpoint.
*/

class DiscoveryPayload
{
    Q_GADGET
    Q_PROPERTY(QString serverName READ serverName WRITE setServerName)
    Q_PROPERTY(QString serverId READ serverId WRITE setServerId)
    Q_PROPERTY(QString authEndpoint READ authEndpoint WRITE setAuthEndpoint)
    Q_PROPERTY(QString tokenEndpoint READ tokenEndpoint WRITE setTokenEndpoint)
    Q_PROPERTY(QString chatEndpoint READ chatEndpoint WRITE setChatEndpoint)
    Q_PROPERTY(QString healthUrl READ healthUrl WRITE setHealthUrl)
    QML_VALUE_TYPE(discoveryPayload)
public:
    DiscoveryPayload() = default;

    explicit DiscoveryPayload(const QJsonObject &json);

    DiscoveryPayload(const QString &name, const QString &serverId, const QString &authEndpoint,
                     const QString &tokenEndpoint, const QString chatEndpoint, const QString healthUrl);

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
    QString m_serverName;
    QString m_serverId;
    QString m_authEndpoint;
    QString m_tokenEndpoint;
    QString m_chatEndpoint;
    QString m_healthUrl;
};

Q_DECLARE_METATYPE(DiscoveryPayload)

#endif // DISCOVERYPAYLOAD_H
