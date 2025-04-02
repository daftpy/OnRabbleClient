#ifndef CHATCLIENTMANAGER_H
#define CHATCLIENTMANAGER_H

#include <QObject>
#include <QQmlEngine>

class ChatClientManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
public:
    ChatClientManager(QObject *parent = nullptr);
};

#endif // CHATCLIENTMANAGER_H
