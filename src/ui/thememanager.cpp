#include "thememanager.h"
#include <QApplication>
#include <QDebug>

ThemeManager *ThemeManager::s_instance = nullptr;

ThemeManager *ThemeManager::instance()
{
    if (!s_instance)
    {
        s_instance = new ThemeManager(qApp);
    }
    return s_instance;
}

ThemeManager::ThemeManager(QObject *parent)
    : QObject(parent), m_currentTheme(Dark), m_settings(new QSettings("QuantumTactical", "SciFiHMI", this))
{
    initializeThemes();
    loadTheme(); // Load saved theme preference
}

void ThemeManager::initializeThemes()
{
    // Dark Theme (Current sci-fi aesthetic) - Optimized for low-light industrial environments
    QMap<ColorRole, QColor> darkTheme;
    darkTheme[MainBackground] = QColor("#0F1419");
    darkTheme[SecondaryBackground] = QColor("#1E2328");
    darkTheme[HeaderBackground] = QColor("#1E2328");
    darkTheme[CardBackground] = QColor("#252A2E");
    darkTheme[StatusStripBackground] = QColor("#0F1419");

    darkTheme[PrimaryText] = QColor("#FFFFFF");
    darkTheme[SecondaryText] = QColor("#B0BEC5");
    darkTheme[AccentText] = QColor("#00E5FF");
    darkTheme[StatusText] = QColor("#78909C");

    darkTheme[Primary] = QColor("#00E5FF");
    darkTheme[Success] = QColor("#4CAF50");
    darkTheme[Warning] = QColor("#FF9800");
    darkTheme[Error] = QColor("#F44336");

    darkTheme[ButtonBackground] = QColor("#2D3748");
    darkTheme[ButtonHover] = QColor("#4A5568");
    darkTheme[ButtonPressed] = QColor("#2B6CB0");
    darkTheme[BorderColor] = QColor("#4A5568");
    darkTheme[FocusColor] = QColor("#00E5FF");

    darkTheme[ControllerActive] = QColor("#4CAF50");
    darkTheme[ControllerInactive] = QColor("#616161");
    darkTheme[ControllerFault] = QColor("#F44336");
    darkTheme[DataGood] = QColor("#4CAF50");
    darkTheme[DataStale] = QColor("#FF9800");
    darkTheme[DataError] = QColor("#F44336");

    m_themes[Dark] = darkTheme;

    // Light Theme - Optimized for bright industrial environments
    QMap<ColorRole, QColor> lightTheme;
    lightTheme[MainBackground] = QColor("#FAFAFA");
    lightTheme[SecondaryBackground] = QColor("#FFFFFF");
    lightTheme[HeaderBackground] = QColor("#E3F2FD");
    lightTheme[CardBackground] = QColor("#FFFFFF");
    lightTheme[StatusStripBackground] = QColor("#F5F5F5");

    lightTheme[PrimaryText] = QColor("#212121");
    lightTheme[SecondaryText] = QColor("#757575");
    lightTheme[AccentText] = QColor("#1976D2");
    lightTheme[StatusText] = QColor("#666666");

    lightTheme[Primary] = QColor("#1976D2");
    lightTheme[Success] = QColor("#388E3C");
    lightTheme[Warning] = QColor("#F57C00");
    lightTheme[Error] = QColor("#D32F2F");

    lightTheme[ButtonBackground] = QColor("#E0E0E0");
    lightTheme[ButtonHover] = QColor("#BDBDBD");
    lightTheme[ButtonPressed] = QColor("#1976D2");
    lightTheme[BorderColor] = QColor("#BDBDBD");
    lightTheme[FocusColor] = QColor("#1976D2");

    lightTheme[ControllerActive] = QColor("#388E3C");
    lightTheme[ControllerInactive] = QColor("#9E9E9E");
    lightTheme[ControllerFault] = QColor("#D32F2F");
    lightTheme[DataGood] = QColor("#388E3C");
    lightTheme[DataStale] = QColor("#F57C00");
    lightTheme[DataError] = QColor("#D32F2F");

    m_themes[Light] = lightTheme;

    // High Contrast Theme - For accessibility and harsh lighting conditions
    QMap<ColorRole, QColor> highContrastTheme;
    highContrastTheme[MainBackground] = QColor("#000000");
    highContrastTheme[SecondaryBackground] = QColor("#1A1A1A");
    highContrastTheme[HeaderBackground] = QColor("#000000");
    highContrastTheme[CardBackground] = QColor("#1A1A1A");
    highContrastTheme[StatusStripBackground] = QColor("#000000");

    highContrastTheme[PrimaryText] = QColor("#FFFFFF");
    highContrastTheme[SecondaryText] = QColor("#CCCCCC");
    highContrastTheme[AccentText] = QColor("#00FFFF");
    highContrastTheme[StatusText] = QColor("#AAAAAA");

    highContrastTheme[Primary] = QColor("#00FFFF");
    highContrastTheme[Success] = QColor("#00FF00");
    highContrastTheme[Warning] = QColor("#FFFF00");
    highContrastTheme[Error] = QColor("#FF0000");

    highContrastTheme[ButtonBackground] = QColor("#333333");
    highContrastTheme[ButtonHover] = QColor("#666666");
    highContrastTheme[ButtonPressed] = QColor("#00FFFF");
    highContrastTheme[BorderColor] = QColor("#FFFFFF");
    highContrastTheme[FocusColor] = QColor("#00FFFF");

    highContrastTheme[ControllerActive] = QColor("#00FF00");
    highContrastTheme[ControllerInactive] = QColor("#808080");
    highContrastTheme[ControllerFault] = QColor("#FF0000");
    highContrastTheme[DataGood] = QColor("#00FF00");
    highContrastTheme[DataStale] = QColor("#FFFF00");
    highContrastTheme[DataError] = QColor("#FF0000");

    m_themes[HighContrast] = highContrastTheme;

    // Apple Light Theme - iOS/iPadOS inspired design
    QMap<ColorRole, QColor> appleLightTheme;
    appleLightTheme[MainBackground] = QColor("#F2F2F7");      // systemGroupedBackground
    appleLightTheme[SecondaryBackground] = QColor("#FFFFFF"); // systemBackground
    appleLightTheme[HeaderBackground] = QColor("#F9F9F9");    // systemBackground with slight tint
    appleLightTheme[CardBackground] = QColor("#FFFFFF");      // systemBackground
    appleLightTheme[StatusStripBackground] = QColor("#F2F2F7");

    appleLightTheme[PrimaryText] = QColor("#000000");   // label
    appleLightTheme[SecondaryText] = QColor("#3C3C43"); // secondaryLabel
    appleLightTheme[AccentText] = QColor("#007AFF");    // systemBlue
    appleLightTheme[StatusText] = QColor("#8E8E93");    // tertiaryLabel

    appleLightTheme[Primary] = QColor("#007AFF"); // systemBlue
    appleLightTheme[Success] = QColor("#34C759"); // systemGreen
    appleLightTheme[Warning] = QColor("#FF9500"); // systemOrange
    appleLightTheme[Error] = QColor("#FF3B30");   // systemRed

    appleLightTheme[ButtonBackground] = QColor("#007AFF"); // systemBlue
    appleLightTheme[ButtonHover] = QColor("#0056CC");      // darker systemBlue
    appleLightTheme[ButtonPressed] = QColor("#003D99");    // pressed systemBlue
    appleLightTheme[BorderColor] = QColor("#C6C6C8");      // separator
    appleLightTheme[FocusColor] = QColor("#007AFF");       // systemBlue

    appleLightTheme[ControllerActive] = QColor("#34C759");   // systemGreen
    appleLightTheme[ControllerInactive] = QColor("#8E8E93"); // systemGray
    appleLightTheme[ControllerFault] = QColor("#FF3B30");    // systemRed
    appleLightTheme[DataGood] = QColor("#34C759");
    appleLightTheme[DataStale] = QColor("#FF9500");
    appleLightTheme[DataError] = QColor("#FF3B30");

    m_themes[AppleLight] = appleLightTheme;

    // Apple Dark Theme - iOS/iPadOS Dark Mode inspired
    QMap<ColorRole, QColor> appleDarkTheme;
    appleDarkTheme[MainBackground] = QColor("#000000");      // systemBackground
    appleDarkTheme[SecondaryBackground] = QColor("#1C1C1E"); // systemGroupedBackground
    appleDarkTheme[HeaderBackground] = QColor("#1C1C1E");    // systemGroupedBackground
    appleDarkTheme[CardBackground] = QColor("#2C2C2E");      // secondarySystemGroupedBackground
    appleDarkTheme[StatusStripBackground] = QColor("#000000");

    appleDarkTheme[PrimaryText] = QColor("#FFFFFF");   // label
    appleDarkTheme[SecondaryText] = QColor("#EBEBF5"); // secondaryLabel
    appleDarkTheme[AccentText] = QColor("#0A84FF");    // systemBlue (dark)
    appleDarkTheme[StatusText] = QColor("#8E8E93");    // tertiaryLabel

    appleDarkTheme[Primary] = QColor("#0A84FF"); // systemBlue (dark)
    appleDarkTheme[Success] = QColor("#30D158"); // systemGreen (dark)
    appleDarkTheme[Warning] = QColor("#FF9F0A"); // systemOrange (dark)
    appleDarkTheme[Error] = QColor("#FF453A");   // systemRed (dark)

    appleDarkTheme[ButtonBackground] = QColor("#0A84FF"); // systemBlue (dark)
    appleDarkTheme[ButtonHover] = QColor("#409CFF");      // lighter systemBlue
    appleDarkTheme[ButtonPressed] = QColor("#64B5F6");    // pressed systemBlue
    appleDarkTheme[BorderColor] = QColor("#38383A");      // separator (dark)
    appleDarkTheme[FocusColor] = QColor("#0A84FF");       // systemBlue (dark)

    appleDarkTheme[ControllerActive] = QColor("#30D158");   // systemGreen (dark)
    appleDarkTheme[ControllerInactive] = QColor("#8E8E93"); // systemGray
    appleDarkTheme[ControllerFault] = QColor("#FF453A");    // systemRed (dark)
    appleDarkTheme[DataGood] = QColor("#30D158");
    appleDarkTheme[DataStale] = QColor("#FF9F0A");
    appleDarkTheme[DataError] = QColor("#FF453A");

    m_themes[AppleDark] = appleDarkTheme;

    // Load initial theme
    loadThemeColors(m_currentTheme);
}

void ThemeManager::setTheme(Theme theme)
{
    if (m_currentTheme != theme)
    {
        m_currentTheme = theme;
        loadThemeColors(theme);
        saveTheme();
        emit themeChanged(theme);
        qDebug() << "Theme changed to:" << themeName();
    }
}

QString ThemeManager::themeName() const
{
    switch (m_currentTheme)
    {
    case Dark:
        return "Dark";
    case Light:
        return "Light";
    case HighContrast:
        return "High Contrast";
    case AppleLight:
        return "Apple Light";
    case AppleDark:
        return "Apple Dark";
    default:
        return "Unknown";
    }
}

QColor ThemeManager::color(ColorRole role) const
{
    return m_currentColors.value(role, QColor("#FF00FF")); // Magenta as error indicator
}

QString ThemeManager::colorString(ColorRole role) const
{
    return color(role).name();
}

void ThemeManager::loadThemeColors(Theme theme)
{
    if (m_themes.contains(theme))
    {
        m_currentColors = m_themes[theme];
    }
    else
    {
        qWarning() << "Theme not found:" << theme;
        m_currentColors = m_themes[Dark]; // Fallback to dark theme
    }
}

QString ThemeManager::generateStyleSheet() const
{
    return QString(
               "QMainWindow { "
               "  background-color: %1; "
               "  color: %2; "
               "}"
               "QWidget#headerBar { "
               "  background-color: %3; "
               "  border-bottom: 2px solid %4; "
               "}"
               "QLabel#titleLabel { "
               "  font-size: 22px; "
               "  font-weight: bold; "
               "  color: %5; "
               "}"
               "QLabel#connectionStatus { "
               "  font-size: 16px; "
               "  color: %6; "
               "  font-weight: bold; "
               "}"
               "QLabel#userLabel, QLabel#dateTimeLabel { "
               "  font-size: 16px; "
               "  color: %7; "
               "}"
               "QWidget#statusStrip { "
               "  background-color: %8; "
               "}"
               "QLabel#statusLabel { "
               "  font-size: 15px; "
               "  color: %9; "
               "  font-weight: 500; "
               "}"
               "QLabel#sectionTitle { "
               "  font-size: 20px; "
               "  font-weight: bold; "
               "  color: %10; "
               "}")
        .arg(
            colorString(MainBackground),        // %1
            colorString(PrimaryText),           // %2
            colorString(HeaderBackground),      // %3
            colorString(Primary),               // %4
            colorString(AccentText),            // %5
            colorString(Success),               // %6
            colorString(SecondaryText),         // %7
            colorString(StatusStripBackground), // %8
            colorString(StatusText),            // %9
            colorString(AccentText)             // %10
        );
}

QString ThemeManager::generateButtonStyle(const QString &objectName) const
{
    QString selector = objectName.isEmpty() ? "QPushButton" : QString("QPushButton#%1").arg(objectName);

    return QString(
               "%1 { "
               "  background-color: %2; "
               "  border: 2px solid %3; "
               "  border-radius: 12px; "
               "  color: %4; "
               "  font-size: 16px; "
               "  font-weight: bold; "
               "  min-height: 60px; "
               "  min-width: 120px; "
               "}"
               "%1:hover { "
               "  background-color: %5; "
               "  border-color: %6; "
               "}"
               "%1:pressed { "
               "  background-color: %7; "
               "  border-color: %8; "
               "}")
        .arg(
            selector,
            colorString(ButtonBackground), // %2
            colorString(BorderColor),      // %3
            colorString(PrimaryText),      // %4
            colorString(ButtonHover),      // %5
            colorString(Primary),          // %6
            colorString(ButtonPressed),    // %7
            colorString(FocusColor)        // %8
        );
}

QString ThemeManager::generateCardStyle() const
{
    return QString(
               "QWidget { "
               "  background-color: %1; "
               "  border: 1px solid %2; "
               "  border-radius: 12px; "
               "  color: %3; "
               "}")
        .arg(
            colorString(CardBackground),
            colorString(BorderColor),
            colorString(PrimaryText));
}

QString ThemeManager::generateHeaderStyle() const
{
    return QString(
               "QWidget#headerBar { "
               "  background-color: %1; "
               "  border-bottom: 2px solid %2; "
               "  min-height: 80px; "
               "}")
        .arg(
            colorString(HeaderBackground),
            colorString(Primary));
}

void ThemeManager::saveTheme()
{
    m_settings->setValue("theme", static_cast<int>(m_currentTheme));
    m_settings->sync();
}

void ThemeManager::loadTheme()
{
    int themeValue = m_settings->value("theme", static_cast<int>(Dark)).toInt();
    setTheme(static_cast<Theme>(themeValue));
}