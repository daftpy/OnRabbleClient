#ifndef DISCOVERYMODEL_H
#define DISCOVERYMODEL_H

#include <QAbstractListModel>
#include "discoverypayload.h"

/**
 * @brief The DiscoveryModel class provides a reactive model of previously discovered servers.
 *
 * This class loads `DiscoveryPayload` objects from disk and exposes them to QML
 * via a standard Qt `QAbstractListModel` interface. It supports four roles:
 * - serverName
 * - authEndpoint
 * - tokenEndpoint
 * - chatEndpoint
 */
class DiscoveryModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    /**
     * @brief Custom roles for DiscoveryPayload fields.
     */
    enum PayloadRoles {
        ServerNameRole = Qt::UserRole + 1, ///< Role for server name
        ServerIdRole,                      ///< Role for server id
        AuthEndpointRole,                  ///< Role for auth URL
        TokenEndpointRole,                 ///< Role for token URL
        ChatEndpointRole                   ///< Role for chat URL
    };
    Q_ENUM(PayloadRoles)

    explicit DiscoveryModel(QObject *parent = nullptr);

    /**
     * @brief Returns display name of the header (if any).
     */
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    /**
     * @brief Returns number of rows (items) in the model.
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief Returns data for a given index and role.
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /**
     * @brief Returns a mapping of custom role integers to names.
     */
    QHash<int, QByteArray> roleNames() const override;

    /**
     * @brief Loads discovery payloads from disk and resets the model.
     */
    Q_INVOKABLE void load();

    /**
     * @brief Clears the model (without touching disk).
     */
    Q_INVOKABLE void clear();

    /**
     * @brief Gets the DiscoveryPayload at the given index.
     * @param index The row index.
     * @return The payload object (or empty one if index is invalid).
     */
    Q_INVOKABLE DiscoveryPayload get(int index) const;

private:
    QVector<DiscoveryPayload> m_payloads; ///< In-memory list of payloads
};

#endif // DISCOVERYMODEL_H
