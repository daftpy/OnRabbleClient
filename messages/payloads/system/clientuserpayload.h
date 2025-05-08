#ifndef CLIENTUSERPAYLOAD_H
#define CLIENTUSERPAYLOAD_H

#include <QString>
#include <QStringList>
#include <QVariantMap>
#include <QtQml/qqmlregistration.h>

// Represents an authenticated user as parsed from JWT claims.
class ClientUserPayload
{
    Q_GADGET

    Q_PROPERTY(QString id READ id CONSTANT)             // Unique user ID from "sub" claim
    Q_PROPERTY(QString username READ username CONSTANT) // Preferred username from "preferred_username"
    Q_PROPERTY(QString email READ email CONSTANT)       // Email address from "email" claim (optional)
    Q_PROPERTY(QString fullName READ fullName CONSTANT) // Full name from "name" claim
    Q_PROPERTY(QStringList roles READ roles CONSTANT)   // Roles from "realm_access.roles"
    Q_PROPERTY(bool isValid READ isValid CONSTANT)      // True if ID and username are valid

    QML_VALUE_TYPE(user)

public:
    ClientUserPayload() = default;
    explicit ClientUserPayload(const QVariantMap &claims);

    QString id() const;
    QString username() const;
    QString email() const;
    QString fullName() const;
    QStringList roles() const;
    bool isValid() const;
    bool hasRole(const QString &role) const;

    void reset(const QVariantMap &claims);

private:
    void parseClaims(const QVariantMap &claims); // Parses JWT fields

    QString m_id;         // "sub" – unique identifier for the user
    QString m_username;   // "preferred_username" – login or display username
    QString m_email;      // "email" – optional email address
    QString m_fullName;   // "name" – full display name
    QStringList m_roles;  // "realm_access.roles" – assigned roles (e.g., admin, user)
};

Q_DECLARE_METATYPE(ClientUserPayload)

#endif // CLIENTUSERPAYLOAD_H
