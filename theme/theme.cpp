#include "theme.h"
#include <QDebug>

Theme::Theme(const QString &name, QObject *parent)
    // Create a default theme with a default palette
    : QObject(parent), m_name(name), m_palette(ColorPalette::CreateDefault())
{
    qDebug() << "Initialized theme:" << m_name;

    // Set the default roles

    // Primary Colors
    setRole({ "primary", "lightest" }, { "indigo", "12" });
    setRole({ "primary", "lighter" },  { "indigo", "11" });
    setRole({ "primary", "light" },    { "indigo", "10" });
    setRole({ "primary", "" },         { "indigo", "9" });
    setRole({ "primary", "dark" },     { "indigo", "8" });
    setRole({ "primary", "darker" },   { "indigo", "7" });
    setRole({ "primary", "darkest" },  { "indigo", "6" });

    // Accent Colors
    setRole({ "accent", "lightest" }, { "jade", "12" });
    setRole({ "accent", "lighter" }, { "jade", "11" });
    setRole({ "accent", "light" }, { "jade", "10" });
    setRole({ "accent", "" }, { "jade", "9"});
    setRole({ "accent", "dark" }, { "jade", "8"});
    setRole({ "accent", "darker" }, { "jade", "7"});
    setRole({ "accent", "darkest" }, { "jade", "6"});

    // Text Colors
    setRole({ "text", "" },            { "slate", "12" });
    setRole({ "text", "highlight" },   { "indigo", "12" });
    setRole({ "text", "muted" },       { "slate", "9" });

    // Background Colors
    setRole({ "background", "darkest" }, { "slate", "1" });
    setRole({ "background", "darker" },  { "slate", "2" });
    setRole({ "background", "dark" },    { "slate", "3" });
    setRole({ "background", "" },        { "slate", "4" });
    setRole({ "background", "light" },   { "slate", "5" });
    setRole({ "background", "lighter" }, { "slate", "6" });
    setRole({ "background", "lightest" },{ "slate", "7" });

    // Border color
    setRole({ "border", "" }, { "slate", "6" });

    // Danger Colors
    setRole({"danger", "lightest"}, {"red", "12"});
    setRole({"danger", "lighter"}, {"red", "11"});
    setRole({"danger", "light"}, {"red", "10"});
    setRole({ "danger", "" }, { "red", "9" });
    setRole({"danger", "dark"}, {"red", "8"});
    setRole({"danger", "darker"}, {"red", "7"});
    setRole({"danger", "darkest"}, {"red", "6"});
    setRole({"danger", "hovered"}, {"tomato", "9"});
    setRole({"danger", "border"}, {"red", "6"});
}

void Theme::setRole(const Theme::RoleKey &role, const Theme::ColorRef &color)
{
    // Compose the key as "role[:modifier]" depending on whether a modifier is provided
    QString fullKey = role.modifier.isEmpty() ? role.role : role.role + ":" + role.modifier;

    // Store the associated color scale and shade
    m_roleMap[fullKey] = qMakePair(color.scale, color.shade);
}

QColor Theme::color(const QString &role, const QString &modifier) const
{
    if (!m_palette)
        return QColor(); // Return invalid color if no palette is set

    // Try to look up a color for the full "role:modifier" key
    if (modifier != "base") {
        QString fullKey = role + ":" + modifier;
        if (m_roleMap.contains(fullKey)) {
            const auto &[scale, shade] = m_roleMap[fullKey];
            return m_palette->shade(scale, shade);
        }
    }

    // Fallback: try just the base role without modifier
    if (m_roleMap.contains(role)) {
        const auto &[scale, shade] = m_roleMap[role];
        return m_palette->shade(scale, shade);
    }

    return QColor(); // Fallback if no color mapping found
}

bool Theme::hasColor(const QString &role, const QString &modifier) const
{
    if (!m_palette)
        return false;

    // Check for "role:modifier" mapping
    if (modifier != "base" && m_roleMap.contains(role + ":" + modifier))
        return true;

    // Check fallback for just the role
    return m_roleMap.contains(role);
}

QStringList Theme::roles() const
{
    // Return all defined role keys (including modifiers)
    return m_roleMap.keys();
}

QString Theme::name() const
{
    // Return the theme's name
    return m_name;
}
