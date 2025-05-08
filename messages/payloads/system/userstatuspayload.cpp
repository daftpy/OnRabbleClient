#include "userstatuspayload.h"

/*!
    \class UserStatusPayload
    \inmodule OnRabbleClient
    \brief Represents the online status of a single user.

    This payload is typically included in "connected_users" or "user_status" messages sent by the server.
*/

/*!
    \fn UserStatusPayload::UserStatusPayload(const QJsonObject &json)
    \brief Constructs a UserStatusPayload from a \a json object.

    Extracts the \c id, \c username, and \c status fields from the JSON structure.
*/
UserStatusPayload::UserStatusPayload(const QJsonObject &json)
{
    m_username = json.value("username").toString();
    m_id = json.value("id").toString();
    m_isConnected = json.value("status").toBool();
}

/*!
    \fn QString UserStatusPayload::username() const
    \brief Returns the user's username.
*/
QString UserStatusPayload::username() const {
    return m_username;
}

/*!
    \fn QString UserStatusPayload::id() const
    \brief Returns the unique identifier of the user.
*/
QString UserStatusPayload::id() const {
    return m_id;
}

/*!
    \fn bool UserStatusPayload::isConnected() const
    \brief Returns \c true if the user is currently online.
*/
bool UserStatusPayload::isConnected() const {
    return m_isConnected;
}
