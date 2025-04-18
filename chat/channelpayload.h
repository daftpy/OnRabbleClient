#ifndef CHANNELPAYLOAD_H
#define CHANNELPAYLOAD_H

#include <QMetaType>
#include <QString>
#include <QJsonObject>
#include <QtQml/qqmlregistration.h>

class ChannelPayload
{
    Q_GADGET
    Q_PROPERTY(int id READ id WRITE setId)
    Q_PROPERTY(QString name READ name WRITE setName)
    Q_PROPERTY(QString description READ description WRITE setDescription)
    Q_PROPERTY(int sortOrder READ sortOrder WRITE setSortOrder)
    QML_VALUE_TYPE(channelPayload)
public:
    ChannelPayload() = default;
    explicit ChannelPayload(const QJsonObject &json);

    int id() const;
    void setId(int id);

    QString name() const;
    void setName(const QString &name);

    QString description() const;
    void setDescription(const QString &description);

    int sortOrder() const;
    void setSortOrder(int order);

    bool operator==(const ChannelPayload &other) const;
    bool operator<(const ChannelPayload &other) const;

private:
    int m_id{-1}; // default to invalid values
    QString m_name;
    QString m_description;
    int m_sortOrder{0}; // default to invalid values
};

Q_DECLARE_METATYPE(ChannelPayload)

#endif // CHANNELPAYLOAD_H
