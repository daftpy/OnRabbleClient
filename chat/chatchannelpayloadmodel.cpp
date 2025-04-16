#include "chatchannelpayloadmodel.h"

ChatChannelPayloadModel::ChatChannelPayloadModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int ChatChannelPayloadModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_channels.size();
}

QVariant ChatChannelPayloadModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_channels.size())
        return QVariant();

    const auto &channel = m_channels.at(index.row());
    switch (role) {
    case IdRole:         return channel.id();
    case NameRole:       return channel.name();
    case DescriptionRole:return channel.description();
    case SortOrderRole:  return channel.sortOrder();
    }

    return QVariant();
}

QHash<int, QByteArray> ChatChannelPayloadModel::roleNames() const
{
    return {
        { IdRole, "id" },
        { NameRole, "name" },
        { DescriptionRole, "description" },
        { SortOrderRole, "sortOrder" }
    };
}

void ChatChannelPayloadModel::clear()
{
    beginResetModel();
    m_channels.clear();
    endResetModel();
}

ChannelPayload ChatChannelPayloadModel::get(int index) const
{
    if (index >= 0 && index < m_channels.size())
        return m_channels.at(index);
    return ChannelPayload(); // return empty
}

void ChatChannelPayloadModel::addChannels(const QList<ChannelPayload> &channels)
{
    if (channels.isEmpty()) return;
    beginInsertRows(QModelIndex(), m_channels.size(), m_channels.size() + channels.size() - 1);
    m_channels.append(channels);
    endInsertRows();
}
