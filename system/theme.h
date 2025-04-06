#ifndef THEME_H
#define THEME_H

#include <QObject>
#include <QColor>
#include <QMap>
#include <QString>
#include <QQmlEngine>

/**
 * @brief The Theme class provides structured access to named color roles and their shades (light, base, dark).
 *
 * This class supports multiple shades for each color role (e.g., "primary", "accent", "background").
 * Shades are typically "light", "base", and "dark", and the class provides QML-accessible functions
 * to retrieve colors and explore available roles and shades.
 *
 * Used in combination with a singleton ThemeManager to provide global theming to a Qt Quick application.
 */
class Theme : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    /**
     * @brief Constructs the Theme object and populates the color map with default roles and shades.
     * @param parent The QObject parent.
     */
    explicit Theme(QObject *parent = nullptr);

    /**
     * @brief Returns the QColor for a given role and shade.
     * @param role The name of the color role (e.g., "primary", "accent").
     * @param shade The shade of the color ("light", "base", "dark"). Defaults to "base".
     * @return The corresponding QColor or an invalid color if not found.
     */
    Q_INVOKABLE QColor color(const QString &role, const QString &shade = "base") const;

    /**
     * @brief Checks if a color exists for the given role and shade.
     * @param role The color role name.
     * @param shade The shade name.
     * @return True if the color exists; false otherwise.
     */
    Q_INVOKABLE bool hasColor(const QString &role, const QString &shade = "base") const;

    /**
     * @brief Returns a list of all defined color roles (e.g., "primary", "text").
     */
    Q_INVOKABLE QStringList colorRoles() const;

    /**
     * @brief Returns a list of shades available for a given role.
     * @param role The color role to inspect.
     */
    Q_INVOKABLE QStringList shadesFor(const QString &role) const;

private:
    QMap<QString, QMap<QString, QColor>> m_colors; ///< Nested color map: role -> shade -> QColor
};

#endif // THEME_H
