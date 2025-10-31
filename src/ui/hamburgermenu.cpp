#include "hamburgermenu.h"
#include "thememanager.h"
#include "../navigation/navigationmanager.h"
#include <QResizeEvent>
#include <QPainter>
#include <QDebug>
#include <QEasingCurve>
#include <QApplication>
#include <QScrollBar>
#include <QMouseEvent>

HamburgerMenu::HamburgerMenu(QWidget *parent)
    : QWidget(parent)
    , m_overlay(nullptr)
    , m_menuPanel(nullptr)
    , m_scrollArea(nullptr)
    , m_mainLayout(nullptr)
    , m_buttonLayout(nullptr)
    , m_headerWidget(nullptr)
    , m_headerLayout(nullptr)
    , m_titleLabel(nullptr)
    , m_closeButton(nullptr)
    , m_overviewButton(nullptr)
    , m_dashboardButton(nullptr)
    , m_graphsButton(nullptr)
    , m_settingsButton(nullptr)
    , m_networkButton(nullptr)
    , m_industrialButton(nullptr)
    , m_slideAnimation(nullptr)
    , m_fadeAnimation(nullptr)
    , m_overlayEffect(nullptr)
    , m_navigationManager(nullptr)
    , m_touchOptimized(true)
    , m_isMenuVisible(false)
    , m_animationDuration(DEFAULT_ANIMATION_DURATION)
    , m_menuWidth(DEFAULT_MENU_WIDTH)
{
    setupUI();
    setTouchOptimized(true);
    
    // Ensure the hamburger menu fills the entire parent initially
    if (parent) {
        setGeometry(0, 0, parent->width(), parent->height());
    }
    
    // Connect to theme system
    connect(ThemeManager::instance(), &ThemeManager::themeChanged,
            this, &HamburgerMenu::onThemeChanged);
    
    // Install event filter on parent to handle outside clicks
    if (parent) {
        parent->installEventFilter(this);
    }
}

HamburgerMenu::~HamburgerMenu()
{
    // Cleanup animations
    if (m_slideAnimation) {
        m_slideAnimation->stop();
    }
    if (m_fadeAnimation) {
        m_fadeAnimation->stop();
    }
}

void HamburgerMenu::setupUI()
{
    // Create overlay for background dimming
    createOverlay();
    
    // Create main menu panel
    m_menuPanel = new QWidget(this);
    m_menuPanel->setFixedWidth(m_menuWidth);
    m_menuPanel->move(-m_menuWidth, 0); // Start hidden off-screen
    
    // Main layout for menu panel
    m_mainLayout = new QVBoxLayout(m_menuPanel);
    m_mainLayout->setContentsMargins(0, 0, 0, 0);
    m_mainLayout->setSpacing(0);
    
    // Create header
    m_headerWidget = new QWidget();
    m_headerLayout = new QHBoxLayout(m_headerWidget);
    m_headerLayout->setContentsMargins(20, 16, 16, 16);
    m_headerLayout->setSpacing(12);
    
    // Title
    m_titleLabel = new QLabel("🧭 Navigation");
    m_titleLabel->setStyleSheet("font-size: 20px; font-weight: bold;");
    
    // Close button
    m_closeButton = new QPushButton("✕");
    m_closeButton->setFixedSize(36, 36);
    m_closeButton->setStyleSheet(
        "QPushButton {"
        "    background: transparent;"
        "    border: none;"
        "    font-size: 18px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background: rgba(255, 255, 255, 0.1);"
        "}"
        "QPushButton:pressed {"
        "    background: rgba(255, 255, 255, 0.2);"
        "}"
    );
    connect(m_closeButton, &QPushButton::clicked, this, &HamburgerMenu::hideMenu);
    
    m_headerLayout->addWidget(m_titleLabel);
    m_headerLayout->addStretch();
    m_headerLayout->addWidget(m_closeButton);
    
    // Create scroll area for navigation buttons
    m_scrollArea = new QScrollArea();
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_scrollArea->setFrameStyle(QFrame::NoFrame);
    
    // Container for navigation buttons
    QWidget *buttonContainer = new QWidget();
    m_buttonLayout = new QVBoxLayout(buttonContainer);
    m_buttonLayout->setContentsMargins(16, 20, 16, 20);
    m_buttonLayout->setSpacing(m_touchOptimized ? TOUCH_BUTTON_SPACING : STANDARD_BUTTON_SPACING);
    
    // Create navigation buttons
    createNavigationButtons();
    
    // Add buttons to layout
    m_buttonLayout->addWidget(m_overviewButton);
    m_buttonLayout->addWidget(m_dashboardButton);
    m_buttonLayout->addWidget(m_graphsButton);
    m_buttonLayout->addWidget(m_settingsButton);
    m_buttonLayout->addWidget(m_networkButton);
    m_buttonLayout->addWidget(m_industrialButton);
    m_buttonLayout->addWidget(m_webBrowserButton);
    m_buttonLayout->addStretch(); // Push buttons to top
    
    m_scrollArea->setWidget(buttonContainer);
    
    // Add components to main layout
    m_mainLayout->addWidget(m_headerWidget);
    m_mainLayout->addWidget(m_scrollArea, 1);
    
    // Create animations
    m_slideAnimation = new QPropertyAnimation(m_menuPanel, "pos", this);
    m_slideAnimation->setDuration(m_animationDuration);
    m_slideAnimation->setEasingCurve(QEasingCurve::OutCubic);
    connect(m_slideAnimation, &QPropertyAnimation::finished,
            this, &HamburgerMenu::onAnimationFinished);
    
    m_fadeAnimation = new QPropertyAnimation(m_overlayEffect, "opacity", this);
    m_fadeAnimation->setDuration(m_animationDuration);
    m_fadeAnimation->setEasingCurve(QEasingCurve::OutCubic);
    
    // Apply initial styling
    applyIndustrialStyling();
    
    // Hide menu initially
    setVisible(false);
}

void HamburgerMenu::createOverlay()
{
    m_overlay = new QWidget(this);
    m_overlay->setStyleSheet("background: rgba(0, 0, 0, 0.5);");
    m_overlay->installEventFilter(this);
    
    // Add opacity effect for fade animation
    m_overlayEffect = new QGraphicsOpacityEffect();
    m_overlayEffect->setOpacity(0.0);
    m_overlay->setGraphicsEffect(m_overlayEffect);
}

void HamburgerMenu::createNavigationButtons()
{
    int buttonHeight = m_touchOptimized ? TOUCH_BUTTON_HEIGHT : STANDARD_BUTTON_HEIGHT;
    
    // Overview button
    m_overviewButton = new QPushButton("🏠 Overview");
    m_overviewButton->setFixedHeight(buttonHeight);
    m_overviewButton->setProperty("pageId", 0);
    connect(m_overviewButton, &QPushButton::clicked, this, &HamburgerMenu::onNavigationButtonClicked);
    
    // Dashboard button
    m_dashboardButton = new QPushButton("📊 Dashboard");
    m_dashboardButton->setFixedHeight(buttonHeight);
    m_dashboardButton->setProperty("pageId", 1);
    connect(m_dashboardButton, &QPushButton::clicked, this, &HamburgerMenu::onNavigationButtonClicked);
    
    // Graphs button
    m_graphsButton = new QPushButton("📈 Graphs");
    m_graphsButton->setFixedHeight(buttonHeight);
    m_graphsButton->setProperty("pageId", 2);
    connect(m_graphsButton, &QPushButton::clicked, this, &HamburgerMenu::onNavigationButtonClicked);
    
    // Settings button
    m_settingsButton = new QPushButton("⚙️ Settings");
    m_settingsButton->setFixedHeight(buttonHeight);
    m_settingsButton->setProperty("pageId", 3);
    connect(m_settingsButton, &QPushButton::clicked, this, &HamburgerMenu::onNavigationButtonClicked);
    
    // Network button
    m_networkButton = new QPushButton("🌐 Network");
    m_networkButton->setFixedHeight(buttonHeight);
    m_networkButton->setProperty("pageId", 4);
    connect(m_networkButton, &QPushButton::clicked, this, &HamburgerMenu::onNavigationButtonClicked);
    
    // Industrial button
    m_industrialButton = new QPushButton("🏭 Industrial");
    m_industrialButton->setFixedHeight(buttonHeight);
    m_industrialButton->setProperty("pageId", 5);
    connect(m_industrialButton, &QPushButton::clicked, this, &HamburgerMenu::onNavigationButtonClicked);
    
    // Web Browser button (for testing/comparison)
    m_webBrowserButton = new QPushButton("🌐 Web Browser");
    m_webBrowserButton->setFixedHeight(buttonHeight);
    m_webBrowserButton->setProperty("pageId", 9);
    connect(m_webBrowserButton, &QPushButton::clicked, this, &HamburgerMenu::onNavigationButtonClicked);
}

void HamburgerMenu::setNavigationManager(NavigationManager *manager)
{
    qDebug() << "HamburgerMenu::setNavigationManager called with:" << (manager ? "valid manager" : "null manager");
    m_navigationManager = manager;
    updateButtonStates();
}

void HamburgerMenu::showMenu()
{
    if (m_isMenuVisible) return;
    
    qDebug() << "Showing hamburger menu";
    m_isMenuVisible = true;
    setVisible(true);
    raise();
    
    startShowAnimation();
    emit menuShown();
}

void HamburgerMenu::hideMenu()
{
    if (!m_isMenuVisible) return;
    
    qDebug() << "Hiding hamburger menu";
    m_isMenuVisible = false;
    
    startHideAnimation();
    emit menuHidden();
}

void HamburgerMenu::toggleMenu()
{
    if (m_isMenuVisible) {
        hideMenu();
    } else {
        showMenu();
    }
}

bool HamburgerMenu::isVisible() const
{
    return m_isMenuVisible;
}

void HamburgerMenu::startShowAnimation()
{
    // Position overlay and menu
    m_overlay->setGeometry(0, 0, parentWidget()->width(), parentWidget()->height());
    m_menuPanel->setGeometry(-m_menuWidth, 0, m_menuWidth, parentWidget()->height());
    
    // Animate menu slide in
    m_slideAnimation->setStartValue(QPoint(-m_menuWidth, 0));
    m_slideAnimation->setEndValue(QPoint(0, 0));
    m_slideAnimation->start();
    
    // Animate overlay fade in
    m_fadeAnimation->setStartValue(0.0);
    m_fadeAnimation->setEndValue(1.0);
    m_fadeAnimation->start();
}

void HamburgerMenu::startHideAnimation()
{
    // Animate menu slide out
    m_slideAnimation->setStartValue(QPoint(0, 0));
    m_slideAnimation->setEndValue(QPoint(-m_menuWidth, 0));
    m_slideAnimation->start();
    
    // Animate overlay fade out
    m_fadeAnimation->setStartValue(1.0);
    m_fadeAnimation->setEndValue(0.0);
    m_fadeAnimation->start();
}

void HamburgerMenu::onAnimationFinished()
{
    if (!m_isMenuVisible) {
        setVisible(false);
    }
}

void HamburgerMenu::onNavigationButtonClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (!button) return;
    
    int pageId = button->property("pageId").toInt();
    qDebug() << "Navigation button clicked, pageId:" << pageId;
    
    if (m_navigationManager) {
        // Navigate to the selected page
        m_navigationManager->navigateToPage(static_cast<NavigationManager::PageId>(pageId));
    }
    
    // Hide menu after navigation
    hideMenu();
    
    emit navigationRequested(pageId);
}

void HamburgerMenu::setTouchOptimized(bool enabled)
{
    m_touchOptimized = enabled;
    
    if (m_buttonLayout) {
        int spacing = enabled ? TOUCH_BUTTON_SPACING : STANDARD_BUTTON_SPACING;
        int buttonHeight = enabled ? TOUCH_BUTTON_HEIGHT : STANDARD_BUTTON_HEIGHT;
        
        m_buttonLayout->setSpacing(spacing);
        
        // Update button heights
        if (m_overviewButton) m_overviewButton->setFixedHeight(buttonHeight);
        if (m_dashboardButton) m_dashboardButton->setFixedHeight(buttonHeight);
        if (m_graphsButton) m_graphsButton->setFixedHeight(buttonHeight);
        if (m_settingsButton) m_settingsButton->setFixedHeight(buttonHeight);
        if (m_networkButton) m_networkButton->setFixedHeight(buttonHeight);
    }
}

void HamburgerMenu::applyIndustrialStyling()
{
    ThemeManager *themeManager = ThemeManager::instance();
    
    // Menu background with industrial panel styling
    setStyleSheet(QString(
        "HamburgerMenu {"
        "    background-color: %1;"
        "    border-right: 2px solid %2;"
        "}"
    ).arg(themeManager->colorString(ThemeManager::CardBackground), 
          themeManager->colorString(ThemeManager::BorderColor)));
    
    // Apply clean, minimal button styling to all navigation buttons
    // White background with subtle hover effects for content-focused design
    QString buttonStyle = QString(
        "QPushButton {"
        "    background-color: transparent;"
        "    color: %1;"
        "    border: none;"
        "    padding: 12px 20px;"
        "    text-align: left;"
        "    font-size: 16px;"
        "    font-weight: 500;"
        "    min-height: 44px;"
        "    border-radius: 8px;"
        "}"
        "QPushButton:hover {"
        "    background-color: %2;"
        "}"
        "QPushButton:pressed {"
        "    background-color: %3;"
        "}"
    ).arg(themeManager->colorString(ThemeManager::PrimaryText),
          themeManager->colorString(ThemeManager::ButtonHover),
          themeManager->colorString(ThemeManager::ButtonPressed));
    
    // Apply to all navigation buttons
    if (m_overviewButton) m_overviewButton->setStyleSheet(buttonStyle);
    if (m_dashboardButton) m_dashboardButton->setStyleSheet(buttonStyle);
    if (m_graphsButton) m_graphsButton->setStyleSheet(buttonStyle);
    if (m_settingsButton) m_settingsButton->setStyleSheet(buttonStyle);
    if (m_networkButton) m_networkButton->setStyleSheet(buttonStyle);
    if (m_industrialButton) m_industrialButton->setStyleSheet(buttonStyle);
    if (m_webBrowserButton) m_webBrowserButton->setStyleSheet(buttonStyle);
    
    // Close button with special industrial accent
    QString closeButtonStyle = QString(
        "QPushButton {"
        "    background-color: %1;"
        "    color: white;"
        "    border: none;"
        "    font-size: 18px;"
        "    font-weight: bold;"
        "    min-height: 44px;"
        "}"
        "QPushButton:hover {"
        "    background-color: %3;"
        "}"
    ).arg(themeManager->colorString(ThemeManager::MainBackground),
          themeManager->colorString(ThemeManager::ButtonHover));
    
    if (m_closeButton) {
        m_closeButton->setStyleSheet(closeButtonStyle);
    }
}

void HamburgerMenu::updateButtonStates()
{
    // Could add current page highlighting here if needed
    // For now, all buttons are always enabled
}

void HamburgerMenu::onThemeChanged()
{
    applyIndustrialStyling();
}

void HamburgerMenu::setAnimationDuration(int milliseconds)
{
    m_animationDuration = milliseconds;
    if (m_slideAnimation) {
        m_slideAnimation->setDuration(milliseconds);
    }
    if (m_fadeAnimation) {
        m_fadeAnimation->setDuration(milliseconds);
    }
}

void HamburgerMenu::setMenuWidth(int width)
{
    m_menuWidth = width;
    if (m_menuPanel) {
        m_menuPanel->setFixedWidth(width);
    }
}

void HamburgerMenu::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    // Base implementation - overlay and menu panel handle their own painting
}

void HamburgerMenu::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    
    // Ensure the hamburger menu fills the entire parent widget
    if (parentWidget()) {
        setGeometry(0, 0, parentWidget()->width(), parentWidget()->height());
        
        // Update overlay size if it exists
        if (m_overlay) {
            m_overlay->setGeometry(0, 0, width(), height());
        }
        
        // Update menu panel height if it exists
        if (m_menuPanel) {
            m_menuPanel->setFixedHeight(height());
            
            // Update position if menu is currently visible
            if (m_isMenuVisible) {
                m_menuPanel->setGeometry(0, 0, m_menuWidth, height());
            } else {
                m_menuPanel->setGeometry(-m_menuWidth, 0, m_menuWidth, height());
            }
        }
    }
}

void HamburgerMenu::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    // Prevent event propagation
}

bool HamburgerMenu::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == m_overlay && event->type() == QEvent::MouseButtonPress) {
        // Click on overlay should close menu
        hideMenu();
        return true;
    }
    
    if (obj == parentWidget() && m_isMenuVisible) {
        if (event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if (!m_menuPanel->geometry().contains(mouseEvent->pos())) {
                // Click outside menu should close it
                hideMenu();
                return true;
            }
        }
    }
    
    return QWidget::eventFilter(obj, event);
}