#ifndef USERSTATUSMODEL_H
#define USERSTATUSMODEL_H

#include <QAbstractListModel>
#include "userstatuspayload.h"

class UserStatusModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum UserRoles {
        UsernameRole = Qt::UserRole + 1,
        IdRole,
        IsConnectedRole,
        PayloadRole
    };
    Q_ENUM(UserRoles)

    explicit UserStatusModel(QObject *parent = nullptr);

    // Basic model functions
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    // API
    Q_INVOKABLE void clear();
    Q_INVOKABLE UserStatusPayload get(int index) const;
    Q_INVOKABLE void setUsers(const QList<UserStatusPayload> &users);
    Q_INVOKABLE void addUser(const UserStatusPayload &user);

private:
    QList<UserStatusPayload> m_users;
};

#endif // USERSTATUSMODEL_H
