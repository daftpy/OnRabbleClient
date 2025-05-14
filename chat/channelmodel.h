#ifndef CHANNELMODEL_H
#define CHANNELMODEL_H

#include <QAbstractListModel>
#include "messages/payloads/system/channelpayload.h"

class ChannelModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    // Custom roles exposed to QML
    enum ChannelRoles {
        IdRole = Qt::UserRole + 1,  // Unique channel ID
        NameRole,                   // Channel name (string)
        DescriptionRole,            // Description or topic text
        SortOrderRole,              // Optional UI sort index
        PayloadRole                 // Full ChannelPayload object
    };
    Q_ENUM(ChannelRoles)

    explicit ChannelModel(QObject *parent = nullptr);

    // Returns the number of channels in the list
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    // Returns role data for a given index
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Returns a hash mapping role enums to names for QML access
    QHash<int, QByteArray> roleNames() const override;

    // Clears all channel entries
    Q_INVOKABLE void clear();

    // Returns the ChannelPayload at the given index, or a default if invalid
    Q_INVOKABLE ChannelPayload get(int index) const;

    // Appends a batch of channels to the model
    Q_INVOKABLE void addChannels(const QList<ChannelPayload> &channels);

private:
    QList<ChannelPayload> m_channels; // Internal list of channels
};

#endif // CHANNELMODEL_H
