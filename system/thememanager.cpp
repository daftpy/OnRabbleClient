#include "thememanager.h"
#include <QDebug>

ThemeManager::ThemeManager(QObject *parent) : m_theme(new Theme(this)), QObject(parent)
{
    qDebug() << "Theme manager initialized";
}

const Theme* ThemeManager::theme() const
{
    return m_theme;
}
