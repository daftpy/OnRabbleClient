#include "userstatusmodel.h"

UserStatusModel::UserStatusModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int UserStatusModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_users.size();
}

QVariant UserStatusModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_users.size())
        return QVariant();

    const auto &user = m_users.at(index.row());

    switch (role) {
    case UsernameRole:    return user.username();
    case IdRole:          return user.id();
    case IsConnectedRole: return user.isConnected();
    }

    return QVariant();
}

QHash<int, QByteArray> UserStatusModel::roleNames() const
{
    return {
        { UsernameRole, "username" },
        { IdRole, "id" },
        { IsConnectedRole, "isConnected" }
    };
}

void UserStatusModel::clear()
{
    beginResetModel();
    m_users.clear();
    endResetModel();
}

UserStatusPayload UserStatusModel::get(int index) const
{
    if (index >= 0 && index < m_users.size())
        return m_users.at(index);
    return UserStatusPayload(); // empty payload
}

void UserStatusModel::setUsers(const QList<UserStatusPayload> &users)
{
    beginResetModel();
    m_users = users;
    endResetModel();
}

void UserStatusModel::addUser(const UserStatusPayload &user)
{
    beginInsertRows(QModelIndex(), m_users.size(), m_users.size());
    m_users.append(user);
    endInsertRows();
}
