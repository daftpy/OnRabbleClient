#ifndef USERSTATUSPAYLOAD_H
#define USERSTATUSPAYLOAD_H

#include <QString>
#include <QJsonObject>
#include <QtQml/qqmlregistration.h>

// Represents a connected user's status as received from the server.
class UserStatusPayload
{
    Q_GADGET

    Q_PROPERTY(QString username READ username CONSTANT)     // Display or login name of the user
    Q_PROPERTY(QString id READ id CONSTANT)                 // Unique user identifier
    Q_PROPERTY(bool isConnected READ isConnected CONSTANT)  // True if the user is currently online

    QML_VALUE_TYPE(userStatusPayload)

public:
    UserStatusPayload() = default;
    explicit UserStatusPayload(const QJsonObject &json); // Constructs from JSON payload

    QString username() const;
    QString id() const;
    bool isConnected() const;

private:
    QString m_username;         // The users username
    QString m_id;               // The users unique ID
    bool m_isConnected = false; // Derived from "status" (true if connected)
};

Q_DECLARE_METATYPE(UserStatusPayload)

#endif // USERSTATUSPAYLOAD_H
