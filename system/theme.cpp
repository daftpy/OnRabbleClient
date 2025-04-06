#include "theme.h"

Theme::Theme(QObject *parent)
    : QObject(parent)
{
    m_colors["indigo"]["1"]  = QColor("#11131f");
    m_colors["indigo"]["2"]  = QColor("#141726");
    m_colors["indigo"]["3"]  = QColor("#182449");
    m_colors["indigo"]["4"]  = QColor("#1d2e62");
    m_colors["indigo"]["5"]  = QColor("#253974");
    m_colors["indigo"]["6"]  = QColor("#304384");
    m_colors["indigo"]["7"]  = QColor("#3a4f97");
    m_colors["indigo"]["8"]  = QColor("#435db1");
    m_colors["indigo"]["9"]  = QColor("#3e63dd");  // Primary base, likely
    m_colors["indigo"]["10"] = QColor("#5472e4");
    m_colors["indigo"]["11"] = QColor("#9eb1ff");
    m_colors["indigo"]["12"] = QColor("#d6e1ff");

    m_colors["ruby"]["1"]  = QColor("#191113");
    m_colors["ruby"]["2"]  = QColor("#1e1517");
    m_colors["ruby"]["3"]  = QColor("#3a141e");
    m_colors["ruby"]["4"]  = QColor("#4e1325");
    m_colors["ruby"]["5"]  = QColor("#5e1a2e");
    m_colors["ruby"]["6"]  = QColor("#6f2539");
    m_colors["ruby"]["7"]  = QColor("#883447");
    m_colors["ruby"]["8"]  = QColor("#b3445a");
    m_colors["ruby"]["9"]  = QColor("#e54666"); // Likely your primary "base"
    m_colors["ruby"]["10"] = QColor("#ec5a72");
    m_colors["ruby"]["11"] = QColor("#ff949d");
    m_colors["ruby"]["12"] = QColor("#fed2e1");

    m_colors["slate"]["1"]  = QColor("#111113");
    m_colors["slate"]["2"]  = QColor("#18191b");
    m_colors["slate"]["3"]  = QColor("#212225");
    m_colors["slate"]["4"]  = QColor("#272a2d");
    m_colors["slate"]["5"]  = QColor("#2e3135");
    m_colors["slate"]["6"]  = QColor("#363a3f");
    m_colors["slate"]["7"]  = QColor("#43484e");
    m_colors["slate"]["8"]  = QColor("#5a6169");
    m_colors["slate"]["9"]  = QColor("#696e77");
    m_colors["slate"]["10"] = QColor("#777b84");
    m_colors["slate"]["11"] = QColor("#b0b4ba");
    m_colors["slate"]["12"] = QColor("#edeef0");


}

QColor Theme::color(const QString &role, const QString &shade) const
{
    if (m_colors.contains(role)) {
        const auto &shades = m_colors[role];
        if (shades.contains(shade))
            return shades[shade];
        else if (shade == "base" && !shades.isEmpty())
            return shades.value("base", shades.first());
    }
    return QColor(); // fallback
}

bool Theme::hasColor(const QString &role, const QString &shade) const
{
    return m_colors.contains(role) && m_colors[role].contains(shade);
}

QStringList Theme::colorRoles() const
{
    return m_colors.keys();
}

QStringList Theme::shadesFor(const QString &role) const
{
    return m_colors.contains(role) ? m_colors[role].keys() : QStringList();
}
