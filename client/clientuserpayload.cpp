#include "clientuserpayload.h"
#include <QDebug>

ClientUserPayload::ClientUserPayload(const QVariantMap &claims)
{
    m_id = claims.value("sub").toString();
    m_username = claims.value("preferred_username").toString();
    m_email = claims.value("email").toString();
    m_fullName = claims.value("name").toString();

    // Handle realm_access.roles if present
    const QVariantMap realmAccess = claims.value("realm_access").toMap();
    const QVariantList roles = realmAccess.value("roles").toList();
    for (const QVariant &role : roles) {
        m_roles.append(role.toString());
    }

    qDebug() << "[ClientUserPayload] Parsed JWT:";
    qDebug() << " • id:" << m_id;
    qDebug() << " • username:" << m_username;
    qDebug() << " • email:" << m_email;
    qDebug() << " • fullName:" << m_fullName;
    qDebug() << " • roles:" << m_roles;
}

QString ClientUserPayload::id() const
{
    return m_id;
}

QString ClientUserPayload::username() const
{
    return m_username;
}

QString ClientUserPayload::email() const
{
    return m_email;
}

QString ClientUserPayload::fullName() const
{
    return m_fullName;
}

QStringList ClientUserPayload::roles() const
{
    return m_roles;
}

bool ClientUserPayload::hasRole(const QString &role) const
{
    return m_roles.contains(role, Qt::CaseInsensitive);
}
