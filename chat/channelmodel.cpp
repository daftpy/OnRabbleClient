#include "channelmodel.h"

/*!
    \class ChannelModel
    \inmodule OnRabbleClient
    \brief Exposes a list of available public channels to QML and C++.

    \section1 Overview

    ChannelModel maintains a collection of \l ChannelPayload objects that represent public chat
    channels the user may join. This model is primarily used to populate views such as channel
    sidebars, dropdowns, or tab lists in the chat UI.

    The model supports bulk insertion of channels, retrieving metadata for a specific index,
    and complete clearing of the internal channel list.

    \div {class="internal"}
    \section2 Internal Members

    \b Private \b Variables
    \list
        \li \tt{m_channels (\l{QList}<\l{ChannelPayload}>)} – Holds all currently known channels received from the server.
    \endlist
    \enddiv

    \sa ChannelPayload
*/

/*!
    \fn ChannelModel::ChannelModel(QObject *parent)
    \brief Constructs an empty ChannelModel.

    This constructor is used to create the model instance, typically within a
    view model or controller class. It does not populate any data initially.

    \a parent is the optional QObject parent.
*/
ChannelModel::ChannelModel(QObject *parent)
    : QAbstractListModel(parent)
{}

/*!
    \fn int ChannelModel::rowCount(const QModelIndex &parent) const
    \brief Returns the number of channels in the model.

    \a parent is unused in this implementation because the model is flat.

    This function is used by view components to determine the number of entries to display.
*/
int ChannelModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_channels.size();
}

/*!
    \fn QVariant ChannelModel::data(const QModelIndex &index, int role) const
    \brief Returns the data at \a index for the given \a role.

    This includes channel ID, name, description, sort order, and the raw payload object.
    If the index is invalid, an invalid QVariant is returned.
*/
QVariant ChannelModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_channels.size())
        return QVariant();

    const auto &channel = m_channels.at(index.row());
    switch (role) {
    case IdRole:         return channel.id();
    case NameRole:       return channel.name();
    case DescriptionRole:return channel.description();
    case SortOrderRole:  return channel.sortOrder();
    case PayloadRole:    return QVariant::fromValue(channel);
    }

    return QVariant();
}

/*!
    \fn QHash<int, QByteArray> ChannelModel::roleNames() const
    \brief Returns a mapping of role enums to QML-visible role names.

    These names are used when binding model roles in QML views.
*/
QHash<int, QByteArray> ChannelModel::roleNames() const
{
    return {
        { IdRole, "id" },
        { NameRole, "name" },
        { DescriptionRole, "description" },
        { SortOrderRole, "sortOrder" },
        { PayloadRole, "payload" }
    };
}

/*!
    \fn void ChannelModel::clear()
    \brief Removes all channels from the model.

    This resets the model, clearing all internal data and notifying any attached views.
*/
void ChannelModel::clear()
{
    beginResetModel();
    m_channels.clear();
    endResetModel();
}

/*!
    \fn ChannelPayload ChannelModel::get(int index) const
    \brief Returns the channel at \a index as a \l ChannelPayload.

    If the index is out of bounds, an empty \l ChannelPayload is returned.
*/
ChannelPayload ChannelModel::get(int index) const
{
    if (index >= 0 && index < m_channels.size())
        return m_channels.at(index);
    return ChannelPayload(); // return empty
}

/*!
    \fn void ChannelModel::addChannels(const QList<ChannelPayload> &channels)
    \brief Appends the given list of \a channels to the model.

    This emits the appropriate signals for attached views to update accordingly.
*/
void ChannelModel::addChannels(const QList<ChannelPayload> &channels)
{
    if (channels.isEmpty()) return;
    beginInsertRows(QModelIndex(), m_channels.size(), m_channels.size() + channels.size() - 1);
    m_channels.append(channels);
    endInsertRows();
}
