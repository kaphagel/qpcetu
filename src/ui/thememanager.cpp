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
    : QObject(parent), m_currentTheme(Light), m_settings(new QSettings("QuantumTactical", "SciFiHMI", this))
{
    initializeThemes();
    loadTheme(); // Load saved theme preference
}

void ThemeManager::initializeThemes()
{
    // Light Theme - Clean iPhone-like design for industrial HMI
    QMap<ColorRole, QColor> lightTheme;
    lightTheme[MainBackground] = QColor("#FFFFFF");      // systemBackground (pure white - iOS standard)
    lightTheme[SecondaryBackground] = QColor("#F2F2F7"); // systemGroupedBackground
    lightTheme[HeaderBackground] = QColor("#FFFFFF");    // same as main for seamless look
    lightTheme[CardBackground] = QColor("#F2F2F7");      // systemGroupedBackground (subtle contrast)
    lightTheme[StatusStripBackground] = QColor("#FFFFFF");

    lightTheme[PrimaryText] = QColor("#000000");   // label
    lightTheme[SecondaryText] = QColor("#3C3C43"); // secondaryLabel
    lightTheme[AccentText] = QColor("#007AFF");    // systemBlue
    lightTheme[StatusText] = QColor("#8E8E93");    // tertiaryLabel

    lightTheme[Primary] = QColor("#007AFF"); // systemBlue
    lightTheme[Success] = QColor("#34C759"); // systemGreen
    lightTheme[Warning] = QColor("#FF9500"); // systemOrange
    lightTheme[Error] = QColor("#FF3B30");   // systemRed

    lightTheme[ButtonBackground] = QColor("#007AFF"); // systemBlue
    lightTheme[ButtonHover] = QColor("#E5E5EA");      // systemGray5 (more visible on white)
    lightTheme[ButtonPressed] = QColor("#D1D1D6");    // systemGray4 (darker for pressed)
    lightTheme[BorderColor] = QColor("#C6C6C8");      // separator (not used in borderless design)
    lightTheme[FocusColor] = QColor("#007AFF");       // systemBlue

    lightTheme[ControllerActive] = QColor("#34C759");   // systemGreen
    lightTheme[ControllerInactive] = QColor("#8E8E93"); // systemGray
    lightTheme[ControllerFault] = QColor("#FF3B30");    // systemRed
    lightTheme[DataGood] = QColor("#34C759");
    lightTheme[DataStale] = QColor("#FF9500");
    lightTheme[DataError] = QColor("#FF3B30");

    m_themes[Light] = lightTheme;

    // Dark Theme - Clean iPhone-like dark design for industrial HMI
    QMap<ColorRole, QColor> darkTheme;
    // Industry-standard dark mode (not pure black - reduces eye strain)
    darkTheme[MainBackground] = QColor("#1C1C1E");      // Apple systemBackground (dark gray)
    darkTheme[SecondaryBackground] = QColor("#2C2C2E"); // systemGroupedBackground
    darkTheme[HeaderBackground] = QColor("#1C1C1E");    // same as main for seamless look
    darkTheme[CardBackground] = QColor("#3A3A3C");      // secondarySystemGroupedBackground (lighter)
    darkTheme[StatusStripBackground] = QColor("#1C1C1E");

    darkTheme[PrimaryText] = QColor("#FFFFFF");   // label
    darkTheme[SecondaryText] = QColor("#EBEBF5"); // secondaryLabel
    darkTheme[AccentText] = QColor("#0A84FF");    // systemBlue (dark)
    darkTheme[StatusText] = QColor("#8E8E93");    // tertiaryLabel

    darkTheme[Primary] = QColor("#0A84FF"); // systemBlue (dark)
    darkTheme[Success] = QColor("#30D158"); // systemGreen (dark)
    darkTheme[Warning] = QColor("#FF9F0A"); // systemOrange (dark)
    darkTheme[Error] = QColor("#FF453A");   // systemRed (dark)

    darkTheme[ButtonBackground] = QColor("#0A84FF"); // systemBlue (dark)
    darkTheme[ButtonHover] = QColor("#2C2C2E");      // subtle dark gray (not blue!)
    darkTheme[ButtonPressed] = QColor("#3A3A3C");    // slightly lighter gray
    darkTheme[BorderColor] = QColor("#38383A");      // separator (not used in borderless design)
    darkTheme[FocusColor] = QColor("#0A84FF");       // systemBlue (dark)

    darkTheme[ControllerActive] = QColor("#30D158");   // systemGreen (dark)
    darkTheme[ControllerInactive] = QColor("#8E8E93"); // systemGray
    darkTheme[ControllerFault] = QColor("#FF453A");    // systemRed (dark)
    darkTheme[DataGood] = QColor("#30D158");
    darkTheme[DataStale] = QColor("#FF9F0A");
    darkTheme[DataError] = QColor("#FF453A");

    m_themes[Dark] = darkTheme;

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
    case Light:
        return "Light";
    case Dark:
        return "Dark";
    default:
        return "Light"; // Default to light theme
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
               "  border: none; "
               "  border-radius: 12px; "
               "  color: %4; "
               "  font-size: 16px; "
               "  font-weight: bold; "
               "  min-height: 60px; "
               "  min-width: 120px; "
               "}"
               "%1:hover { "
               "  background-color: %5; "
               "}"
               "%1:pressed { "
               "  background-color: %7; "
               "}")
        .arg(
            selector,
            colorString(ButtonBackground), // %2
            colorString(PrimaryText),      // %4
            colorString(ButtonHover),      // %5
            colorString(ButtonPressed)     // %7
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
    int themeValue = m_settings->value("theme", static_cast<int>(Light)).toInt();
    setTheme(static_cast<Theme>(themeValue));
}