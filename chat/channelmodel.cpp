#include "channelmodel.h"

ChannelModel::ChannelModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int ChannelModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_channels.size();
}

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

void ChannelModel::clear()
{
    beginResetModel();
    m_channels.clear();
    endResetModel();
}

ChannelPayload ChannelModel::get(int index) const
{
    if (index >= 0 && index < m_channels.size())
        return m_channels.at(index);
    return ChannelPayload(); // return empty
}

void ChannelModel::addChannels(const QList<ChannelPayload> &channels)
{
    if (channels.isEmpty()) return;
    beginInsertRows(QModelIndex(), m_channels.size(), m_channels.size() + channels.size() - 1);
    m_channels.append(channels);
    endInsertRows();
}
