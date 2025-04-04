#include "discoverypayloadlistmodel.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

DiscoveryPayloadListModel::DiscoveryPayloadListModel(QObject *parent)
    : QAbstractListModel(parent)
{
    load(); // Automatically load data on construction
}

QVariant DiscoveryPayloadListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return QVariant();

    switch (section) {
    case 0: return QStringLiteral("Server Name");
    case 1: return QStringLiteral("Server ID");
    case 2: return QStringLiteral("Auth Endpoint");
    case 3: return QStringLiteral("Token Endpoint");
    case 4: return QStringLiteral("Chat Endpoint");
    default: return QVariant();
    }
}

int DiscoveryPayloadListModel::rowCount(const QModelIndex &parent) const
{
    // List models only return count when parent is invalid
    if (parent.isValid())
        return 0;

    return m_payloads.size();
}

QVariant DiscoveryPayloadListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_payloads.size())
        return {};

    const auto &p = m_payloads.at(index.row());

    switch (role) {
    case ServerNameRole:    return p.serverName();
    case AuthEndpointRole:  return p.authEndpoint();
    case TokenEndpointRole: return p.tokenEndpoint();
    case ChatEndpointRole:  return p.chatEndpoint();
    case ServerIdRole:      return p.serverId();
    default: return {};
    }
}

QHash<int, QByteArray> DiscoveryPayloadListModel::roleNames() const
{
    // These role names are used in QML delegate bindings
    return {
        { ServerNameRole, "serverName" },
        { AuthEndpointRole, "authEndpoint" },
        { TokenEndpointRole, "tokenEndpoint" },
        { ChatEndpointRole, "chatEndpoint" },
        { ServerIdRole, "serverId" }
    };
}

void DiscoveryPayloadListModel::load()
{
    // Begin model reset to notify any views that data will be updated
    beginResetModel();

    // Clear current payloads
    m_payloads.clear();

    // Open the persistent JSON file containing discovery data
    QFile file("discovery_store.json");

    if (file.open(QIODevice::ReadOnly)) {
        // Parse the JSON content into a document
        QJsonDocument doc = QJsonDocument::fromJson(file.readAll());

        // If it's a valid array, convert each entry into a DiscoveryPayload
        if (doc.isArray()) {
            for (const auto &val : doc.array()) {
                if (val.isObject())
                    m_payloads.append(DiscoveryPayload(val.toObject()));
            }
        }

        file.close();
    }

    // End model reset and notify views that data is ready
    endResetModel();
}

void DiscoveryPayloadListModel::clear()
{
    beginResetModel();
    m_payloads.clear();
    endResetModel();
}

DiscoveryPayload DiscoveryPayloadListModel::get(int index) const
{
    if (index >= 0 && index < m_payloads.size())
        return m_payloads.at(index);
    return {};
}
