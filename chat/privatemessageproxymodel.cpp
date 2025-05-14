#include "privatemessageproxymodel.h"
#include "privatemessagemodel.h"

/*!
    \class PrivateMessageProxyModel
    \inmodule OnRabbleClient
    \brief Filters private messages exchanged between two specific users.

    \section1 Overview

    PrivateMessageProxyModel sits on top of \l PrivateMessageModel and filters its contents
    to only expose messages where either:

    \list
        \li The current user is the sender and the target user is the recipient
        \li Or the current user is the recipient and the target user is the sender
    \endlist

    This allows QML views to display private chat threads without managing filtering logic.

    \div {class="internal"}
    \section2 Internal Members

    \b Private \b Variables
    \list
        \li \tt{m_myUserId (\l QString)} — ID of the current authenticated user
        \li \tt{m_targetUserId (\l QString)} — ID of the user on the other end of the conversation
    \endlist
    \enddiv

    \sa PrivateMessageModel
*/

/*!
    \fn PrivateMessageProxyModel::PrivateMessageProxyModel(QObject *parent)
    \brief Constructs a new proxy model for filtering private messages.
*/
PrivateMessageProxyModel::PrivateMessageProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent) {}

/*!
    \fn QString PrivateMessageProxyModel::myUserId() const
    \brief Returns the ID of the current user.
*/
QString PrivateMessageProxyModel::myUserId() const
{
    return m_myUserId;
}

/*!
    \fn void PrivateMessageProxyModel::setMyUserId(const QString &id)
    \brief Sets the ID of the current user.

    Calling this triggers a re-evaluation of the filter.
*/
void PrivateMessageProxyModel::setMyUserId(const QString &id)
{
    if (m_myUserId != id) {
        m_myUserId = id;
        emit myUserIdChanged();
        invalidateFilter();
    }
}

/*!
    \fn QString PrivateMessageProxyModel::targetUserId() const
    \brief Returns the ID of the chat partner (target user).
*/
QString PrivateMessageProxyModel::targetUserId() const
{
    return m_targetUserId;
}

/*!
    \fn void PrivateMessageProxyModel::setTargetUserId(const QString &id)
    \brief Sets the ID of the user being chatted with.

    Calling this triggers a re-evaluation of the filter.
*/
void PrivateMessageProxyModel::setTargetUserId(const QString &id)
{
    if (m_targetUserId != id) {
        m_targetUserId = id;
        emit targetUserIdChanged();
        invalidateFilter();
    }
}

/*!
    \fn QVariantMap PrivateMessageProxyModel::get(int row) const
    \brief Returns a single row as a QVariantMap, useful for QML delegate access.

    \a row is the index in the proxy model. Returns an empty map if the index is invalid.
*/
QVariantMap PrivateMessageProxyModel::get(int row) const
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
    \fn bool PrivateMessageProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
    \brief Returns \c true if the message at \a sourceRow is between the current user and the target user.

    Both sent and received messages are accepted.
*/
bool PrivateMessageProxyModel::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    if (m_myUserId.isEmpty() || m_targetUserId.isEmpty())
        return false;

    const QModelIndex ownerIdIndex = sourceModel()->index(sourceRow, 0, sourceParent);
    const QModelIndex recipientIdIndex = sourceModel()->index(sourceRow, 0, sourceParent);

    QString ownerId = ownerIdIndex.data(PrivateMessageModel::OwnerIdRole).toString();
    QString recipientId = recipientIdIndex.data(PrivateMessageModel::RecipientIdRole).toString();

    return ( (ownerId == m_myUserId && recipientId == m_targetUserId) ||
            (ownerId == m_targetUserId && recipientId == m_myUserId) );
}
