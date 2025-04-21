#include "privatechatmessageproxymodel.h"
#include "privatechatmessagemodel.h"

PrivateChatMessageProxyModel::PrivateChatMessageProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{
}

QString PrivateChatMessageProxyModel::myUserId() const
{
    return m_myUserId;
}

void PrivateChatMessageProxyModel::setMyUserId(const QString &id)
{
    if (m_myUserId != id) {
        m_myUserId = id;
        emit myUserIdChanged();
        invalidateFilter(); // <- Important to re-filter
    }
}

QString PrivateChatMessageProxyModel::targetUserId() const
{
    return m_targetUserId;
}

void PrivateChatMessageProxyModel::setTargetUserId(const QString &id)
{
    if (m_targetUserId != id) {
        m_targetUserId = id;
        emit targetUserIdChanged();
        invalidateFilter(); // <- Important to re-filter
    }
}

QVariantMap PrivateChatMessageProxyModel::get(int row) const
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

bool PrivateChatMessageProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (m_myUserId.isEmpty() || m_targetUserId.isEmpty())
        return false; // Don't show anything if IDs aren't properly set yet

    const QModelIndex ownerIdIndex = sourceModel()->index(sourceRow, 0, sourceParent);
    const QModelIndex recipientIdIndex = sourceModel()->index(sourceRow, 0, sourceParent);

    QString ownerId = ownerIdIndex.data(PrivateChatMessageModel::OwnerIdRole).toString();
    QString recipientId = recipientIdIndex.data(PrivateChatMessageModel::RecipientIdRole).toString();

    return ( (ownerId == m_myUserId && recipientId == m_targetUserId) ||
            (ownerId == m_targetUserId && recipientId == m_myUserId) );
}
