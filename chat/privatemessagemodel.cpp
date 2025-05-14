#include "privatemessagemodel.h"

/*!
    \class PrivateMessageModel
    \inmodule OnRabbleClient
    \internal
    \brief Stores all private chat messages and provides the source for filtering.

    \section1 Overview

    PrivateMessageModel is a \l QAbstractListModel that holds a list of \l PrivateChatMessagePayload
    objects, representing one-on-one direct messages between users. It is not exposed directly to QML;
    instead, it is consumed internally by \l PrivateMessageProxyModel, which filters messages by user
    and is exposed to the UI through the \l ClientManager.

    The model supports prepending new messages, clearing its contents, and retrieving the full
    internal list for use by message controllers or proxies.

    \div {class="internal"}
    \section2 Internal Members

    \b Private \b Variables
    \list
        \li \tt{m_messages (\l QList<PrivateChatMessagePayload>)} — Stores private messages in reverse-chronological order
    \endlist
    \enddiv

    \sa PrivateMessageProxyModel
*/


/*!
    \fn PrivateMessageModel::PrivateMessageModel(QObject *parent)
    \brief Constructs an empty private message model.

    \a parent is the optional QObject parent.
*/
PrivateMessageModel::PrivateMessageModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

/*!
    \fn int PrivateMessageModel::rowCount(const QModelIndex &parent) const
    \brief Returns the number of messages in the model.

    \a parent is unused in this flat list implementation.
*/
int PrivateMessageModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_messages.size();
}

/*!
    \fn QVariant PrivateMessageModel::data(const QModelIndex &index, int role) const
    \brief Returns the data for the message at \a index for the given \a role.

    This includes fields such as sender, recipient, and timestamp. Returns an invalid
    QVariant if the index is out of bounds.
*/
QVariant PrivateMessageModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_messages.size())
        return QVariant();

    const auto &msg = m_messages.at(index.row());

    switch (role) {
    case IdRole: return msg.id();
    case OwnerIdRole: return msg.ownerId();
    case UsernameRole: return msg.username();
    case RecipientIdRole: return msg.recipientId();
    case RecipientRole: return msg.recipient();
    case MessageRole: return msg.message();
    case AuthoredAtRole: return msg.authoredAt();
    default: return QVariant();
    }
}

/*!
    \fn QHash<int, QByteArray> PrivateMessageModel::roleNames() const
    \brief Returns a mapping from role IDs to QML role names.

    This allows QML views to bind to message properties like \c username, \c message, etc.
*/
QHash<int, QByteArray> PrivateMessageModel::roleNames() const
{
    return {
        {IdRole, "id"},
        {OwnerIdRole, "ownerId"},
        {UsernameRole, "username"},
        {RecipientIdRole, "recipientId"},
        {RecipientRole, "recipient"},
        {MessageRole, "message"},
        {AuthoredAtRole, "authoredAt"}
    };
}

/*!
    \fn void PrivateMessageModel::appendMessage(const PrivateChatMessagePayload &msg)
    \brief Prepends a private message \a msg to the model.

    New messages appear at the top of the list.
*/
void PrivateMessageModel::appendMessage(const PrivateChatMessagePayload &msg)
{
    beginInsertRows(QModelIndex(), 0, 0);
    m_messages.prepend(msg);
    endInsertRows();
}

/*!
    \fn void PrivateMessageModel::clear()
    \brief Clears all private messages from the model.
*/
void PrivateMessageModel::clear()
{
    beginResetModel();
    m_messages.clear();
    endResetModel();
}

/*!
    \fn const QList<PrivateChatMessagePayload> &PrivateMessageModel::messages() const
    \brief Returns a const reference to the internal message list.
*/
const QList<PrivateChatMessagePayload> &PrivateMessageModel::messages() const
{
    return m_messages;
}
