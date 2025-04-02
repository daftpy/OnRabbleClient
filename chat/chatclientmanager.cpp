#include "chatclientmanager.h"
#include <QDebug>

ChatClientManager::ChatClientManager(QObject *parent) : QObject{parent}
{
    qDebug() << "ChatClientManager: initialized";
}
