#ifndef USERSTATUSPAYLOAD_H
#define USERSTATUSPAYLOAD_H

#include <QString>
#include <QJsonObject>
#include <QtQml/qqmlregistration.h>

/**
 * @brief The UserStatusPayload class represents a user in the connected users list.
 *
 * It is typically sent by the server in a "connected_users" or "user_status" message.
 */
class UserStatusPayload
{
    Q_GADGET

    Q_PROPERTY(QString username READ username CONSTANT)  ///< The user's display or login name
    Q_PROPERTY(QString id READ id CONSTANT)              ///< Unique identifier for the user
    Q_PROPERTY(bool isConnected READ isConnected CONSTANT) ///< Whether the user is currently connected

    QML_VALUE_TYPE(userStatusPayload)

public:
    UserStatusPayload() = default;

    /**
     * @brief Constructs a UserStatusPayload from a QJsonObject.
     * @param json The JSON object containing user fields.
     */
    explicit UserStatusPayload(const QJsonObject &json);

    QString username() const { return m_username; }
    QString id() const { return m_id; }
    bool isConnected() const { return m_isConnected; }

private:
    QString m_username;
    QString m_id;
    bool m_isConnected = false;
};

Q_DECLARE_METATYPE(UserStatusPayload)

#endif // USERSTATUSPAYLOAD_H
