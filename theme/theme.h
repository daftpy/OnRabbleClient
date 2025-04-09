#ifndef THEME_H
#define THEME_H

#include <QObject>
#include <QColor>
#include <QMap>
#include <QStringList>
#include <QQmlEngine>
#include <memory>

#include "colorpalette.h"

/**
 * @brief The Theme class maps semantic roles like "primary" or "text" to color scale/shade pairs.
 *
 * Roles can optionally include a modifier (e.g., "text:muted"). This allows themes to be defined
 * semantically rather than with direct color values. Colors are pulled from a shared ColorPalette.
 *
 * Internally, the theme keeps a map from role identifiers to scale/shade color references.
 * Theme exposes a QML-accessible API for color retrieval.
 */
class Theme : public QObject
{
    Q_OBJECT
    QML_ELEMENT

public:
    /**
     * @brief Represents a semantic role and optional modifier.
     * For example: {"text", "muted"} maps to "text:muted" internally.
     */
    struct RoleKey {
        QString role;
        QString modifier;
    };

    /**
     * @brief Represents a reference to a specific color in the palette.
     * For example: {"indigo", "9"}.
     */
    struct ColorRef {
        QString scale;
        QString shade;
    };

    /**
     * @brief Constructs a theme with a given name and optional parent.
     * The internal color palette is initialized to the default set.
     */
    explicit Theme(const QString &name, QObject *parent = nullptr);

    /**
     * @brief Associate a semantic role with a color in the palette.
     * @param role The role (with optional modifier) to assign.
     * @param color The color reference (scale + shade).
     */
    void setRole(const RoleKey &role, const ColorRef &color);

    /**
     * @brief Retrieve a color associated with a semantic role.
     * @param role The role name (e.g. "primary").
     * @param modifier Optional modifier (e.g. "light"). Defaults to "base".
     * @return The resolved QColor, or invalid if not found.
     */
    Q_INVOKABLE QColor color(const QString &role, const QString &modifier = "base") const;

    /**
     * @brief Check if a role and modifier has an associated color.
     * @param role The role name.
     * @param modifier Optional modifier.
     * @return True if the color mapping exists.
     */
    Q_INVOKABLE bool hasColor(const QString &role, const QString &modifier = "base") const;

    /**
     * @brief Return all defined roles (with modifiers).
     */
    Q_INVOKABLE QStringList roles() const;

    /**
     * @brief Get the name of this theme.
     */
    Q_INVOKABLE QString name() const;

private:
    QString m_name; ///< Name of the theme
    QMap<QString, QPair<QString, QString>> m_roleMap; ///< role[:modifier] -> (scale, shade)
    std::unique_ptr<ColorPalette> m_palette; ///< The underlying palette used by the theme
};

#endif // THEME_H
