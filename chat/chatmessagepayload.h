#ifndef CHATMESSAGEPAYLOAD_H
#define CHATMESSAGEPAYLOAD_H

#include <QMetaType>
#include <QDateTime>
#include <QJsonObject>
#include <QtQml/qqmlregistration.h>

/**
 * @class ChatMessagePayload
 * @brief Represents a single chat message within the client.
 *
 * This class encapsulates the data structure of a chat message received from or sent to the server.
 * It is designed to be usable from both C++ and QML and supports initialization from a QJsonObject.
 */
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
    ChatMessagePayload() = default;

    /**
     * @brief Constructs a ChatMessagePayload from a QJsonObject.
     * @param json JSON object containing the message data.
     */
    explicit ChatMessagePayload(const QJsonObject &json);

    /** @brief Returns the unique ID of the message. */
    int id() const;
    /** @brief Sets the unique ID of the message. */
    void setId(int id);

    /** @brief Returns the cache ID, typically used for local identification. */
    int cacheId() const;
    /** @brief Sets the cache ID. */
    void setCacheId(int id);

    /** @brief Returns the user ID of the message sender. */
    QString ownerId() const;
    /** @brief Sets the user ID of the message sender. */
    void setOwnerId(const QString &id);

    /** @brief Returns the username of the message sender. */
    QString username() const;
    /** @brief Sets the username of the message sender. */
    void setUsername(const QString &name);

    /** @brief Returns the name of the channel this message was sent in. */
    QString channel() const;
    /** @brief Sets the name of the channel this message belongs to. */
    void setChannel(const QString &channel);

    /** @brief Returns the actual text content of the message. */
    QString message() const;
    /** @brief Sets the text content of the message. */
    void setMessage(const QString &message);

    /** @brief Returns the timestamp indicating when the message was authored. */
    QDateTime authoredAt() const;
    /** @brief Sets the authored timestamp of the message. */
    void setAuthoredAt(const QDateTime &datetime);

private:
    int m_id{-1};                 ///< Unique message ID
    int m_cacheId{-1};            ///< Optional cache ID for local use
    QString m_ownerId;            ///< Sender's user ID
    QString m_username;           ///< Sender's username
    QString m_channel;            ///< Channel name
    QString m_message;            ///< Message content
    QDateTime m_authoredAt;       ///< Timestamp of when the message was written
};

Q_DECLARE_METATYPE(ChatMessagePayload)

#endif // CHATMESSAGEPAYLOAD_H
