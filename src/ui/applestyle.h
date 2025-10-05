#ifndef APPLESTYLE_H
#define APPLESTYLE_H

#include <QString>
#include <QColor>

/**
 * @brief Apple Human Interface Guidelines styling utilities
 *
 * Provides Apple-inspired design system constants and helpers
 * for creating iOS/iPadOS-like interfaces in Qt Widgets.
 */
class AppleStyle
{
public:
    // Apple's 8pt grid system (based on iOS point system)
    static constexpr int SPACING_XS = 4;   // 0.5 units
    static constexpr int SPACING_S = 8;    // 1 unit (base)
    static constexpr int SPACING_M = 16;   // 2 units
    static constexpr int SPACING_L = 24;   // 3 units
    static constexpr int SPACING_XL = 32;  // 4 units
    static constexpr int SPACING_XXL = 40; // 5 units

    // Apple's corner radius system (iOS standard)
    static constexpr int RADIUS_S = 8;   // Small elements (buttons, inputs)
    static constexpr int RADIUS_M = 12;  // Medium elements (cards, panels)
    static constexpr int RADIUS_L = 16;  // Large elements (modals, sheets)
    static constexpr int RADIUS_XL = 20; // Extra large elements

    // Apple's touch target system (Apple Accessibility Guidelines)
    static constexpr int TOUCH_TARGET_MIN = 44;         // 44pt minimum (Apple standard)
    static constexpr int TOUCH_TARGET_COMFORTABLE = 60; // Industrial comfortable size

    // Apple Typography Scale (iOS standard sizes)
    static constexpr int FONT_LARGE_TITLE = 34; // largeTitle
    static constexpr int FONT_TITLE1 = 28;      // title1
    static constexpr int FONT_TITLE2 = 22;      // title2
    static constexpr int FONT_TITLE3 = 20;      // title3
    static constexpr int FONT_BODY = 17;        // body (base)
    static constexpr int FONT_CALLOUT = 16;     // callout
    static constexpr int FONT_SUBHEAD = 15;     // subheadline
    static constexpr int FONT_FOOTNOTE = 13;    // footnote
    static constexpr int FONT_CAPTION1 = 12;    // caption1
    static constexpr int FONT_CAPTION2 = 11;    // caption2

    // Apple Color System Constants (semantic colors)
    static const QString SYSTEM_BLUE_LIGHT;   // #007AFF
    static const QString SYSTEM_BLUE_DARK;    // #0A84FF
    static const QString SYSTEM_GREEN_LIGHT;  // #34C759
    static const QString SYSTEM_GREEN_DARK;   // #30D158
    static const QString SYSTEM_RED_LIGHT;    // #FF3B30
    static const QString SYSTEM_RED_DARK;     // #FF453A
    static const QString SYSTEM_ORANGE_LIGHT; // #FF9500
    static const QString SYSTEM_ORANGE_DARK;  // #FF9F0A

    // Apple-style button stylesheet generator
    static QString generatePrimaryButtonStyle(const QColor &backgroundColor,
                                              const QColor &textColor,
                                              int cornerRadius = RADIUS_M);

    static QString generateSecondaryButtonStyle(const QColor &borderColor,
                                                const QColor &textColor,
                                                const QColor &backgroundColor,
                                                int cornerRadius = RADIUS_M);

    static QString generateCardStyle(const QColor &backgroundColor,
                                     const QColor &borderColor,
                                     int cornerRadius = RADIUS_M);

    // Apple-style elevation (shadow) effects
    static QString generateElevationStyle(int elevation = 1);

    // Apple Typography helpers
    static QString generateTitleStyle(int fontSize = FONT_TITLE1, bool bold = true);
    static QString generateBodyStyle(int fontSize = FONT_BODY, bool regular = true);
    static QString generateCaptionStyle(int fontSize = FONT_CAPTION1, bool light = true);

    // Apple Motion (easing functions)
    static QString generateTransitionStyle(int durationMs = 300);
    static QString generateSpringTransition(int durationMs = 400);

    // Apple-specific component generators
    static QString generateNavigationBarStyle(const QColor &backgroundColor, const QColor &textColor);
    static QString generateSwitchStyle(const QColor &activeColor, const QColor &inactiveColor);
    static QString generateSegmentedControlStyle(const QColor &selectedColor, const QColor &unselectedColor);

private:
    AppleStyle() = default;
};

#endif // APPLESTYLE_H