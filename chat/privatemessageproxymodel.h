#ifndef PRIVATEMESSAGEPROXYMODEL_H
#define PRIVATEMESSAGEPROXYMODEL_H

#include <QSortFilterProxyModel>

// Filters private messages to only those exchanged between two specific users
class PrivateMessageProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
    Q_PROPERTY(QString myUserId READ myUserId WRITE setMyUserId NOTIFY myUserIdChanged)           // The current user
    Q_PROPERTY(QString targetUserId READ targetUserId WRITE setTargetUserId NOTIFY targetUserIdChanged) // The user being chatted with

public:
    explicit PrivateMessageProxyModel(QObject *parent = nullptr);

    QString myUserId() const;            // Returns the current user's ID
    void setMyUserId(const QString &id); // Sets the current user's ID and re-filters

    QString targetUserId() const;            // Returns the chat partner's ID
    void setTargetUserId(const QString &id); // Sets the target user ID and re-filters

    Q_INVOKABLE QVariantMap get(int row) const; // Returns a row's data as a QVariantMap for QML use

signals:
    void myUserIdChanged();       // Emitted when myUserId changes
    void targetUserIdChanged();   // Emitted when targetUserId changes

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override; // Filters rows based on the two user IDs

private:
    QString m_myUserId;       // The user's own ID
    QString m_targetUserId;   // The ID of the user they're chatting with
};

#endif // PRIVATEMESSAGEPROXYMODEL_H
