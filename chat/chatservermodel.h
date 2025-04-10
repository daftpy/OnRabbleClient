#ifndef CHATSERVERMODEL_H
#define CHATSERVERMODEL_H

#include <QAbstractListModel>
#include "discovery/discoverypayload.h"
#include "chatclientmanager.h"

/**
 * @brief Represents a single entry in the ChatServerModel.
 *
 * Each entry holds the discovery payload (metadata) for the chat server,
 * along with a pointer to the associated ChatClientManager instance
 * responsible for maintaining the connection.
 */
struct ChatServerEntry
{
    DiscoveryPayload m_payload;              ///< Server metadata and configuration
    ChatClientManager *m_chatClientManager;  ///< Manages chat connection lifecycle
};
/**
 * @brief The ChatServerModel class provides a list model for active chat server connections.
 *
 * This class maintains a collection of connected or reconnectable chat servers, each with
 * an associated DiscoveryPayload and ChatClientManager. It is exposed to QML as a list model.
 *
 * Roles exposed to QML:
 * - payload: The DiscoveryPayload used to configure the connection
 * - chatClientManager: The active ChatClientManager for that server
 */
class ChatServerModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    /**
     * @brief Custom roles for accessing entry data in QML.
     */
    enum Roles {
        PayloadRole = Qt::UserRole + 1, ///< Role for DiscoveryPayload
        ManagerRole                     ///< Role for ChatClientManager
    };
    Q_ENUM(Roles)

    /**
     * @brief Constructs an empty ChatServerModel.
     */
    explicit ChatServerModel(QObject *parent = nullptr);

    /**
     * @brief Returns number of active chat servers.
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief Returns data for a given row and role.
     * @param index The row index.
     * @param role The role (e.g., PayloadRole or ManagerRole).
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /**
     * @brief Returns mapping of custom roles to QML names.
     */
    QHash<int, QByteArray> roleNames() const override;

    /**
     * @brief Opens or reopens a chat connection to a server.
     *
     * If the server already exists in the model, the existing manager is replaced.
     * Otherwise, a new row is appended.
     *
     * @param payload The discovery metadata for the chat server.
     * @param token The access token for authentication.
     */
    Q_INVOKABLE void openChatWindoow(const DiscoveryPayload &payload, const QString &token);

    /**
     * @brief Closes and removes the chat server at the given row.
     * @param row The index of the chat server to remove.
     */
    Q_INVOKABLE void closeAt(int row);

private:
    /**
     * @brief Finds the index of a server by name.
     * @param name The server name to look for.
     * @return The index if found, -1 otherwise.
     */
    int indexOfServer(const QString &name) const;

    QVector<ChatServerEntry> m_entries; ///< Internal list of server entries
};

#endif // CHATSERVERMODEL_H
