#include "channelproxymodel.h"
#include "chatmessagemodel.h"

ChannelProxyModel::ChannelProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    setFilterRole(ChatMessageModel::ChannelRole);
    setDynamicSortFilter(true);
}

void ChannelProxyModel::setChannel(const QString &name)
{
    if (name != m_channel) {
        m_channel = name;
        invalidateFilter();
        emit channelChanged();
    }
}

QString ChannelProxyModel::channel() const
{
    return m_channel;
}

bool ChannelProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    const QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    QString rowChannel = index.data(ChatMessageModel::ChannelRole).toString();
    return rowChannel == m_channel;
}
