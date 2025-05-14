#include "chatmessagemodel.h"
#include <QDebug>

/*!
    \class ChatMessageModel
    \inmodule OnRabbleClient
    \brief Exposes a list of chat messages in a given channel.

    \section1 Overview

    ChatMessageModel is a QAbstractListModel that holds a collection of \l ChatMessagePayload
    objects. It provides role-based access to properties like message ID, sender, channel,
    and authored time. This model is typically used in combination with
    \l ChannelMessageProxyModel to display only messages relevant to a specific channel.

    Messages can be appended from either C++ or QML, and the model supports full clearing
    and retrieval of the raw backing list.

    \div {class="internal"}
    \section2 Internal Members

    \b Private \b Variables
    \list
        \li \tt{m_messages (\l QList<ChatMessagePayload>)} – Internal list of all messages stored in reverse-chronological order.
    \endlist
    \enddiv

    \sa ChannelMessageProxyModel, ChatMessagePayload
*/

/*!
    \fn ChatMessageModel::ChatMessageModel(QObject *parent)
    \brief Constructs an empty ChatMessageModel instance.

    \a parent is the optional QObject parent.
*/
ChatMessageModel::ChatMessageModel(QObject *parent)
    : QAbstractListModel(parent)
{}

/*!
    \fn int ChatMessageModel::rowCount(const QModelIndex &parent) const
    \brief Returns the number of messages in the model.

    This is used by QML views to determine how many items to render.
    \a parent is unused for flat list models.
*/
int ChatMessageModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_messages.count();
}

/*!
    \fn QVariant ChatMessageModel::data(const QModelIndex &index, int role) const
    \brief Returns the data for the message at \a index for a given \a role.

    This includes properties such as ID, username, channel name, and message body.
    Returns an invalid QVariant if the index is out of range.
*/
QVariant ChatMessageModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_messages.size())
        return QVariant();

    const auto &msg = m_messages.at(index.row());
    switch (role) {
    case IdRole: return msg.id();
    case CacheIdRole: return msg.cacheId();
    case OwnerIdRole: return msg.ownerId();
    case UsernameRole: return msg.username();
    case ChannelRole: return msg.channel();
    case MessageRole: return msg.message();
    case AuthoredAtRole: return msg.authoredAt();
    }

    return QVariant();
}

/*!
    \fn QHash<int, QByteArray> ChatMessageModel::roleNames() const
    \brief Returns a mapping from role values to their corresponding QML role names.

    This is used by QML delegates to access message properties directly in views.
*/
QHash<int, QByteArray> ChatMessageModel::roleNames() const
{
    return {
        { IdRole, "id" },
        { CacheIdRole, "cacheId" },
        { OwnerIdRole, "ownerId" },
        { UsernameRole, "username" },
        { ChannelRole, "channel" },
        { MessageRole, "message" },
        { AuthoredAtRole, "authoredAt" }
    };
}

/*!
    \fn void ChatMessageModel::appendMessage(const ChatMessagePayload &msg)
    \brief Appends a new chat message \a msg to the top of the model.

    This inserts the message in reverse-chronological order (most recent first).
*/
void ChatMessageModel::appendMessage(const ChatMessagePayload &msg)
{
    qDebug() << "[ChatMessageModel] Appending message from" << msg.username()
    << "in channel" << msg.channel() << ":" << msg.message();

    beginInsertRows(QModelIndex(), 0, 0);
    m_messages.prepend(msg);
    endInsertRows();
}

/*!
    \fn void ChatMessageModel::clear()
    \brief Removes all messages from the model.

    This is typically used during disconnection or channel switching.
*/
void ChatMessageModel::clear()
{
    beginResetModel();
    m_messages.clear();
    endResetModel();
}

/*!
    \fn const QList<ChatMessagePayload>& ChatMessageModel::messages() const
    \brief Returns a const reference to the internal message list.

    This allows controller classes to inspect or iterate over the full model contents.
*/
const QList<ChatMessagePayload> &ChatMessageModel::messages() const
{
    return m_messages;
}
