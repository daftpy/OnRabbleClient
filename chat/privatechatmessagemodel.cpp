#include "privatechatmessagemodel.h"

PrivateChatMessageModel::PrivateChatMessageModel(QObject *parent)
    : QAbstractListModel(parent)
{
}

int PrivateChatMessageModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return m_messages.size();
}

QVariant PrivateChatMessageModel::data(const QModelIndex &index, int role) const
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

QHash<int, QByteArray> PrivateChatMessageModel::roleNames() const
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

void PrivateChatMessageModel::appendMessage(const PrivateChatMessagePayload &msg)
{
    beginInsertRows(QModelIndex(), 0, 0);
    m_messages.prepend(msg);
    endInsertRows();
}

void PrivateChatMessageModel::clear()
{
    beginResetModel();
    m_messages.clear();
    endResetModel();
}

const QList<PrivateChatMessagePayload> &PrivateChatMessageModel::messages() const
{
    return m_messages;
}
