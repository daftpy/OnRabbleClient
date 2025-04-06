#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>
#include <QQmlEngine>
#include "theme.h"

class ThemeManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(const Theme* theme READ theme CONSTANT)

public:
    explicit ThemeManager(QObject *parent = nullptr);

    const Theme* theme() const;

private:
    Theme* m_theme;
};

#endif // THEMEMANAGER_H
