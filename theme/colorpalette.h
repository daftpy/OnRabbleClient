#ifndef COLORPALETTE_H
#define COLORPALETTE_H

#include <QString>
#include <QColor>
#include <QMap>
#include <QStringList>

/**
 * @brief The ColorPalette class represents a named group of related colors (a color scale).
 *
 * Each scale (e.g., "indigo", "slate") has shades identified by string keys like "1" to "12".
 * This class provides methods to define, retrieve, and inspect these color scales.
 */
class ColorPalette
{
public:
    ColorPalette() = default;

    /**
     * @brief Create a default color palette with predefined scales and shades.
     * @return A unique pointer to a fully populated ColorPalette instance.
     */
    static std::unique_ptr<ColorPalette> CreateDefault();

    /**
     * @brief Define an entire color scale at once.
     * @param name The name of the color scale (e.g. "indigo").
     * @param shades A map from shade keys (e.g. "1", "2", ...) to QColor values.
     */
    void setColorScale(const QString &name, const QMap<QString, QColor> &shades);

    /**
     * @brief Set or update a single shade within a scale.
     * @param scaleName The name of the color scale.
     * @param shadeKey The key for the shade (e.g. "6").
     * @param color The QColor to assign to this shade.
     */
    void setColorShade(const QString &scaleName, const QString &shadeKey, const QColor &color);

    /**
     * @brief Retrieve a specific color from a scale and shade.
     * @param scaleName The name of the color scale.
     * @param shadeKey The shade key.
     * @return The corresponding QColor, or default if not found.
     */
    QColor shade(const QString &scaleName, const QString &shadeKey) const;

    /**
     * @brief Check if a specific scale and shade exists.
     * @param scaleName The name of the color scale.
     * @param shadeKey The key for the shade.
     * @return True if the scale and shade are present.
     */
    bool hasShade(const QString &scaleName, const QString &shadeKey) const;

    /**
     * @brief Get a list of all defined scale names.
     * @return A QStringList of scale names.
     */
    QStringList scaleNames() const;

    /**
     * @brief Get a list of shade keys for a given scale.
     * @param scaleName The name of the scale.
     * @return A QStringList of shade keys, or empty if the scale is not found.
     */
    QStringList shadeKeysFor(const QString &scaleName) const;

private:
    QMap<QString, QMap<QString, QColor>> m_colors; // Map from scale -> (shade -> color)
};

#endif // COLORPALETTE_H
