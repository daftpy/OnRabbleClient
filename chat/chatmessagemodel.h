#ifndef CHATMESSAGEMODEL_H
#define CHATMESSAGEMODEL_H

#include <QAbstractListModel>
#include <qqmlintegration.h>
#include "messages/payloads/chat/chatmessagepayload.h"

class ChatMessageModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT  // Registers this class as a QML element

public:
    // Roles used to expose message data to QML
    enum ChatMessageRoles {
        IdRole = Qt::UserRole + 1,   // Unique message ID
        CacheIdRole,                 // Local or cached ID
        OwnerIdRole,                 // Sender's user ID
        UsernameRole,                // Sender's display name
        ChannelRole,                 // Channel the message belongs to
        MessageRole,                 // Raw message text
        AuthoredAtRole               // Timestamp string
    };
    Q_ENUM(ChatMessageRoles)

    explicit ChatMessageModel(QObject *parent = nullptr);

    // Returns the number of messages in the model
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // Returns data for a specific message and role
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Returns the mapping of role values to QML-accessible names
    QHash<int, QByteArray> roleNames() const override;

    // Appends a new message to the top of the list
    Q_INVOKABLE void appendMessage(const ChatMessagePayload &msg);

    // Clears all messages from the model
    void clear();

    // Returns the full list of messages (const reference)
    const QList<ChatMessagePayload> &messages() const;

private:
    QList<ChatMessagePayload> m_messages;  // Internal list of chat messages
};

#endif // CHATMESSAGEMODEL_H
