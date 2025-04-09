#include "colorpalette.h"

std::unique_ptr<ColorPalette> ColorPalette::CreateDefault()
{
    // Step 1: Create and populate the palette
    auto palette = std::make_unique<ColorPalette>();

    // Set the default color scales
    // Default scales from https://www.radix-ui.com/colors/docs/palette-composition/scales
    palette->setColorScale("gray", {
        {"1", "#111111"}, {"2", "#191919"}, {"3", "#222222"}, {"4", "#2a2a2a"},
        {"5", "#313131"}, {"6", "#3a3a3a"}, {"7", "#484848"}, {"8", "#606060"},
        {"9", "#6e6e6e"}, {"10", "#7b7b7b"}, {"11", "#b4b4b4"}, {"12", "#eeeeee"}
    });

    palette->setColorScale("mauve", {
        {"1", "#121113"}, {"2", "#1a191b"}, {"3", "#232225"}, {"4", "#2b292d"},
        {"5", "#323035"}, {"6", "#3c393f"}, {"7", "#49474e"}, {"8", "#625f69"},
        {"9", "#6f6d78"}, {"10", "#7c7a85"}, {"11", "#b5b2bc"}, {"12", "#eeeef0"}
    });


    palette->setColorScale("slate", {
        {"1", "#111113"}, {"2", "#18191b"}, {"3", "#212225"}, {"4", "#272a2d"},
        {"5", "#2e3135"}, {"6", "#363a3f"}, {"7", "#43484e"}, {"8", "#5a6169"},
        {"9", "#696e77"}, {"10", "#777b84"}, {"11", "#b0b4ba"}, {"12", "#edeef0"}
    });

    palette->setColorScale("sage", {
        {"1", "#101211"}, {"2", "#171918"}, {"3", "#202221"}, {"4", "#272a29"},
        {"5", "#2e3130"}, {"6", "#373b39"}, {"7", "#444947"}, {"8", "#5b625f"},
        {"9", "#63706b"}, {"10", "#717d79"}, {"11", "#adb5b2"}, {"12", "#eceeed"}
    });

    palette->setColorScale("olive", {
        {"1", "#111210"}, {"2", "#181917"}, {"3", "#212220"}, {"4", "#282a27"},
        {"5", "#2f312e"}, {"6", "#383a36"}, {"7", "#454843"}, {"8", "#5c625b"},
        {"9", "#687066"}, {"10", "#767d74"}, {"11", "#afb5ad"}, {"12", "#eceeec"}
    });

    palette->setColorScale("sand", {
        {"1", "#111110"}, {"2", "#191918"}, {"3", "#222221"}, {"4", "#2a2a28"},
        {"5", "#31312e"}, {"6", "#3b3a37"}, {"7", "#494844"}, {"8", "#62605b"},
        {"9", "#6f6d66"}, {"10", "#7c7b74"}, {"11", "#b5b3ad"}, {"12", "#eeeeec"}
    });

    palette->setColorScale("gold", {
        {"1", "#121211"}, {"2", "#1b1a17"}, {"3", "#24231f"}, {"4", "#2d2b26"},
        {"5", "#38352e"}, {"6", "#444039"}, {"7", "#544f46"}, {"8", "#696256"},
        {"9", "#978365"}, {"10", "#a39073"}, {"11", "#cbb99f"}, {"12", "#e8e2d9"}
    });

    palette->setColorScale("bronze", {
        {"1", "#141110"}, {"2", "#1c1917"}, {"3", "#262220"}, {"4", "#302a27"},
        {"5", "#3b3330"}, {"6", "#493e3a"}, {"7", "#5a4c47"}, {"8", "#6f5f58"},
        {"9", "#a18072"}, {"10", "#ae8c7e"}, {"11", "#d4b3a5"}, {"12", "#ede0d9"}
    });

    palette->setColorScale("brown", {
        {"1", "#12110f"}, {"2", "#1c1816"}, {"3", "#28211d"}, {"4", "#322922"},
        {"5", "#3e3128"}, {"6", "#4d3c2f"}, {"7", "#614a39"}, {"8", "#7c5f46"},
        {"9", "#ad7f58"}, {"10", "#b88c67"}, {"11", "#dbb594"}, {"12", "#f2e1ca"}
    });

    palette->setColorScale("yellow", {
        {"1", "#14120b"}, {"2", "#1b180f"}, {"3", "#2d2305"}, {"4", "#362b00"},
        {"5", "#433500"}, {"6", "#524202"}, {"7", "#665417"}, {"8", "#836a21"},
        {"9", "#ffe629"}, {"10", "#ffff57"}, {"11", "#f5e147"}, {"12", "#f6eeb4"}
    });

    palette->setColorScale("amber", {
        {"1", "#16120c"}, {"2", "#1d180f"}, {"3", "#302008"}, {"4", "#3f2700"},
        {"5", "#4d3000"}, {"6", "#5c3d05"}, {"7", "#714f19"}, {"8", "#8f6424"},
        {"9", "#ffc53d"}, {"10", "#ffd60a"}, {"11", "#ffca16"}, {"12", "#ffe7b3"}
    });

    palette->setColorScale("orange", {
        {"1", "#17120e"}, {"2", "#1e160f"}, {"3", "#331e0b"}, {"4", "#462100"},
        {"5", "#562800"}, {"6", "#66350c"}, {"7", "#7e451d"}, {"8", "#a35829"},
        {"9", "#f76b15"}, {"10", "#ff801f"}, {"11", "#ffa057"}, {"12", "#ffe0c2"}
    });

    palette->setColorScale("tomato", {
        {"1", "#181111"}, {"2", "#1f1513"}, {"3", "#391714"}, {"4", "#4e1511"},
        {"5", "#5e1c16"}, {"6", "#6e2920"}, {"7", "#853a2d"}, {"8", "#ac4d39"},
        {"9", "#e54d2e"}, {"10", "#ec6142"}, {"11", "#ff977d"}, {"12", "#fbd3cb"}
    });


    palette->setColorScale("red", {
        {"1", "#191111"}, {"2", "#201314"}, {"3", "#3b1219"}, {"4", "#500f1c"},
        {"5", "#611623"}, {"6", "#72232d"}, {"7", "#8c333a"}, {"8", "#b54548"},
        {"9", "#e5484d"}, {"10", "#ec5d5e"}, {"11", "#ff9592"}, {"12", "#ffd1d9"}
    });

    palette->setColorScale("ruby", {
        {"1", "#191113"}, {"2", "#1e1517"}, {"3", "#3a141e"}, {"4", "#4e1325"},
        {"5", "#5e1a2e"}, {"6", "#6f2539"}, {"7", "#883447"}, {"8", "#b3445a"},
        {"9", "#e54666"}, {"10", "#ec5a72"}, {"11", "#ff949d"}, {"12", "#fed2e1"}
    });

    palette->setColorScale("crimson", {
        {"1", "#191114"}, {"2", "#201318"}, {"3", "#381525"}, {"4", "#4d122f"},
        {"5", "#5c1839"}, {"6", "#6d2545"}, {"7", "#873356"}, {"8", "#b0436e"},
        {"9", "#e93d82"}, {"10", "#ee518a"}, {"11", "#ff92ad"}, {"12", "#fdd3e8"}
    });

    palette->setColorScale("pink", {
        {"1", "#191117"}, {"2", "#21121d"}, {"3", "#37172f"}, {"4", "#4b143d"},
        {"5", "#591c47"}, {"6", "#692955"}, {"7", "#833869"}, {"8", "#a84885"},
        {"9", "#d6409f"}, {"10", "#de51a8"}, {"11", "#ff8dcc"}, {"12", "#fdd1ea"}
    });

    palette->setColorScale("plum", {
        {"1", "#181118"}, {"2", "#201320"}, {"3", "#351a35"}, {"4", "#451d47"},
        {"5", "#512454"}, {"6", "#5e3061"}, {"7", "#734079"}, {"8", "#92549c"},
        {"9", "#ab4aba"}, {"10", "#b658c4"}, {"11", "#e796f3"}, {"12", "#f4d4f4"}
    });

    palette->setColorScale("purple", {
        {"1", "#18111b"}, {"2", "#1e1523"}, {"3", "#301c3b"}, {"4", "#3d224e"},
        {"5", "#48295c"}, {"6", "#54346b"}, {"7", "#664282"}, {"8", "#8457aa"},
        {"9", "#8e4ec6"}, {"10", "#9a5cd0"}, {"11", "#d19dff"}, {"12", "#ecd9fa"}
    });


    palette->setColorScale("violet", {
        {"1", "#14121f"}, {"2", "#1b1525"}, {"3", "#291f43"}, {"4", "#33255b"},
        {"5", "#3c2e69"}, {"6", "#473876"}, {"7", "#56468b"}, {"8", "#6958ad"},
        {"9", "#6e56cf"}, {"10", "#7d66d9"}, {"11", "#baa7ff"}, {"12", "#e2ddfe"}
    });

    palette->setColorScale("iris", {
        {"1", "#13131e"}, {"2", "#171625"}, {"3", "#202248"}, {"4", "#262a65"},
        {"5", "#303374"}, {"6", "#3d3e82"}, {"7", "#4a4a95"}, {"8", "#5958b1"},
        {"9", "#5b5bd6"}, {"10", "#6e6ade"}, {"11", "#b1a9ff"}, {"12", "#e0dffe"}
    });

    palette->setColorScale("indigo", {
        {"1", "#11131f"}, {"2", "#141726"}, {"3", "#182449"}, {"4", "#1d2e62"},
        {"5", "#253974"}, {"6", "#304384"}, {"7", "#3a4f97"}, {"8", "#435db1"},
        {"9", "#3e63dd"}, {"10", "#5472e4"}, {"11", "#9eb1ff"}, {"12", "#d6e1ff"}
    });

    palette->setColorScale("blue", {
        {"1", "#0d1520"}, {"2", "#111927"}, {"3", "#0d2847"}, {"4", "#003362"},
        {"5", "#004074"}, {"6", "#104d87"}, {"7", "#205d9e"}, {"8", "#2870bd"},
        {"9", "#0090ff"}, {"10", "#3b9eff"}, {"11", "#70b8ff"}, {"12", "#c2e6ff"}
    });

    palette->setColorScale("cyan", {
        {"1", "#0b161a"}, {"2", "#101b20"}, {"3", "#082c36"}, {"4", "#003848"},
        {"5", "#004558"}, {"6", "#045468"}, {"7", "#12677e"}, {"8", "#11809c"},
        {"9", "#00a2c7"}, {"10", "#23afd0"}, {"11", "#4ccce6"}, {"12", "#b6ecf7"}
    });

    palette->setColorScale("teal", {
        {"1", "#0d1514"}, {"2", "#111c1b"}, {"3", "#0d2d2a"}, {"4", "#023b37"},
        {"5", "#084843"}, {"6", "#145750"}, {"7", "#1c6961"}, {"8", "#207e73"},
        {"9", "#12a594"}, {"10", "#0eb39e"}, {"11", "#0bd8b6"}, {"12", "#adf0dd"}
    });

    palette->setColorScale("jade", {
        {"1", "#0d1512"}, {"2", "#121c18"}, {"3", "#0f2e22"}, {"4", "#0b3b2c"},
        {"5", "#114837"}, {"6", "#1b5745"}, {"7", "#246854"}, {"8", "#2a7e68"},
        {"9", "#29a383"}, {"10", "#27b08b"}, {"11", "#1fd8a4"}, {"12", "#adf0d4"}
    });

    palette->setColorScale("green", {
        {"1", "#0e1512"}, {"2", "#121b17"}, {"3", "#132d21"}, {"4", "#113b29"},
        {"5", "#174933"}, {"6", "#20573e"}, {"7", "#28684a"}, {"8", "#2f7c57"},
        {"9", "#30a46c"}, {"10", "#33b074"}, {"11", "#3dd68c"}, {"12", "#b1f1cb"}
    });


    palette->setColorScale("grass", {
        {"1", "#0e1511"}, {"2", "#141a15"}, {"3", "#1b2a1e"}, {"4", "#1d3a24"},
        {"5", "#25482d"}, {"6", "#2d5736"}, {"7", "#366740"}, {"8", "#3e7949"},
        {"9", "#46a758"}, {"10", "#53b365"}, {"11", "#71d083"}, {"12", "#c2f0c2"}
    });

    palette->setColorScale("lime", {
        {"1", "#11130c"}, {"2", "#151a10"}, {"3", "#1f2917"}, {"4", "#29371d"},
        {"5", "#334423"}, {"6", "#3d522a"}, {"7", "#496231"}, {"8", "#577538"},
        {"9", "#bdee63"}, {"10", "#d4ff70"}, {"11", "#bde56c"}, {"12", "#e3f7ba"}
    });

    palette->setColorScale("mint", {
        {"1", "#0e1515"}, {"2", "#0f1b1b"}, {"3", "#092c2b"}, {"4", "#003a38"},
        {"5", "#004744"}, {"6", "#105650"}, {"7", "#1e685f"}, {"8", "#277f70"},
        {"9", "#86ead4"}, {"10", "#a8f5e5"}, {"11", "#58d5ba"}, {"12", "#c4f5e1"}
    });

    palette->setColorScale("sky", {
        {"1", "#0d141f"}, {"2", "#111a27"}, {"3", "#112840"}, {"4", "#113555"},
        {"5", "#154467"}, {"6", "#1b537b"}, {"7", "#1f6692"}, {"8", "#197cae"},
        {"9", "#7ce2fe"}, {"10", "#a8eeff"}, {"11", "#75c7f0"}, {"12", "#c2f3ff"}
    });

    return palette;
}

void ColorPalette::setColorScale(const QString &name, const QMap<QString, QColor> &shades)
{
    // Overwrite or insert an entire color scale
    m_colors[name] = shades;
}

void ColorPalette::setColorShade(const QString &scaleName, const QString &shadeKey, const QColor &color)
{
    // Set or overwrite a single shade in a specific scale
    m_colors[scaleName][shadeKey] = color;
}

QColor ColorPalette::shade(const QString &scaleName, const QString &shadeKey) const
{
    // Return the shade color if found, otherwise return a default-constructed QColor (invalid)
    if (m_colors.contains(scaleName))
    {
        const auto &shades = m_colors[scaleName];
        return shades.value(shadeKey, QColor());
    }
    return QColor();
}

bool ColorPalette::hasShade(const QString &scaleName, const QString &shadeKey) const
{
    // Check if a specific shade exists within a scale
    return m_colors.contains(scaleName) && m_colors[scaleName].contains(shadeKey);
}

QStringList ColorPalette::scaleNames() const
{
    // Return the list of available scale names
    return m_colors.keys();
}

QStringList ColorPalette::shadeKeysFor(const QString &scaleName) const
{
    // Return the list of shade keys for a given scale
    return m_colors.contains(scaleName) ? m_colors[scaleName].keys() : QStringList();
}
