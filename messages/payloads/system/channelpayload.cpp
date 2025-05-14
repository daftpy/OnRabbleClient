#include "channelpayload.h"
#include <QDebug>

/*!
    \class ChannelPayload
    \inmodule OnRabbleClient
    \brief Represents the metadata for a public chat channel.

    ChannelPayload is a simple value type used to represent individual public channels.
    It provides identifiers, descriptions, and sorting metadata. Instances can be
    constructed from JSON objects and are used to populate channel-related models.

    \sa ChannelModel
*/

/*!
    \fn ChannelPayload::ChannelPayload(const QJsonObject &json)
    \brief Constructs a ChannelPayload by parsing a \a json object.

    Extracts values for \c id, \c name, \c description, and \c sort_order if present.
*/
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

/*!
    \property ChannelPayload::id
    \brief Returns the channel ID.
*/
int ChannelPayload::id() const
{
    return m_id;
}

/*!
    \fn void ChannelPayload::setId(int id)
    \brief Sets the channel ID to \a id.
*/
void ChannelPayload::setId(int id)
{
    if (m_id != id) m_id = id;
}

/*!
    \property ChannelPayload::name
    \brief Returns the name of the channel.
*/
QString ChannelPayload::name() const
{
    return m_name;
}

/*!
    \fn void ChannelPayload::setName(const QString &name)
    \brief Sets the name of the channel to \a name.
*/
void ChannelPayload::setName(const QString &name)
{
    if (m_name != name) m_name = name;
}

/*!
    \property ChannelPayload::description
    \brief Returns the description of the channel.
*/
QString ChannelPayload::description() const
{
    return m_description;
}

/*!
    \fn void ChannelPayload::setDescription(const QString &description)
    \brief Sets the channel description to \a description.
*/
void ChannelPayload::setDescription(const QString &description)
{
    if (m_description != description) m_description = description;
}

/*!
    \property ChannelPayload::sortOrder
    \brief Returns the sort order used to organize channels.
*/
int ChannelPayload::sortOrder() const
{
    return m_sortOrder;
}

/*!
    \fn void ChannelPayload::setSortOrder(int order)
    \brief Sets the channel's sort order to \a order.
*/
void ChannelPayload::setSortOrder(int order)
{
    if (m_sortOrder != order) m_sortOrder = order;
}

/*!
    \fn bool ChannelPayload::operator==(const ChannelPayload &other) const
    \brief Returns true if this payload represents the same channel as \a other.
*/
bool ChannelPayload::operator==(const ChannelPayload &other) const
{
    return m_id == other.m_id;
}

/*!
    \fn bool ChannelPayload::operator<(const ChannelPayload &other) const
    \brief Returns true if this channel should be ordered before \a other based on sort order.
*/
bool ChannelPayload::operator<(const ChannelPayload &other) const
{
    return m_sortOrder < other.m_sortOrder;
}
