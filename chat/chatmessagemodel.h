#ifndef CHATMESSAGEMODEL_H
#define CHATMESSAGEMODEL_H

#include <QAbstractListModel>
#include <qqmlintegration.h>
#include "chatmessagepayload.h"

/**
 * @class ChatMessageModel
 * @brief A QAbstractListModel subclass for managing and exposing a list of chat messages.
 *
 * This model is intended for use in QML to display a list of `ChatMessagePayload` items.
 * It supports appending new messages, clearing the list, and exposing role names for binding in QML views.
 */
class ChatMessageModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT  ///< Registers this class as a QML element (ChatMessageModel)

public:
    /**
     * @enum ChatMessageRoles
     * @brief Role names used to expose message data to QML delegates.
     */
    enum ChatMessageRoles {
        IdRole = Qt::UserRole + 1,    ///< Message ID
        CacheIdRole,                  ///< Cache/local ID
        OwnerIdRole,                  ///< Sender's user ID
        UsernameRole,                 ///< Sender's username
        ChannelRole,                  ///< Channel name
        MessageRole,                  ///< Message content
        AuthoredAtRole                ///< Time the message was written
    };
    Q_ENUM(ChatMessageRoles)

    explicit ChatMessageModel(QObject *parent = nullptr);

    /**
     * @brief Returns the number of rows (messages) in the model.
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
     * @brief Appends a single ChatMessagePayload to the model.
     * @param msg The message to append.
     *
     * Can be called from QML.
     */
    Q_INVOKABLE void appendMessage(const ChatMessagePayload &msg);

    /**
     * @brief Clears all messages from the model.
     */
    void clear();

    /**
     * @brief Returns a const reference to the list of messages.
     */
    const QList<ChatMessagePayload> &messages() const;

private:
    QList<ChatMessagePayload> m_messages; ///< Internal storage for chat messages
};

#endif // CHATMESSAGEMODEL_H
