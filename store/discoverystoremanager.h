#ifndef DISCOVERYSTOREMANAGER_H
#define DISCOVERYSTOREMANAGER_H

#include <QObject>
#include <QQmlEngine>
#include "discovery/discoverypayload.h"

/**
 * @brief DiscoveryStoreManager stores previously connected chat servers.
 *
 * Provides persistent storage for DiscoveryPayloads via JSON.
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
     * @brief Adds a new discovery payload and saves it.
     * @param payload The discovery payload to store.
     */
    Q_INVOKABLE void addPayload(const DiscoveryPayload &payload);

    /**
     * @brief Returns all stored discovery payloads.
     */
    Q_INVOKABLE QVector<DiscoveryPayload> payloads() const;

    /**
     * @brief Removes a payload by server name and saves the change.
     * @param serverName The name of the server to remove.
     * @return True if the payload was removed.
     */
    Q_INVOKABLE bool removePayloadByName(const QString &serverName);

    /**
     * @brief Loads discovery payloads from the JSON file.
     * @return True on success.
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
    QVector<DiscoveryPayload> m_payloads; ///< In-memory list of discovery payloads
    QString m_storagePath = "discovery_store.json"; ///< File location for payload persistence

    static DiscoveryStoreManager* s_instance;
};

#endif // DISCOVERYSTOREMANAGER_H
