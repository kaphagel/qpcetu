#include "applestyle.h"

// Apple Color System Constants (iOS semantic colors)
const QString AppleStyle::SYSTEM_BLUE_LIGHT = "#007AFF";
const QString AppleStyle::SYSTEM_BLUE_DARK = "#0A84FF";
const QString AppleStyle::SYSTEM_GREEN_LIGHT = "#34C759";
const QString AppleStyle::SYSTEM_GREEN_DARK = "#30D158";
const QString AppleStyle::SYSTEM_RED_LIGHT = "#FF3B30";
const QString AppleStyle::SYSTEM_RED_DARK = "#FF453A";
const QString AppleStyle::SYSTEM_ORANGE_LIGHT = "#FF9500";
const QString AppleStyle::SYSTEM_ORANGE_DARK = "#FF9F0A";

QString AppleStyle::generatePrimaryButtonStyle(const QColor &backgroundColor,
                                               const QColor &textColor,
                                               int cornerRadius)
{
    return QString(
               "QPushButton { "
               "  background-color: %1; "
               "  color: %2; "
               "  border: none; "
               "  border-radius: %3px; "
               "  font-weight: 600; "
               "  font-size: 17px; "
               "  padding: %4px %5px; "
               "  min-height: %6px; "
               "  min-width: 88px; "
               "} "
               "QPushButton:hover { "
               "  background-color: %7; "
               "} "
               "QPushButton:pressed { "
               "  background-color: %8; "
               "  transform: scale(0.95); "
               "}")
        .arg(
            backgroundColor.name(),             // %1
            textColor.name(),                   // %2
            QString::number(cornerRadius),      // %3
            QString::number(SPACING_M),         // %4 vertical padding
            QString::number(SPACING_L),         // %5 horizontal padding
            QString::number(TOUCH_TARGET_MIN),  // %6 minimum height
            backgroundColor.darker(110).name(), // %7 hover
            backgroundColor.darker(120).name()  // %8 pressed
        );
}

QString AppleStyle::generateSecondaryButtonStyle(const QColor &borderColor,
                                                 const QColor &textColor,
                                                 const QColor &backgroundColor,
                                                 int cornerRadius)
{
    return QString(
               "QPushButton { "
               "  background-color: %1; "
               "  color: %2; "
               "  border: 1px solid %3; "
               "  border-radius: %4px; "
               "  font-weight: 400; "
               "  font-size: 17px; "
               "  padding: %5px %6px; "
               "  min-height: %7px; "
               "  min-width: 88px; "
               "} "
               "QPushButton:hover { "
               "  background-color: %8; "
               "  border-color: %9; "
               "} "
               "QPushButton:pressed { "
               "  background-color: %10; "
               "  transform: scale(0.95); "
               "}")
        .arg(
            backgroundColor.name(),              // %1
            textColor.name(),                    // %2
            borderColor.name(),                  // %3
            QString::number(cornerRadius),       // %4
            QString::number(SPACING_M),          // %5 vertical padding
            QString::number(SPACING_L),          // %6 horizontal padding
            QString::number(TOUCH_TARGET_MIN),   // %7 minimum height
            backgroundColor.lighter(105).name(), // %8 hover background
            borderColor.darker(110).name(),      // %9 hover border
            backgroundColor.lighter(110).name()  // %10 pressed background
        );
}

QString AppleStyle::generateCardStyle(const QColor &backgroundColor,
                                      const QColor &borderColor,
                                      int cornerRadius)
{
    return QString(
               "QWidget { "
               "  background-color: %1; "
               "  border: 1px solid %2; "
               "  border-radius: %3px; "
               "  padding: %4px; "
               "} "
               "QWidget:hover { "
               "  border-color: %5; "
               "}")
        .arg(
            backgroundColor.name(),        // %1
            borderColor.name(),            // %2
            QString::number(cornerRadius), // %3
            QString::number(SPACING_M),    // %4 padding
            borderColor.darker(110).name() // %5 hover border
        );
}

QString AppleStyle::generateElevationStyle(int elevation)
{
    // Apple-style subtle shadows
    QString shadowColor;
    QString shadowBlur;
    QString shadowOffset;

    switch (elevation)
    {
    case 1:
        shadowColor = "rgba(0, 0, 0, 0.1)";
        shadowBlur = "4px";
        shadowOffset = "0px 1px";
        break;
    case 2:
        shadowColor = "rgba(0, 0, 0, 0.15)";
        shadowBlur = "8px";
        shadowOffset = "0px 2px";
        break;
    case 3:
        shadowColor = "rgba(0, 0, 0, 0.2)";
        shadowBlur = "12px";
        shadowOffset = "0px 4px";
        break;
    default:
        shadowColor = "rgba(0, 0, 0, 0.05)";
        shadowBlur = "2px";
        shadowOffset = "0px 1px";
    }

    return QString(
        "QWidget { "
        "  border: none; "
        "}");
    // Note: Qt Widgets doesn't support box-shadow directly
    // For real shadows, we'd need to use QGraphicsDropShadowEffect programmatically
}

QString AppleStyle::generateTitleStyle(int fontSize, bool bold)
{
    return QString(
               "font-family: -apple-system, system-ui, 'SF Pro Display', sans-serif;"
               "font-size: %1px;"
               "font-weight: %2;"
               "line-height: 1.2;")
        .arg(fontSize)
        .arg(bold ? "600" : "400");
}

QString AppleStyle::generateBodyStyle(int fontSize, bool regular)
{
    return QString(
               "font-family: -apple-system, system-ui, 'SF Pro Text', sans-serif;"
               "font-size: %1px;"
               "font-weight: %2;"
               "line-height: 1.4;")
        .arg(fontSize)
        .arg(regular ? "400" : "300");
}

QString AppleStyle::generateCaptionStyle(int fontSize, bool light)
{
    return QString(
               "font-family: -apple-system, system-ui, 'SF Pro Text', sans-serif;"
               "font-size: %1px;"
               "font-weight: %2;"
               "line-height: 1.3;"
               "opacity: 0.7;")
        .arg(fontSize)
        .arg(light ? "300" : "400");
}

QString AppleStyle::generateTransitionStyle(int durationMs)
{
    // Apple's standard easing curve
    return QString(
               "transition: all %1ms cubic-bezier(0.25, 0.1, 0.25, 1);")
        .arg(durationMs);
}

QString AppleStyle::generateSpringTransition(int durationMs)
{
    // Apple's spring animation curve
    return QString(
               "transition: all %1ms cubic-bezier(0.68, -0.55, 0.265, 1.55);")
        .arg(durationMs);
}

QString AppleStyle::generateNavigationBarStyle(const QColor &backgroundColor, const QColor &textColor)
{
    return QString(
               "background-color: %1;"
               "border-bottom: 1px solid rgba(0, 0, 0, 0.1);"
               "padding: %2px %3px;"
               "min-height: %4px;"
               "%5"
               "%6")
        .arg(backgroundColor.name())
        .arg(SPACING_S)
        .arg(SPACING_M)
        .arg(TOUCH_TARGET_MIN)
        .arg(generateTitleStyle(FONT_TITLE3, true))
        .arg(generateTransitionStyle(300));
}

QString AppleStyle::generateSwitchStyle(const QColor &activeColor, const QColor &inactiveColor)
{
    return QString(
               "border-radius: %1px;"
               "background-color: %2;"
               "border: none;"
               "min-width: %3px;"
               "min-height: %4px;"
               "%5")
        .arg(RADIUS_L)
        .arg(inactiveColor.name())
        .arg(TOUCH_TARGET_MIN + 8)
        .arg(RADIUS_L * 2)
        .arg(generateTransitionStyle(200));
}

QString AppleStyle::generateSegmentedControlStyle(const QColor &selectedColor, const QColor &unselectedColor)
{
    return QString(
               "border-radius: %1px;"
               "background-color: %2;"
               "border: 1px solid %3;"
               "padding: %4px %5px;"
               "min-height: %6px;"
               "%7"
               "%8")
        .arg(RADIUS_S)
        .arg(unselectedColor.name())
        .arg(selectedColor.name())
        .arg(SPACING_S)
        .arg(SPACING_M)
        .arg(TOUCH_TARGET_MIN - 12)
        .arg(generateBodyStyle(FONT_SUBHEAD))
        .arg(generateTransitionStyle(200));
}