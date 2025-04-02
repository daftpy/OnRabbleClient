#include "discoverypayload.h"
#include <QDebug>

DiscoveryPayload::DiscoveryPayload(const QJsonObject &json)
{
    // Extract the values from the JSON
    m_serverName   = json.value("server_name").toString();
    m_authEndpoint = json.value("auth_url").toString();
    m_tokenEndpoint= json.value("token_url").toString();
    m_chatEndpoint = json.value("chat_url").toString();

    qDebug() << "Discovery payload: initialized payload for: " << m_serverName;
}

DiscoveryPayload::DiscoveryPayload(const QString &name, const QString &authEndpoint, const QString &tokenEndpoint, const QString chatEndpoint)
    : m_serverName(name), m_authEndpoint(authEndpoint), m_tokenEndpoint(tokenEndpoint), m_chatEndpoint(chatEndpoint)
{
    qDebug() << "Discovery payload: initialized discovery payload for: " << name;
}

QString DiscoveryPayload::serverName() const
{
    return m_serverName;
}

void DiscoveryPayload::setServerName(const QString &serverName)
{
    m_serverName = serverName;
}

QString DiscoveryPayload::authEndpoint() const
{
    return m_authEndpoint;
}

void DiscoveryPayload::setAuthEndpoint(const QString &endpoint)
{
    m_authEndpoint = endpoint;
}

QString DiscoveryPayload::tokenEndpoint() const
{
    return m_tokenEndpoint;
}

void DiscoveryPayload::setTokenEndpoint(const QString &endpoint)
{
    m_tokenEndpoint = endpoint;
}

QString DiscoveryPayload::chatEndpoint() const
{
    return m_chatEndpoint;
}

void DiscoveryPayload::setChatEndpoint(const QString &endpoint)
{
    m_chatEndpoint = endpoint;
}
