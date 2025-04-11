#ifndef CLIENTUSERPAYLOAD_H
#define CLIENTUSERPAYLOAD_H

#include <QString>
#include <QStringList>
#include <QJsonObject>
#include <QVariantMap>
#include <QtQml/qqmlregistration.h>

class ClientUserPayload
{
    Q_GADGET
    Q_PROPERTY(QString id READ id CONSTANT)
    Q_PROPERTY(QString username READ username CONSTANT)
    Q_PROPERTY(QString email READ email CONSTANT)
    Q_PROPERTY(QString fullName READ fullName CONSTANT)
    Q_PROPERTY(QStringList roles READ roles CONSTANT)
    QML_VALUE_TYPE(user)

public:
    ClientUserPayload() = default;
    explicit ClientUserPayload(const QVariantMap &claims);

    QString id() const;
    QString username() const;
    QString email() const;
    QString fullName() const;
    QStringList roles() const;

    bool hasRole(const QString &role) const;

private:
    QString m_id;
    QString m_username;
    QString m_email;
    QString m_fullName;
    QStringList m_roles;
};

#endif // CLIENTUSERPAYLOAD_H
