#ifndef CLIENTUSERPAYLOAD_H
#define CLIENTUSERPAYLOAD_H

#include <QString>
#include <QStringList>
#include <QVariantMap>
#include <QtQml/qqmlregistration.h>

/**
 * @brief The ClientUserPayload class represents an authenticated user based on JWT claims.
 *
 * This class parses and stores identity and role information from a JWT token payload.
 * It can be used to access the current user's ID, username, email, and roles.
 * Intended for use in a client-facing chat application.
 */
class ClientUserPayload
{
    Q_GADGET

    Q_PROPERTY(QString id READ id CONSTANT)                  ///< Unique user identifier (typically the "sub" claim)
    Q_PROPERTY(QString username READ username CONSTANT)      ///< Preferred username (from "preferred_username")
    Q_PROPERTY(QString email READ email CONSTANT)            ///< Email address (optional)
    Q_PROPERTY(QString fullName READ fullName CONSTANT)      ///< Full display name (from "name")
    Q_PROPERTY(QStringList roles READ roles CONSTANT)        ///< List of assigned roles (from "realm_access.roles")
    Q_PROPERTY(bool isValid READ isValid CONSTANT)           ///< True if payload has required identity claims

    QML_VALUE_TYPE(user)

public:
    /**
     * @brief Constructs an empty, invalid ClientUserPayload.
     */
    ClientUserPayload() = default;

    /**
     * @brief Constructs a ClientUserPayload from a JWT claim map.
     * @param claims A QVariantMap containing parsed JWT claims.
     */
    explicit ClientUserPayload(const QVariantMap &claims);

    /**
     * @brief Returns the unique user ID.
     * @return User ID string.
     */
    QString id() const;

    /**
     * @brief Returns the username.
     * @return Preferred username string.
     */
    QString username() const;

    /**
     * @brief Returns the email address.
     * @return Email string (may be empty if not provided).
     */
    QString email() const;

    /**
     * @brief Returns the full name of the user.
     * @return Full name string.
     */
    QString fullName() const;

    /**
     * @brief Returns the list of user roles.
     * @return QStringList of role names.
     */
    QStringList roles() const;

    /**
     * @brief Checks if the payload contains valid user data.
     * @return True if user ID and username are both present.
     */
    bool isValid() const;

    /**
     * @brief Checks whether the user has a specific role.
     * @param role The name of the role to check.
     * @return True if the role is found in the role list.
     */
    bool hasRole(const QString &role) const;

    /**
     * @brief Resets the payload state with new claims.
     * @param claims A new set of JWT claims to parse.
     */
    void reset(const QVariantMap &claims);

private:
    /**
     * @brief Parses identity and role information from a claims map.
     * This is used internally by both the constructor and reset method.
     * @param claims JWT claim map.
     */
    void parseClaims(const QVariantMap &claims);

    QString m_id;          ///< Unique ID from "sub"
    QString m_username;    ///< Username from "preferred_username"
    QString m_email;       ///< Email from "email"
    QString m_fullName;    ///< Full name from "name"
    QStringList m_roles;   ///< Roles from "realm_access.roles"
};

#endif // CLIENTUSERPAYLOAD_H
