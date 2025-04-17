#ifndef PRIVATECHATMESSAGEMODEL_H
#define PRIVATECHATMESSAGEMODEL_H

#include <QAbstractListModel>
#include <qqmlintegration.h>
#include "privatechatmessagepayload.h"

/**
 * @class PrivateChatMessageModel
 * @brief A QAbstractListModel subclass for managing and exposing a list of private chat messages.
 *
 * This model is intended for use in QML to display a list of `PrivateChatMessagePayload` items.
 * It supports appending new messages, clearing the list, and exposing role names for binding in QML views.
 */
class PrivateChatMessageModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    /**
     * @enum PrivateChatMessageRoles
     * @brief Role names used to expose private message data to QML delegates.
     */
    enum PrivateChatMessageRoles {
        IdRole = Qt::UserRole + 1,   ///< Message ID
        OwnerIdRole,                 ///< Sender's user ID
        UsernameRole,                ///< Sender's username
        RecipientIdRole,             ///< Recipient's user ID
        RecipientRole,               ///< Recipient's username
        MessageRole,                 ///< Message content
        AuthoredAtRole               ///< Time the message was written
    };
    Q_ENUM(PrivateChatMessageRoles)

    explicit PrivateChatMessageModel(QObject *parent = nullptr);

    /**
     * @brief Returns the number of rows (private messages) in the model.
     * @param parent Unused for list models.
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * @brief Returns the data at a given index and role.
     * @param index The index in the model.
     * @param role The role (e.g. MessageRole, UsernameRole).
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /**
     * @brief Returns the mapping of role integers to their corresponding QML role names.
     */
    QHash<int, QByteArray> roleNames() const override;

    /**
     * @brief Appends a single PrivateChatMessagePayload to the model.
     * @param msg The private message to append.
     *
     * Can be called from QML.
     */
    Q_INVOKABLE void appendMessage(const PrivateChatMessagePayload &msg);

    /**
     * @brief Clears all private messages from the model.
     */
    void clear();

    /**
     * @brief Returns a const reference to the list of private messages.
     */
    const QList<PrivateChatMessagePayload> &messages() const;

private:
    QList<PrivateChatMessagePayload> m_messages; ///< Internal storage for private chat messages
};

#endif // PRIVATECHATMESSAGEMODEL_H
