#ifndef PRIVATEMESSAGEMODEL_H
#define PRIVATEMESSAGEMODEL_H

#include <QAbstractListModel>
#include <qqmlintegration.h>
#include "messages/payloads/chat/privatechatmessagepayload.h"

// Model for managing a list of private messages (used in QML)
class PrivateMessageModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    // Role identifiers for exposing private message fields to QML
    enum PrivateMessageRoles {
        IdRole = Qt::UserRole + 1,   // Message ID
        OwnerIdRole,                 // Sender's user ID
        UsernameRole,                // Sender's username
        RecipientIdRole,            // Recipient's user ID
        RecipientRole,              // Recipient's username
        MessageRole,                // Message text
        AuthoredAtRole              // Timestamp
    };
    Q_ENUM(PrivateMessageRoles)

    explicit PrivateMessageModel(QObject *parent = nullptr);

    // Returns the number of rows in the model
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // Returns data for the specified index and role
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Returns a hash of role IDs to QML-accessible names
    QHash<int, QByteArray> roleNames() const override;

    // Appends a new private message to the top of the list
    Q_INVOKABLE void appendMessage(const PrivateChatMessagePayload &msg);

    // Clears all messages from the model
    void clear();

    // Returns the full list of stored messages
    const QList<PrivateChatMessagePayload> &messages() const;

private:
    QList<PrivateChatMessagePayload> m_messages;  // Internal message storage
};

#endif // PRIVATEMESSAGEMODEL_H
