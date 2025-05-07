#ifndef CHANNELPAYLOAD_H
#define CHANNELPAYLOAD_H

#include <QMetaType>
#include <QString>
#include <QJsonObject>
#include <QtQml/qqmlregistration.h>

// Represents metadata for a public chat channel
class ChannelPayload
{
    Q_GADGET
    Q_PROPERTY(int id READ id WRITE setId)                                  // Unique ID of the channel
    Q_PROPERTY(QString name READ name WRITE setName)                        // Channel display name
    Q_PROPERTY(QString description READ description WRITE setDescription)   // Channel description
    Q_PROPERTY(int sortOrder READ sortOrder WRITE setSortOrder)             // Sort priority
    QML_VALUE_TYPE(channelPayload)

public:
    ChannelPayload() = default;
    explicit ChannelPayload(const QJsonObject &json); // Construct from JSON

    int id() const;
    void setId(int id);

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    int sortOrder() const;
    void setSortOrder(int order);

    bool operator==(const ChannelPayload &other) const; // Used for equality checks
    bool operator<(const ChannelPayload &other) const;  // Used for sorting

private:
    int m_id{-1};             // Channel ID (defaults to invalid)
    QString m_name;           // Name of the channel
    QString m_description;    // Description of the channel
    int m_sortOrder{0};       // Order in sorted lists
};

Q_DECLARE_METATYPE(ChannelPayload)

#endif // CHANNELPAYLOAD_H
