#include "discoverypayload.h"
#include <QDebug>

/*!
    \class DiscoveryPayload
    \inmodule OnRabbleClient
    \brief Represents server discovery data including endpoint URLs and metadata.

    DiscoveryPayload encapsulates the fields returned from a discovery server,
    such as the server name and key endpoint URLs for authentication and messaging.
*/

/*!
    \fn DiscoveryPayload::DiscoveryPayload(const QJsonObject &json)
    \brief Constructs a DiscoveryPayload from a JSON object.

    Extracts fields from \a json including server name, ID, and endpoint URLs.
*/
DiscoveryPayload::DiscoveryPayload(const QJsonObject &json)
{
    m_serverName    = json.value("server_name").toString();
    m_serverId      = json.value("server_id").toString();
    m_authEndpoint  = QString("https://") + json.value("auth_url").toString();
    m_tokenEndpoint = QString("https://") + json.value("token_url").toString();
    m_chatEndpoint  = json.value("chat_url").toString();
    m_healthUrl     = QString("https://") + json.value("health_url").toString();

    qDebug() << "Discovery payload: initialized payload for:" << m_serverName;
}

/*!
    \fn DiscoveryPayload::DiscoveryPayload(const QString &name, const QString &serverId, const QString &authEndpoint, const QString &tokenEndpoint, const QString chatEndpoint, const QString healthUrl)
    \brief Constructs a DiscoveryPayload with explicit values.

    \a name is the display name of the server.
    \a serverId is a unique identifier.
    \a authEndpoint is the authentication endpoint.
    \a tokenEndpoint is the URL for token exchange.
    \a chatEndpoint is the URL for WebSocket connection.
    \a healthUrl is the endpoint for authentication service health checks.
*/
DiscoveryPayload::DiscoveryPayload(const QString &name, const QString &serverId,
                                   const QString &authEndpoint, const QString &tokenEndpoint,
                                   const QString chatEndpoint, const QString healthUrl)
    : m_serverName(name), m_serverId(serverId), m_authEndpoint(authEndpoint),
    m_tokenEndpoint(tokenEndpoint), m_chatEndpoint(chatEndpoint), m_healthUrl(healthUrl)
{
    qDebug() << "Discovery payload: initialized discovery payload for:" << name;
}

/*!
    \fn QString DiscoveryPayload::serverName() const
    \brief Returns the user-facing name of the server.
*/
QString DiscoveryPayload::serverName() const
{
    return m_serverName;
}

/*!
    \fn void DiscoveryPayload::setServerName(const QString &serverName)
    \brief Sets the server display name.

    \a serverName is the new name to set.
*/
void DiscoveryPayload::setServerName(const QString &serverName)
{
    m_serverName = serverName;
}

/*!
    \fn QString DiscoveryPayload::serverId() const
    \brief Returns the internal identifier for the server.
*/
QString DiscoveryPayload::serverId() const
{
    return m_serverId;
}

/*!
    \fn void DiscoveryPayload::setServerId(const QString &serverId)
    \brief Sets the server's unique identifier.

    \a serverId is the new ID to assign.
*/
void DiscoveryPayload::setServerId(const QString &serverId)
{
    m_serverId = serverId;
}

/*!
    \fn QString DiscoveryPayload::authEndpoint() const
    \brief Returns the authentication endpoint URL.
*/
QString DiscoveryPayload::authEndpoint() const
{
    return m_authEndpoint;
}

/*!
    \fn void DiscoveryPayload::setAuthEndpoint(const QString &endpoint)
    \brief Sets the authentication \a endpoint.

    \a endpoint is the authentication new URL to set.
*/
void DiscoveryPayload::setAuthEndpoint(const QString &endpoint)
{
    m_authEndpoint = endpoint;
}

/*!
    \fn QString DiscoveryPayload::tokenEndpoint() const
    \brief Returns the token exchange endpoint URL.
*/
QString DiscoveryPayload::tokenEndpoint() const
{
    return m_tokenEndpoint;
}

/*!
    \fn void DiscoveryPayload::setTokenEndpoint(const QString &endpoint)
    \brief Sets the token \a endpoint URL.

    \a endpoint is the new URL to set.
*/
void DiscoveryPayload::setTokenEndpoint(const QString &endpoint)
{
    m_tokenEndpoint = endpoint;
}

/*!
    \fn QString DiscoveryPayload::chatEndpoint() const
    \brief Returns the WebSocket chat endpoint URL.
*/
QString DiscoveryPayload::chatEndpoint() const
{
    return m_chatEndpoint;
}

/*!
    \fn void DiscoveryPayload::setChatEndpoint(const QString &endpoint)
    \brief Sets the new WebSocket chat \a endpoint.

    \a endpoint is the new URL to set.
*/
void DiscoveryPayload::setChatEndpoint(const QString &endpoint)
{
    m_chatEndpoint = endpoint;
}

/*!
    \fn QString DiscoveryPayload::healthUrl() const
    \brief Returns the health check endpoint URL.
*/
QString DiscoveryPayload::healthUrl() const
{
    return m_healthUrl;
}

/*!
    \fn void DiscoveryPayload::setHealthUrl(const QString &url)
    \brief Sets the health check URL.

    \a url is the new URL to set.
*/
void DiscoveryPayload::setHealthUrl(const QString &url)
{
    m_healthUrl = url;
}
