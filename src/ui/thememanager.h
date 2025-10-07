#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>
#include <QColor>
#include <QMap>
#include <QString>
#include <QSettings>

/**
 * @brief Theme management system for industrial HMI
 *
 * Provides centralized theme switching between dark/light modes
 * with industrial-grade color palettes optimized for touch interfaces.
 */
class ThemeManager : public QObject
{
    Q_OBJECT

public:
    enum Theme
    {
        Light,
        Dark
    };
    Q_ENUM(Theme)

    enum ColorRole
    {
        // Background colors
        MainBackground,
        SecondaryBackground,
        HeaderBackground,
        CardBackground,
        StatusStripBackground,

        // Text colors
        PrimaryText,
        SecondaryText,
        AccentText,
        StatusText,

        // Accent colors
        Primary, // Main brand color (cyan)
        Success, // Green for success states
        Warning, // Orange for warnings
        Error,   // Red for errors

        // Interactive colors
        ButtonBackground,
        ButtonHover,
        ButtonPressed,
        BorderColor,
        FocusColor,

        // Industrial specific
        ControllerActive,
        ControllerInactive,
        ControllerFault,
        DataGood,
        DataStale,
        DataError
    };
    Q_ENUM(ColorRole)

    static ThemeManager *instance();

    // Theme management
    void setTheme(Theme theme);
    Theme currentTheme() const { return m_currentTheme; }
    QString themeName() const;

    // Color access
    QColor color(ColorRole role) const;
    QString colorString(ColorRole role) const;

    // Style generation
    QString generateStyleSheet() const;
    QString generateButtonStyle(const QString &objectName = "") const;
    QString generateCardStyle() const;
    QString generateHeaderStyle() const;

    // Settings persistence
    void saveTheme();
    void loadTheme();

signals:
    void themeChanged(Theme newTheme);

private:
    explicit ThemeManager(QObject *parent = nullptr);
    void initializeThemes();
    void loadThemeColors(Theme theme);

    Theme m_currentTheme;
    QMap<ColorRole, QColor> m_currentColors;
    QMap<Theme, QMap<ColorRole, QColor>> m_themes;
    QSettings *m_settings;

    static ThemeManager *s_instance;
};

// Convenience macros for theme colors
#define THEME_COLOR(role) ThemeManager::instance()->color(ThemeManager::role)
#define THEME_COLOR_STR(role) ThemeManager::instance()->colorString(ThemeManager::role)

#endif // THEMEMANAGER_H