#include "userstatuspayload.h"

UserStatusPayload::UserStatusPayload(const QJsonObject &json)
{
    m_username = json.value("username").toString();
    m_id = json.value("id").toString();
    m_isConnected = json.value("status").toBool();
}
