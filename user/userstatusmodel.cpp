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
    case UsernameRole:      return user.username();
    case IdRole:            return user.id();
    case IsConnectedRole:   return user.isConnected();
    case PayloadRole:       return QVariant::fromValue(user);
    }

    return QVariant();
}

QHash<int, QByteArray> UserStatusModel::roleNames() const
{
    return {
        { UsernameRole, "username" },
        { IdRole, "id" },
        { IsConnectedRole, "isConnected" },
        { PayloadRole, "payload" }
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

void UserStatusModel::updateOrAddUser(const UserStatusPayload &payload)
{
    for (int i = 0; i < m_users.size(); i++)
    {
        if (m_users[i].id() == payload.id())
        {
            m_users[i] = payload;
            emit dataChanged(index(i), index(i));
            return;
        }
    }

    // If user is not found, add user
    addUser(payload);
    return;
}

void UserStatusModel::addUser(const UserStatusPayload &user)
{
    beginInsertRows(QModelIndex(), m_users.size(), m_users.size());
    m_users.append(user);
    endInsertRows();
}
