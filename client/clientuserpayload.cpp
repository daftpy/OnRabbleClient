#include "clientuserpayload.h"
#include <QDebug>

ClientUserPayload::ClientUserPayload(const QVariantMap &claims)
{
    parseClaims(claims);
}

void ClientUserPayload::parseClaims(const QVariantMap &claims)
{
    // Clear all internal fields in case this is a re-parse or reset.
    m_id.clear();
    m_username.clear();
    m_email.clear();
    m_fullName.clear();
    m_roles.clear();

    // If the claims map is empty (parsing failed or token invalid), log and exit early.
    if (claims.isEmpty()) {
        qWarning() << "[ClientUserPayload] Empty or invalid claims.";
        return;
    }

    // Extract standard user identity fields from the JWT claims.
    m_id = claims.value("sub").toString();                    // Unique user ID
    m_username = claims.value("preferred_username").toString(); // Username used in chat
    m_email = claims.value("email").toString();
    m_fullName = claims.value("name").toString();

    // If critical identifiers are missing, abort parsing to avoid a half-valid user.
    if (m_id.isEmpty() || m_username.isEmpty()) {
        qWarning() << "[ClientUserPayload] Missing critical user fields (sub or preferred_username).";
        return;
    }

    // Extract user roles (e.g., admin, moderator) from realm_access.roles.
    const QVariantMap realmAccess = claims.value("realm_access").toMap();
    const QVariantList roles = realmAccess.value("roles").toList();
    for (const QVariant &role : roles) {
        m_roles.append(role.toString());
    }

    // Log the fully parsed user payload.
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

QString ClientUserPayload::email() const {
    return m_email;
}

QString ClientUserPayload::fullName() const {
    return m_fullName;
}

QStringList ClientUserPayload::roles() const {
    return m_roles;
}

bool ClientUserPayload::isValid() const
{
    return !m_id.isEmpty() && !m_username.isEmpty();
}

bool ClientUserPayload::hasRole(const QString &role) const
{
    return m_roles.contains(role, Qt::CaseInsensitive);
}

void ClientUserPayload::reset(const QVariantMap &claims)
{
    parseClaims(claims);
}
