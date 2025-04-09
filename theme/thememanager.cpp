#include "thememanager.h"
#include "colorpalette.h"
#include <QDebug>

ThemeManager::ThemeManager(QObject *parent) : QObject(parent)
{
    qDebug() << "Theme manager initialized";

    auto palette = ColorPalette::CreateDefault();

    // Step 2: Create a default theme
    m_theme = new Theme("Default", this);

    qDebug() << "Theme manager initialized with theme:" << m_theme->name();
}
const Theme* ThemeManager::theme() const
{
    return m_theme;
}
