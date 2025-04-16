#ifndef CHATCHANNELPAYLOADMODEL_H
#define CHATCHANNELPAYLOADMODEL_H

#include <QAbstractListModel>
#include "channelpayload.h"

class ChatChannelPayloadModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum ChannelRoles {
        IdRole = Qt::UserRole + 1,
        NameRole,
        DescriptionRole,
        SortOrderRole
    };
    Q_ENUM(ChannelRoles)

    explicit ChatChannelPayloadModel(QObject *parent = nullptr);

    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_INVOKABLE void clear();
    Q_INVOKABLE ChannelPayload get(int index) const;
    Q_INVOKABLE void addChannels(const QList<ChannelPayload> &channels);

private:
    QList<ChannelPayload> m_channels;
};

#endif // CHATCHANNELPAYLOADMODEL_H
