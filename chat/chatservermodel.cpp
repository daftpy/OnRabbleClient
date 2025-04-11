#include "chatservermodel.h"

ChatServerModel::ChatServerModel(QObject *parent)
    : QAbstractListModel(parent)
{}

int ChatServerModel::rowCount(const QModelIndex &parent) const
{
    // Only return data for the root index; this is a flat list.
    return parent.isValid() ? 0 : m_entries.size();
}

QVariant ChatServerModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid()) return QVariant();

    const ChatServerEntry &e = m_entries.at(index.row());
    switch (role) {
    case PayloadRole: return QVariant::fromValue(e.m_payload);
    case ManagerRole: return QVariant::fromValue(e.m_chatClientManager);
    default: return QVariant();
    }
}

QHash<int, QByteArray> ChatServerModel::roleNames() const
{
    // Maps internal role IDs to role names for use in QML
    return {
        {PayloadRole, "payload"},
        {ManagerRole, "chatClientManager"}
    };
}

void ChatServerModel::openChatWindoow(const DiscoveryPayload &payload, const QString &token)
{
    const int row = indexOfServer(payload.serverName());

    // Always create a new ChatClientManager for the connection
    auto *mgr = new ChatClientManager(payload, token, this);
    mgr->connectToServer();

    if (row != -1) {
        // Replace existing entry (remove then re-insert)
        beginRemoveRows({}, row, row);
        delete m_entries[row].m_chatClientManager;
        m_entries.removeAt(row);
        endRemoveRows();
    }

    // Insert new entry at the end of the model
    const int newRow = m_entries.size();
    beginInsertRows({}, newRow, newRow);
    m_entries.push_back({payload, mgr});
    endInsertRows();
}

void ChatServerModel::closeAt(int row)
{
    if (row < 0 || row >= m_entries.size()) return;

    // Remove and delete the specified entry
    beginRemoveRows({}, row, row);
    delete m_entries[row].m_chatClientManager;
    m_entries.removeAt(row);
    endRemoveRows();
}

int ChatServerModel::indexOfServer(const QString &name) const
{
    // Search for server by name
    for (int i = 0; i < m_entries.size(); ++i)
        if (m_entries[i].m_payload.serverName() == name)
            return i;
    return -1;
}
