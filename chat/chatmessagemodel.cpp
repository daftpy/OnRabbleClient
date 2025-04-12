#include "chatmessagemodel.h"
#include <QDebug>

ChatMessageModel::ChatMessageModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int ChatMessageModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_messages.count();
}

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

QHash<int, QByteArray> ChatMessageModel::roleNames() const
{
    return {
            {IdRole, "id"},
            {CacheIdRole, "cacheId"},
            {OwnerIdRole, "ownerId"},
            {UsernameRole, "username"},
            {ChannelRole, "channel"},
            {MessageRole, "message"},
            {AuthoredAtRole, "authoredAt"},
            };
}

void ChatMessageModel::appendMessage(const ChatMessagePayload &msg)
{
    qDebug() << "[ChatMessageModel] Appending message from" << msg.username()
    << "in channel" << msg.channel()
    << ":" << msg.message();

    beginInsertRows(QModelIndex(), m_messages.size(), m_messages.size());
    m_messages.append(msg);
    endInsertRows();
}

void ChatMessageModel::clear()
{
    beginResetModel();
    m_messages.clear();
    endResetModel();
}

const QList<ChatMessagePayload> &ChatMessageModel::messages() const
{
    return m_messages;
}
