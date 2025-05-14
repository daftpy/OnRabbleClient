#ifndef PRIVATEMESSAGEPROXYMODEL_H
#define PRIVATEMESSAGEPROXYMODEL_H

#include <QSortFilterProxyModel>

/**
 * @class PrivateMessageProxyModel
 * @brief A proxy model filtering messages strictly between two users.
 */
class PrivateMessageProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString myUserId READ myUserId WRITE setMyUserId NOTIFY myUserIdChanged)
    Q_PROPERTY(QString targetUserId READ targetUserId WRITE setTargetUserId NOTIFY targetUserIdChanged)

public:
    explicit PrivateMessageProxyModel(QObject *parent = nullptr);

    QString myUserId() const;
    void setMyUserId(const QString &id);

    QString targetUserId() const;
    void setTargetUserId(const QString &id);

    Q_INVOKABLE QVariantMap get(int row) const;

signals:
    void myUserIdChanged();
    void targetUserIdChanged();

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

private:
    QString m_myUserId;
    QString m_targetUserId;
};

#endif // PRIVATEMESSAGEPROXYMODEL_H
