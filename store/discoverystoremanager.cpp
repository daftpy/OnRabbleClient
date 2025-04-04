#include "discoverystoremanager.h"
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>

// Initialize the static singleton instance pointer to null
DiscoveryStoreManager* DiscoveryStoreManager::s_instance = nullptr;

// Assigns singleton instance and loads any existing payloads from disk
DiscoveryStoreManager::DiscoveryStoreManager(QObject *parent)
    : QObject(parent)
{
    // Ensure only one instance exists
    if (!s_instance) {
        s_instance = this;
    }

    // Attempt to load previously stored payloads
    load();
}

// Adds a new payload to memory and persists the updated list to disk
void DiscoveryStoreManager::addPayload(const DiscoveryPayload &payload)
{
    m_payloads.append(payload);
    save();
}

// Returns the current in-memory list of stored discovery payloads
QVector<DiscoveryPayload> DiscoveryStoreManager::payloads() const
{
    return m_payloads;
}

// Removes a payload by matching server name, and saves the updated list
bool DiscoveryStoreManager::removePayloadByName(const QString &serverName)
{
    // Try to find a payload with the matching name
    auto it = std::remove_if(m_payloads.begin(), m_payloads.end(), [&](const DiscoveryPayload &p) {
        return p.serverName() == serverName;
    });

    // If found, erase and save the updated list
    if (it != m_payloads.end()) {
        m_payloads.erase(it, m_payloads.end());
        return save();
    }

    // No match found; nothing removed
    return false;
}

// Loads discovery payloads from the disk
bool DiscoveryStoreManager::load()
{
    QFile file(m_storagePath);

    // If the file doesn't exist, treat as an empty list
    if (!file.exists()) return true;

    // Try to open file for reading
    if (!file.open(QIODevice::ReadOnly)) return false;

    QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
    file.close();

    // Expect a JSON array format
    if (!doc.isArray()) return false;

    // Parse array of payloads
    QJsonArray array = doc.array();
    m_payloads.clear();

    for (const QJsonValue &val : array) {
        if (val.isObject()) {
            m_payloads.append(DiscoveryPayload(val.toObject()));
        }
    }

    return true;
}

// Saves the current list of discovery payload
bool DiscoveryStoreManager::save()
{
    QJsonArray array;

    for (const auto &payload : m_payloads) {
        QJsonObject obj;
        obj["server_name"] = payload.serverName();
        obj["server_id"]   = payload.serverId();
        obj["auth_url"]    = payload.authEndpoint();
        obj["token_url"]   = payload.tokenEndpoint();
        obj["chat_url"]    = payload.chatEndpoint();
        array.append(obj);
    }

    QFile file(m_storagePath);

    // Try to open file for writing
    if (!file.open(QIODevice::WriteOnly)) return false;

    QJsonDocument doc(array);
    file.write(doc.toJson());
    file.close();

    return true;
}

// Returns the singleton instance (creating it if necessary)
DiscoveryStoreManager *DiscoveryStoreManager::getInstance()
{
    if (!s_instance) {
        s_instance = new DiscoveryStoreManager();
    }
    return s_instance;
}
