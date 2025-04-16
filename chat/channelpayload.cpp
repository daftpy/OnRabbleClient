#include "channelpayload.h"
#include <QDebug>

ChannelPayload::ChannelPayload(const QJsonObject &json)
{
    if (json.contains("id") && json["id"].isDouble())
        m_id = json["id"].toInt();

    if (json.contains("name") && json["name"].isString())
        m_name = json["name"].toString();

    if (json.contains("description") && json["description"].isString())
        m_description = json["description"].toString();

    if (json.contains("sort_order") && json["sort_order"].isDouble())
        m_sortOrder = json["sort_order"].toInt();

    qDebug() << "ChannelPayload: initialized payload for channel:"
             << m_name << "with ID:" << m_id << "and sort order:" << m_sortOrder;
}

int ChannelPayload::id() const
{
    return m_id;
}

void ChannelPayload::setId(int id)
{
    if (m_id != id) m_id = id;
}

QString ChannelPayload::name() const
{
    return m_name;
}

void ChannelPayload::setName(const QString &name)
{
    if (m_name != name) m_name = name;
}

QString ChannelPayload::description() const
{
    return m_description;
}

void ChannelPayload::setDescription(const QString &description)
{
    if (m_description != description) m_description = description;
}

int ChannelPayload::sortOrder() const
{
    return m_sortOrder;
}

void ChannelPayload::setSortOrder(int order)
{
    if (m_sortOrder != order) m_sortOrder = order;
}

bool ChannelPayload::operator==(const ChannelPayload &other) const
{
    return m_id == other.m_id;
}

bool ChannelPayload::operator<(const ChannelPayload &other) const
{
    return m_sortOrder < other.m_sortOrder;
}
