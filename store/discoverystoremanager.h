#ifndef DISCOVERYSTOREMANAGER_H
#define DISCOVERYSTOREMANAGER_H

#include <QObject>
#include <QQmlEngine>
#include <QHash>
#include "messages/payloads/discoverypayload.h"

/**
 * @brief DiscoveryStoreManager stores previously connected chat servers.
 *
 * Provides persistent storage for DiscoveryPayloads via JSON,
 * keyed by unique `server_id`. Ensures no duplicates are stored.
 * Can be accessed from both C++ (getInstance) and QML (singleton).
 */
class DiscoveryStoreManager : public QObject
{
    Q_OBJECT
    QML_SINGLETON
    QML_ELEMENT
public:
    /**
     * @brief Constructs the DiscoveryStoreManager and loads saved payloads.
     */
    explicit DiscoveryStoreManager(QObject *parent = nullptr);

    /**
     * @brief Adds or replaces a discovery payload by server ID and saves it.
     * @param payload The discovery payload to store.
     */
    Q_INVOKABLE void addPayload(const DiscoveryPayload &payload);

    /**
     * @brief Returns the payload matching a specific server ID.
     * @param serverId The unique server ID.
     * @return The matching payload, or a default-constructed one if not found.
     */
    Q_INVOKABLE DiscoveryPayload getPayloadById(const QString &serverId) const;

    /**
     * @brief Returns all stored discovery payloads as a list.
     * Useful for populating list views in QML.
     */
    Q_INVOKABLE QVector<DiscoveryPayload> payloads() const;

    /**
     * @brief Removes a payload by server ID and saves the change.
     * @param serverId The unique ID of the server to remove.
     * @return True if the payload was removed and saved.
     */
    Q_INVOKABLE bool removePayloadById(const QString &serverId);

    /**
     * @brief Loads discovery payloads from the JSON file.
     * @return True on success (even if file doesn't exist).
     */
    Q_INVOKABLE bool load();

    /**
     * @brief Saves discovery payloads to the JSON file.
     * @return True on success.
     */
    Q_INVOKABLE bool save();

    /**
     * @brief Accessor for the singleton instance.
     * @return The shared DiscoveryStoreManager instance.
     */
    static DiscoveryStoreManager* getInstance();

private:
    QHash<QString, DiscoveryPayload> m_payloads; ///< In-memory hash map of discovery payloads keyed by server ID
    QString m_storagePath = "discovery_store.json"; ///< File location for payload persistence

    static DiscoveryStoreManager* s_instance;
};

#endif // DISCOVERYSTOREMANAGER_H
