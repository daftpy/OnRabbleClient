#ifndef CHANNELMESSAGEPROXYMODEL_H
#define CHANNELMESSAGEPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <qqmlintegration.h>

class ChannelMessageProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    QML_ELEMENT

    // Channel name used to filter messages
    Q_PROPERTY(QString channel READ channel WRITE setChannel NOTIFY channelChanged)

    // Duplicate of 'channel' exposed as read-only under 'name'
    Q_PROPERTY(QString name READ channelName CONSTANT)

public:
    explicit ChannelMessageProxyModel(QObject *parent = nullptr);

    // Sets the active channel used to filter messages
    void setChannel(const QString &name);

    // Returns the current channel name
    QString channel() const;

    // Returns the same value as channel(), exposed for QML UI purposes
    QString channelName() const { return m_channel; }

    // Returns a full QVariantMap of data at a proxy row
    Q_INVOKABLE QVariantMap get(int row) const;

signals:
    // Emitted when the channel name changes
    void channelChanged();

protected:
    // Determines whether a given row matches the current channel filter
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
    QString m_channel;  // Active channel used for filtering
};

#endif // CHANNELMEESSAGEPROXYMODEL_H
