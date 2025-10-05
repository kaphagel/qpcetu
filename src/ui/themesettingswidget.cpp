#include "themesettingswidget.h"
#include <QGroupBox>

ThemeSettingsWidget::ThemeSettingsWidget(QWidget *parent)
    : QWidget(parent)
{
    setupUI();
    setupStyling();

    // Connect to theme manager
    connect(ThemeManager::instance(), &ThemeManager::themeChanged,
            this, &ThemeSettingsWidget::onThemeChanged);

    // Update initial state
    updateThemeButtons();
}

void ThemeSettingsWidget::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(24, 24, 24, 24);
    m_mainLayout->setSpacing(20);

    // Title
    m_titleLabel = new QLabel("Interface Theme");
    m_titleLabel->setObjectName("sectionTitle");
    m_mainLayout->addWidget(m_titleLabel);

    // Description
    m_descriptionLabel = new QLabel(
        "Choose the interface theme that works best for your environment. "
        "Dark theme reduces eye strain in low-light conditions, while light theme "
        "provides better visibility in bright industrial environments.");
    m_descriptionLabel->setObjectName("descriptionText");
    m_descriptionLabel->setWordWrap(true);
    m_mainLayout->addWidget(m_descriptionLabel);

    // Theme selection buttons
    QGroupBox *themeGroup = new QGroupBox("Available Themes");
    themeGroup->setObjectName("themeGroup");
    QVBoxLayout *groupLayout = new QVBoxLayout(themeGroup);
    groupLayout->setSpacing(16);

    m_themeGroup = new QButtonGroup(this);

    // Dark Theme Button
    m_darkThemeBtn = new QPushButton();
    m_darkThemeBtn->setCheckable(true);
    m_darkThemeBtn->setObjectName("themeButton");
    m_darkThemeBtn->setText("🌙 Dark Theme\nOptimized for low-light industrial environments");
    m_darkThemeBtn->setMinimumHeight(80);
    m_themeGroup->addButton(m_darkThemeBtn, static_cast<int>(ThemeManager::Dark));
    groupLayout->addWidget(m_darkThemeBtn);

    // Light Theme Button
    m_lightThemeBtn = new QPushButton();
    m_lightThemeBtn->setCheckable(true);
    m_lightThemeBtn->setObjectName("themeButton");
    m_lightThemeBtn->setText("☀️ Light Theme\nOptimized for bright industrial environments");
    m_lightThemeBtn->setMinimumHeight(80);
    m_themeGroup->addButton(m_lightThemeBtn, static_cast<int>(ThemeManager::Light));
    groupLayout->addWidget(m_lightThemeBtn);

    // High Contrast Theme Button
    m_highContrastBtn = new QPushButton();
    m_highContrastBtn->setCheckable(true);
    m_highContrastBtn->setObjectName("themeButton");
    m_highContrastBtn->setText("🔆 High Contrast\nMaximum visibility and accessibility");
    m_highContrastBtn->setMinimumHeight(80);
    m_themeGroup->addButton(m_highContrastBtn, static_cast<int>(ThemeManager::HighContrast));
    groupLayout->addWidget(m_highContrastBtn);

    m_mainLayout->addWidget(themeGroup);

    // Connect button clicks
    connect(m_themeGroup, QOverload<int>::of(&QButtonGroup::idClicked),
            [this](int id)
            {
                ThemeManager::instance()->setTheme(static_cast<ThemeManager::Theme>(id));
            });

    // Preview area
    m_previewFrame = new QFrame();
    m_previewFrame->setObjectName("previewFrame");
    m_previewFrame->setMinimumHeight(120);

    QVBoxLayout *previewLayout = new QVBoxLayout(m_previewFrame);
    m_previewLabel = new QLabel("Theme Preview");
    m_previewLabel->setObjectName("previewLabel");
    m_previewLabel->setAlignment(Qt::AlignCenter);
    previewLayout->addWidget(m_previewLabel);

    m_mainLayout->addWidget(m_previewFrame);

    m_mainLayout->addStretch();
}

void ThemeSettingsWidget::setupStyling()
{
    // This will be updated when theme changes
    onThemeChanged(ThemeManager::instance()->currentTheme());
}

void ThemeSettingsWidget::onThemeChanged(ThemeManager::Theme theme)
{
    // Update widget styling based on current theme
    ThemeManager *tm = ThemeManager::instance();

    setStyleSheet(QString(
                      "QLabel#sectionTitle { "
                      "  font-size: 24px; "
                      "  font-weight: bold; "
                      "  color: %1; "
                      "  margin-bottom: 8px; "
                      "}"
                      "QLabel#descriptionText { "
                      "  font-size: 16px; "
                      "  color: %2; "
                      "  line-height: 1.4; "
                      "}"
                      "QGroupBox { "
                      "  font-size: 18px; "
                      "  font-weight: bold; "
                      "  color: %3; "
                      "  border: 2px solid %4; "
                      "  border-radius: 12px; "
                      "  margin-top: 12px; "
                      "  padding-top: 12px; "
                      "}"
                      "QGroupBox::title { "
                      "  subcontrol-origin: margin; "
                      "  left: 20px; "
                      "  padding: 0 8px 0 8px; "
                      "}"
                      "QPushButton#themeButton { "
                      "  background-color: %5; "
                      "  border: 2px solid %6; "
                      "  border-radius: 12px; "
                      "  color: %7; "
                      "  font-size: 16px; "
                      "  font-weight: bold; "
                      "  text-align: left; "
                      "  padding: 16px; "
                      "}"
                      "QPushButton#themeButton:hover { "
                      "  background-color: %8; "
                      "  border-color: %9; "
                      "}"
                      "QPushButton#themeButton:checked { "
                      "  background-color: %10; "
                      "  border-color: %11; "
                      "  border-width: 3px; "
                      "}"
                      "QFrame#previewFrame { "
                      "  background-color: %12; "
                      "  border: 2px solid %13; "
                      "  border-radius: 12px; "
                      "}"
                      "QLabel#previewLabel { "
                      "  font-size: 18px; "
                      "  font-weight: bold; "
                      "  color: %14; "
                      "}")
                      .arg(
                          tm->colorString(ThemeManager::AccentText),       // %1
                          tm->colorString(ThemeManager::SecondaryText),    // %2
                          tm->colorString(ThemeManager::AccentText),       // %3
                          tm->colorString(ThemeManager::BorderColor),      // %4
                          tm->colorString(ThemeManager::ButtonBackground), // %5
                          tm->colorString(ThemeManager::BorderColor),      // %6
                          tm->colorString(ThemeManager::PrimaryText),      // %7
                          tm->colorString(ThemeManager::ButtonHover),      // %8
                          tm->colorString(ThemeManager::Primary),          // %9
                          tm->colorString(ThemeManager::ButtonPressed),    // %10
                          tm->colorString(ThemeManager::FocusColor),       // %11
                          tm->colorString(ThemeManager::CardBackground),   // %12
                          tm->colorString(ThemeManager::Primary),          // %13
                          tm->colorString(ThemeManager::AccentText)        // %14
                          ));

    // Update preview text
    QString themeName = tm->themeName();
    m_previewLabel->setText(QString("Current Theme: %1\nBackground: %2")
                                .arg(themeName)
                                .arg(tm->colorString(ThemeManager::MainBackground)));

    updateThemeButtons();
}

void ThemeSettingsWidget::updateThemeButtons()
{
    ThemeManager::Theme currentTheme = ThemeManager::instance()->currentTheme();

    m_darkThemeBtn->setChecked(currentTheme == ThemeManager::Dark);
    m_lightThemeBtn->setChecked(currentTheme == ThemeManager::Light);
    m_highContrastBtn->setChecked(currentTheme == ThemeManager::HighContrast);
}