#include "clientuserpayload.h"
#include <QDebug>

/*!
    \class ClientUserPayload
    \inmodule OnRabbleClient
    \brief Represents the identity of the authenticated user based on JWT claims.

    This class stores decoded user information, such as user ID, username, email, and roles,
    extracted from a JWT payload. It is typically used in QML to check user identity and roles.
*/

/*!
    \fn ClientUserPayload::ClientUserPayload(const QVariantMap &claims)
    \brief Constructs a ClientUserPayload from a parsed JWT claim map.

    \a claims is the QVariantMap containing the decoded claims.
*/
ClientUserPayload::ClientUserPayload(const QVariantMap &claims)
{
    parseClaims(claims);
}

/*!
    \internal
    \brief Parses identity fields and role information from the JWT claims.

    Called by the constructor and \c reset().
    \a claims is a QVariantMap decoded from the JWT payload.
*/
void ClientUserPayload::parseClaims(const QVariantMap &claims)
{
    // Clear all internal fields in case this is a re-parse or reset
    m_id.clear();
    m_username.clear();
    m_email.clear();
    m_fullName.clear();
    m_roles.clear();

    // If the claims map is empty (parsing failed or token invalid), log and exit early
    if (claims.isEmpty()) {
        qWarning() << "[ClientUserPayload] Empty or invalid claims.";
        return;
    }

    // Extract standard user identity fields from the JWT claims
    m_id = claims.value("sub").toString();                        // Unique user ID
    m_username = claims.value("preferred_username").toString();   // Username used in chat
    m_email = claims.value("email").toString();                   // Optional email
    m_fullName = claims.value("name").toString();                 // Optional full name

    // If critical identifiers are missing, abort parsing to avoid a half-valid user
    if (m_id.isEmpty() || m_username.isEmpty()) {
        qWarning() << "[ClientUserPayload] Missing critical user fields (sub or preferred_username).";
        return;
    }

    // Extract user roles (e.g., admin, moderator) from realm_access.roles
    const QVariantMap realmAccess = claims.value("realm_access").toMap();
    const QVariantList roles = realmAccess.value("roles").toList();
    for (const QVariant &role : roles) {
        m_roles.append(role.toString());
    }

    // Log the fully parsed user payload
    qDebug() << "[ClientUserPayload] Parsed JWT:";
    qDebug() << " • id:" << m_id;
    qDebug() << " • username:" << m_username;
    qDebug() << " • email:" << m_email;
    qDebug() << " • fullName:" << m_fullName;
    qDebug() << " • roles:" << m_roles;
}

/*!
    \fn QString ClientUserPayload::id() const
    \brief Returns the unique user ID ("sub" claim).
*/
QString ClientUserPayload::id() const
{
    return m_id;
}

/*!
    \fn QString ClientUserPayload::username() const
    \brief Returns the preferred username.
*/
QString ClientUserPayload::username() const
{
    return m_username;
}

/*!
    \fn QString ClientUserPayload::email() const
    \brief Returns the email address associated with the user.
*/
QString ClientUserPayload::email() const {
    return m_email;
}

/*!
    \fn QString ClientUserPayload::fullName() const
    \brief Returns the user's full display name.
*/
QString ClientUserPayload::fullName() const {
    return m_fullName;
}

/*!
    \fn QStringList ClientUserPayload::roles() const
    \brief Returns the list of roles assigned to the user.
*/
QStringList ClientUserPayload::roles() const {
    return m_roles;
}

/*!
    \fn bool ClientUserPayload::isValid() const
    \brief Returns \c true if the payload contains valid identity data (ID and username).
*/
bool ClientUserPayload::isValid() const
{
    return !m_id.isEmpty() && !m_username.isEmpty();
}

/*!
    \fn bool ClientUserPayload::hasRole(const QString &role) const
    \brief Returns \c true if the user has the specified \a role.

    Case-insensitive comparison is used.
*/
bool ClientUserPayload::hasRole(const QString &role) const
{
    return m_roles.contains(role, Qt::CaseInsensitive);
}

/*!
    \fn void ClientUserPayload::reset(const QVariantMap &claims)
    \brief Re-parses the internal state using new JWT claims.

    \a claims is the new set of decoded JWT fields.
*/
void ClientUserPayload::reset(const QVariantMap &claims)
{
    parseClaims(claims);
}
