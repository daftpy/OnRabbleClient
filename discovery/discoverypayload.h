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
    Q_PROPERTY(QString authEndpoint READ authEndpoint WRITE setAuthEndpoint)
    Q_PROPERTY(QString tokenEndpoint READ tokenEndpoint WRITE setTokenEndpoint)
    Q_PROPERTY(QString chatEndpoint READ chatEndpoint WRITE setChatEndpoint)
    QML_VALUE_TYPE(discoveryPayload)
public:
    DiscoveryPayload() = default;
    explicit DiscoveryPayload(const QJsonObject &json);
    DiscoveryPayload(const QString &name, const QString &authEndpoint, const QString &tokenEndpoint, const QString chatEndpoint);

    QString serverName() const;
    void setServerName(const QString &serverName);

    QString authEndpoint() const;
    void setAuthEndpoint(const QString &endpoint);

    QString tokenEndpoint() const;
    void setTokenEndpoint(const QString &endpoint);

    QString chatEndpoint() const;
    void setChatEndpoint(const QString &endpoint);

private:
    QString m_serverName;
    QString m_authEndpoint;
    QString m_tokenEndpoint;
    QString m_chatEndpoint;
};

Q_DECLARE_METATYPE(DiscoveryPayload)

#endif // DISCOVERYPAYLOAD_H
