#ifndef CHATMESSAGEPAYLOAD_H
#define CHATMESSAGEPAYLOAD_H

#include <QMetaType>
#include <QDateTime>
#include <QJsonObject>
#include <QtQml/qqmlregistration.h>

// Represents a single chat message sent or received by the client.
class ChatMessagePayload
{
    Q_GADGET
    Q_PROPERTY(int id READ id WRITE setId)
    Q_PROPERTY(int cacheId READ cacheId WRITE setCacheId)
    Q_PROPERTY(QString ownerId READ ownerId WRITE setOwnerId)
    Q_PROPERTY(QString username READ username WRITE setUsername)
    Q_PROPERTY(QString channel READ channel WRITE setChannel)
    Q_PROPERTY(QString message READ message WRITE setMessage)
    Q_PROPERTY(QDateTime authoredAt READ authoredAt WRITE setAuthoredAt)
    QML_VALUE_TYPE(chatMessagePayload)

public:
    ChatMessagePayload() = default; // Default constructor

    explicit ChatMessagePayload(const QJsonObject &json); // Construct from JSON

    int id() const;
    void setId(int id);

    int cacheId() const;
    void setCacheId(int id);

    QString ownerId() const;
    void setOwnerId(const QString &id);

    QString username() const;
    void setUsername(const QString &name);

    QString channel() const;
    void setChannel(const QString &channel);

    QString message() const;
    void setMessage(const QString &message);

    QDateTime authoredAt() const;
    void setAuthoredAt(const QDateTime &datetime);

private:
    int m_id{-1};                 // Server-provided unique message ID
    int m_cacheId{-1};            // Server-cache ID
    QString m_ownerId;            // Sender's user ID
    QString m_username;           // Sender's display name
    QString m_channel;            // Channel name the message belongs to
    QString m_message;            // Message content
    QDateTime m_authoredAt;       // Timestamp of when the message was authored
};

Q_DECLARE_METATYPE(ChatMessagePayload)

#endif // CHATMESSAGEPAYLOAD_H
