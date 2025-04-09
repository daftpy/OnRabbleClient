#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>
#include <QQmlEngine>
#include "theme.h"

/**
 * @brief The ThemeManager class provides a singleton wrapper around a Theme instance.
 *
 * This manager exposes the current theme to QML via a constant property. It is intended to be
 * a global access point for the application's active visual theme.
 */
class ThemeManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

    /**
     * @brief The current theme exposed to QML.
     */
    Q_PROPERTY(const Theme* theme READ theme CONSTANT)

public:
    /**
     * @brief Constructs a ThemeManager.
     * @param parent Optional parent QObject.
     */
    explicit ThemeManager(QObject *parent = nullptr);

    /**
     * @brief Returns the active theme.
     */
    const Theme* theme() const;

private:
    Theme* m_theme; ///< Pointer to the currently active theme instance
};

#endif // THEMEMANAGER_H
