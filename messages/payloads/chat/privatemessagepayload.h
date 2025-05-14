#ifndef PRIVATEMESSAGEPAYLOAD_H
#define PRIVATEMESSAGEPAYLOAD_H

#include <QMetaType>
#include <QDateTime>
#include <QJsonObject>
#include <QtQml/qqmlregistration.h>

// Represents a private chat message exchanged between two users.
// Usable from both C++ and QML.
class PrivateMessagePayload
{
    Q_GADGET
    Q_PROPERTY(int id READ id WRITE setId)
    Q_PROPERTY(QString ownerId READ ownerId WRITE setOwnerId)
    Q_PROPERTY(QString username READ username WRITE setUsername)
    Q_PROPERTY(QString recipientId READ recipientId WRITE setRecipientId)
    Q_PROPERTY(QString recipient READ recipient WRITE setRecipient)
    Q_PROPERTY(QString message READ message WRITE setMessage)
    Q_PROPERTY(QDateTime authoredAt READ authoredAt WRITE setAuthoredAt)
    QML_VALUE_TYPE(privateChatMessagePayload)

public:
    PrivateMessagePayload() = default;

    // Construct from a JSON payload
    explicit PrivateMessagePayload(const QJsonObject &json);

    int id() const;
    void setId(int id);

    QString ownerId() const;
    void setOwnerId(const QString &id);

    QString username() const;
    void setUsername(const QString &username);

    QString recipientId() const;
    void setRecipientId(const QString &recipientId);

    QString recipient() const;
    void setRecipient(const QString &recipient);

    QString message() const;
    void setMessage(const QString &message);

    QDateTime authoredAt() const;
    void setAuthoredAt(const QDateTime &datetime);

private:
    int m_id{-1};
    QString m_ownerId;
    QString m_username;
    QString m_recipientId;
    QString m_recipient;
    QString m_message;
    QDateTime m_authoredAt;
};

Q_DECLARE_METATYPE(PrivateMessagePayload)

#endif // PRIVATECHATMESSAGEPAYLOAD_H
