#include "discoverystoremanager.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDebug>

// Static instance initialized to nullptr
DiscoveryStoreManager* DiscoveryStoreManager::s_instance = nullptr;

DiscoveryStoreManager::DiscoveryStoreManager(QObject *parent)
    : QObject(parent)
{
    // Ensure only one instance is used (singleton pattern)
    if (!s_instance) {
        s_instance = this;
    }

    // Load stored payloads from disk
    load();
}

void DiscoveryStoreManager::addPayload(const DiscoveryPayload &payload)
{
    qDebug() << "DiscoveryStoreManager: Saving payload for" << payload.serverName();
    // Insert or overwrite payload by server ID
    m_payloads[payload.serverId()] = payload;

    // Persist changes to disk
    save();
}

DiscoveryPayload DiscoveryStoreManager::getPayloadById(const QString &serverId) const
{
    // Return the payload if it exists, otherwise return an empty one
    return m_payloads.value(serverId, {});
}

QVector<DiscoveryPayload> DiscoveryStoreManager::payloads() const
{
    // Return all values from the internal hash
    return m_payloads.values();
}

bool DiscoveryStoreManager::removePayloadById(const QString &serverId)
{
    // Remove the payload if it exists, then save
    if (m_payloads.remove(serverId) > 0) {
        return save();
    }

    return false;
}

bool DiscoveryStoreManager::load()
{
    QFile file(m_storagePath);

    // If the file doesn't exist, treat it like an empty store
    if (!file.exists()) return true;

    // Open the file for reading
    if (!file.open(QIODevice::ReadOnly)) return false;

    // Parse file contents as JSON
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    // Only accept an array format
    if (!doc.isArray()) return false;

    // Clear the current in-memory store
    QJsonArray array = doc.array();
    m_payloads.clear();

    // Add each payload from the array
    for (const QJsonValue &val : array) {
        if (val.isObject()) {
            DiscoveryPayload payload(val.toObject());
            m_payloads.insert(payload.serverId(), payload);
        }
    }

    return true;
}

bool DiscoveryStoreManager::save()
{
    QJsonArray array;

    // Serialize each payload to JSON
    for (const auto &payload : m_payloads) {
        QJsonObject obj;
        obj["server_name"] = payload.serverName();
        obj["server_id"]   = payload.serverId();
        obj["auth_url"]    = payload.authEndpoint();
        obj["token_url"]   = payload.tokenEndpoint();
        obj["chat_url"]    = payload.chatEndpoint();
        obj["health_url"]  = payload.healthUrl();
        array.append(obj);
    }

    QFile file(m_storagePath);

    // Write JSON to file
    if (!file.open(QIODevice::WriteOnly)) return false;

    QJsonDocument doc(array);
    file.write(doc.toJson());
    file.close();

    return true;
}

DiscoveryStoreManager *DiscoveryStoreManager::getInstance()
{
    // Lazy singleton initialization
    if (!s_instance) {
        s_instance = new DiscoveryStoreManager();
    }

    return s_instance;
}
