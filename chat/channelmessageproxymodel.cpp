#include "channelmessageproxymodel.h"
#include "chatmessagemodel.h"

/*!
    \class ChannelMessageProxyModel
    \inmodule OnRabbleClient
    \brief Filters chat messages by channel name using a QSortFilterProxyModel.

    \section1 Overview

    ChannelMessageProxyModel provides a filtered view over the \l ChatMessageModel,
    exposing only those messages that belong to a specified channel. It is commonly used
    in tabbed chat UIs or side-by-side channel panes to isolate conversations by topic.

    The proxy works by matching the \l{ChatMessageModel::ChannelRole} of each message
    against a user-specified channel string, which can be set from C++ or QML.

    \div {class="internal"}
    \section2 Internal Members

    \b Private \b Variables
    \list
        \li \tt{m_channel (\l QString)} – The name of the channel currently used to filter messages.
    \endlist
    \enddiv

    \sa ChannelPayload, ChatMessageModel
*/

/*!
    \fn ChannelMessageProxyModel::ChannelMessageProxyModel(QObject *parent)
    \brief Constructs a new proxy for filtering messages by channel.

    Sets the filter role to \l ChatMessageModel::ChannelRole and enables
    dynamic filtering behavior when the channel name changes.

    \a parent is the optional QObject parent.
*/
ChannelMessageProxyModel::ChannelMessageProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
    setFilterRole(ChatMessageModel::ChannelRole);
    setDynamicSortFilter(true);
}

/*!
    \fn void ChannelMessageProxyModel::setChannel(const QString &name)
    \brief Updates the channel filter string to \a name.

    This will trigger re-evaluation of the source model and emit
    \l channelChanged() if the name has changed.
*/
void ChannelMessageProxyModel::setChannel(const QString &name)
{
    if (name != m_channel) {
        m_channel = name;
        invalidateFilter();
        emit channelChanged();
    }
}

/*!
    \fn QString ChannelMessageProxyModel::channel() const
    \brief Returns the current channel name used for filtering.
*/
QString ChannelMessageProxyModel::channel() const
{
    return m_channel;
}

/*!
    \fn QVariantMap ChannelMessageProxyModel::get(int row) const
    \brief Returns all role data at proxy row \a row as a QVariantMap.

    This method maps the row index from the proxy to the source model,
    retrieves data for all roles, and returns the values as a QML-friendly map.

    Returns an empty map if the row is invalid.
*/
QVariantMap ChannelMessageProxyModel::get(int row) const
{
    QVariantMap map;
    if (row < 0 || row >= rowCount())
        return map;

    QAbstractItemModel *m = sourceModel();
    QModelIndex sourceIndex = mapToSource(index(row, 0));

    if (!sourceIndex.isValid())
        return map;

    for (int role : m->roleNames().keys()) {
        map[m->roleNames().value(role)] = m->data(sourceIndex, role);
    }

    return map;
}

/*!
    \reimp
    \brief Returns true if the message at \a sourceRow belongs to the current channel.

    This override implements the actual filtering logic by comparing the channel name
    of each source row against \l m_channel.
*/
bool ChannelMessageProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    const QModelIndex index = sourceModel()->index(sourceRow, 0, sourceParent);
    QString rowChannel = index.data(ChatMessageModel::ChannelRole).toString();
    return rowChannel == m_channel;
}
