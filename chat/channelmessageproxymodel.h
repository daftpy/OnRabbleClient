#ifndef CHANNELMESSAGEPROXYMODEL_H
#define CHANNELMESSAGEPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <qqmlintegration.h>

/**
 * @class ChannelMessageProxyModel
 * @brief A proxy model that filters chat messages by channel name.
 *
 * This proxy model is meant to sit on top of ChatMessageModel and expose only
 * the messages that belong to a specific channel. The channel can be set from C++ or QML.
 */
class ChannelMessageProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    QML_ELEMENT

    /**
     * @brief The name of the channel to filter messages by.
     */
    Q_PROPERTY(QString channel READ channel WRITE setChannel NOTIFY channelChanged)

    Q_PROPERTY(QString name READ channelName CONSTANT)

public:
    explicit ChannelMessageProxyModel(QObject *parent = nullptr);

    /**
     * @brief Sets the channel name used for filtering messages.
     * @param name The name of the channel.
     */
    void setChannel(const QString &name);

    /**
     * @brief Returns the currently set channel name.
     * @return The name of the channel used for filtering.
     */
    QString channel() const;

    QString channelName() const { return m_channel; }

    Q_INVOKABLE QVariantMap get(int row) const;

signals:
    void channelChanged();

protected:
    /**
     * @brief Called for each row to determine if it should be included in the view.
     * @param sourceRow The index of the row in the source model.
     * @param sourceParent The parent index.
     * @return true if the row should be included, false otherwise.
     */
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
    QString m_channel;
};

#endif // CHANNELMEESSAGEPROXYMODEL_H
