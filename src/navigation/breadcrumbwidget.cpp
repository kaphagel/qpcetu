#include "breadcrumbwidget.h"
#include "navigationmanager.h"
#include "../ui/thememanager.h"
#include <QResizeEvent>
#include <QPainter>
#include <QDebug>
#include <QEasingCurve>
#include <QApplication>

BreadcrumbWidget::BreadcrumbWidget(QWidget *parent)
    : QWidget(parent)
    , m_mainLayout(nullptr)
    , m_breadcrumbLayout(nullptr)
    , m_homeButton(nullptr)
    , m_backButton(nullptr)
    , m_overflowButton(nullptr)
    , m_maxVisibleItems(5)
    , m_currentIndex(-1)
    , m_separator("›")
    , m_animationsEnabled(true)
    , m_touchOptimized(true)
    , m_fadeAnimation(nullptr)
    , m_opacityEffect(nullptr)
    , m_navigationManager(nullptr)
{
    setupUI();
    setTouchOptimized(true);
    
    // Connect to theme system
    connect(ThemeManager::instance(), &ThemeManager::themeChanged,
            this, &BreadcrumbWidget::applyIndustrialStyling);
}

BreadcrumbWidget::~BreadcrumbWidget()
{
    clearBreadcrumbs();
}

void BreadcrumbWidget::setupUI()
{
    setFixedHeight(m_touchOptimized ? 64 : 48);
    
    m_mainLayout = new QHBoxLayout(this);
    m_mainLayout->setContentsMargins(12, 8, 12, 8);
    m_mainLayout->setSpacing(m_touchOptimized ? TOUCH_BUTTON_SPACING : STANDARD_BUTTON_SPACING);
    
    // Home button
    m_homeButton = new QPushButton("🏠");
    m_homeButton->setFixedSize(m_touchOptimized ? TOUCH_BUTTON_SIZE : STANDARD_BUTTON_SIZE,
                              m_touchOptimized ? TOUCH_BUTTON_SIZE : STANDARD_BUTTON_SIZE);
    m_homeButton->setToolTip("Home");
    connect(m_homeButton, &QPushButton::clicked, this, &BreadcrumbWidget::homeClicked);
    
    // Back button
    m_backButton = new QPushButton("←");
    m_backButton->setFixedSize(m_touchOptimized ? TOUCH_BUTTON_SIZE : STANDARD_BUTTON_SIZE,
                              m_touchOptimized ? TOUCH_BUTTON_SIZE : STANDARD_BUTTON_SIZE);
    m_backButton->setToolTip("Back");
    connect(m_backButton, &QPushButton::clicked, this, [this]() {
        qDebug() << "BreadcrumbWidget: Back button physically clicked!";
        emit backClicked();
    });
    
    // Overflow button (for long paths)
    m_overflowButton = new QPushButton("...");
    m_overflowButton->setFixedSize(m_touchOptimized ? TOUCH_BUTTON_SIZE : STANDARD_BUTTON_SIZE,
                                  m_touchOptimized ? TOUCH_BUTTON_SIZE : STANDARD_BUTTON_SIZE);
    m_overflowButton->setVisible(false);
    
    // Breadcrumb container
    m_breadcrumbLayout = new QHBoxLayout();
    m_breadcrumbLayout->setSpacing(m_touchOptimized ? TOUCH_BUTTON_SPACING : STANDARD_BUTTON_SPACING);
    m_breadcrumbLayout->setContentsMargins(0, 0, 0, 0);
    
    // Add to main layout
    m_mainLayout->addWidget(m_homeButton);
    m_mainLayout->addWidget(m_backButton);
    m_mainLayout->addWidget(m_overflowButton);
    m_mainLayout->addLayout(m_breadcrumbLayout);
    m_mainLayout->addStretch();
    
    applyIndustrialStyling();
}

void BreadcrumbWidget::setBreadcrumbs(const QStringList &breadcrumbs)
{
    if (m_breadcrumbs == breadcrumbs) {
        return;
    }
    
    clearBreadcrumbs();
    m_breadcrumbs = breadcrumbs;
    m_currentIndex = breadcrumbs.size() - 1;
    
    updateLayout();
    updateButtonStates();
    
    qDebug() << "Breadcrumbs updated:" << breadcrumbs;
}

void BreadcrumbWidget::addBreadcrumb(const QString &title)
{
    m_breadcrumbs.append(title);
    m_currentIndex = m_breadcrumbs.size() - 1;
    updateLayout();
    updateButtonStates();
}

void BreadcrumbWidget::removeBreadcrumb(int index)
{
    if (index >= 0 && index < m_breadcrumbs.size()) {
        m_breadcrumbs.removeAt(index);
        if (m_currentIndex >= index) {
            m_currentIndex = qMax(0, m_currentIndex - 1);
        }
        updateLayout();
        updateButtonStates();
    }
}

void BreadcrumbWidget::clearBreadcrumbs()
{
    // Clear existing buttons and labels
    for (QPushButton *button : m_breadcrumbButtons) {
        m_breadcrumbLayout->removeWidget(button);
        button->deleteLater();
    }
    m_breadcrumbButtons.clear();
    
    for (QLabel *label : m_separatorLabels) {
        m_breadcrumbLayout->removeWidget(label);
        label->deleteLater();
    }
    m_separatorLabels.clear();
    
    m_breadcrumbs.clear();
    m_currentIndex = -1;
    
    updateButtonStates();
}

void BreadcrumbWidget::setTouchOptimized(bool enabled)
{
    if (m_touchOptimized == enabled) {
        return;
    }
    
    m_touchOptimized = enabled;
    
    // Update button sizes
    int buttonSize = enabled ? TOUCH_BUTTON_SIZE : STANDARD_BUTTON_SIZE;
    int spacing = enabled ? TOUCH_BUTTON_SPACING : STANDARD_BUTTON_SPACING;
    
    m_homeButton->setFixedSize(buttonSize, buttonSize);
    m_backButton->setFixedSize(buttonSize, buttonSize);
    m_overflowButton->setFixedSize(buttonSize, buttonSize);
    
    // Update layouts
    m_mainLayout->setSpacing(spacing);
    m_breadcrumbLayout->setSpacing(spacing);
    
    // Update widget height
    setFixedHeight(enabled ? 64 : 48);
    
    // Update breadcrumb buttons
    for (BreadcrumbButton *button : m_breadcrumbButtons) {
        button->setTouchOptimized(enabled);
    }
    
    applyTouchStyling();
}

void BreadcrumbWidget::navigateToIndex(int index)
{
    if (index >= 0 && index < m_breadcrumbs.size()) {
        m_currentIndex = index;
        updateButtonStates();
        emit breadcrumbClicked(index);
    }
}

void BreadcrumbWidget::goHome()
{
    emit homeClicked();
}

void BreadcrumbWidget::goBack()
{
    emit backClicked();
}

void BreadcrumbWidget::setNavigationManager(NavigationManager *manager)
{
    qDebug() << "BreadcrumbWidget::setNavigationManager called with:" << (manager ? "valid manager" : "null manager");
    m_navigationManager = manager;
    if (m_navigationManager) {
        // Connect to navigation signals to update button states
        connect(m_navigationManager, &NavigationManager::navigationStateChanged, 
                this, &BreadcrumbWidget::updateButtonStates);
        qDebug() << "NavigationManager connected to BreadcrumbWidget";
    }
    updateButtonStates();
}

void BreadcrumbWidget::updateLayout()
{
    clearBreadcrumbs();
    
    if (m_breadcrumbs.isEmpty()) {
        m_overflowButton->setVisible(false);
        return;
    }
    
    // Determine visible items
    int startIndex = 0;
    bool showOverflow = false;
    
    if (m_breadcrumbs.size() > m_maxVisibleItems) {
        startIndex = m_breadcrumbs.size() - m_maxVisibleItems;
        showOverflow = true;
    }
    
    m_overflowButton->setVisible(showOverflow);
    
    // Create breadcrumb items
    for (int i = startIndex; i < m_breadcrumbs.size(); ++i) {
        if (i > startIndex) {
            createSeparatorLabel();
        }
        createBreadcrumbButton(m_breadcrumbs[i], i);
    }
    
    updateButtonStates();
}

void BreadcrumbWidget::createBreadcrumbButton(const QString &title, int index)
{
    BreadcrumbButton *button = new BreadcrumbButton(title, index, this);
    button->setTouchOptimized(m_touchOptimized);
    button->setActive(index == m_currentIndex);
    
    connect(button, &QPushButton::clicked, this, [this, index]() {
        navigateToIndex(index);
    });
    
    m_breadcrumbButtons.append(button);
    m_breadcrumbLayout->addWidget(button);
    
    if (m_animationsEnabled) {
        animateItemTransition(button, true);
    }
}

void BreadcrumbWidget::createSeparatorLabel()
{
    QLabel *separator = new QLabel(m_separator);
    separator->setAlignment(Qt::AlignCenter);
    separator->setFixedSize(16, m_touchOptimized ? TOUCH_BUTTON_SIZE : STANDARD_BUTTON_SIZE);
    
    m_separatorLabels.append(separator);
    m_breadcrumbLayout->addWidget(separator);
}

void BreadcrumbWidget::animateItemTransition(QWidget *item, bool fadeIn)
{
    if (!m_animationsEnabled || !item) {
        return;
    }
    
    m_opacityEffect = new QGraphicsOpacityEffect(item);
    item->setGraphicsEffect(m_opacityEffect);
    
    m_fadeAnimation = new QPropertyAnimation(m_opacityEffect, "opacity", this);
    m_fadeAnimation->setDuration(200);
    m_fadeAnimation->setEasingCurve(QEasingCurve::OutCubic);
    
    if (fadeIn) {
        m_fadeAnimation->setStartValue(0.0);
        m_fadeAnimation->setEndValue(1.0);
    } else {
        m_fadeAnimation->setStartValue(1.0);
        m_fadeAnimation->setEndValue(0.0);
    }
    
    connect(m_fadeAnimation, &QPropertyAnimation::finished,
            this, &BreadcrumbWidget::onAnimationFinished);
    
    m_fadeAnimation->start();
}

void BreadcrumbWidget::updateButtonStates()
{
    // Update navigation buttons - use NavigationManager if available
    if (m_navigationManager) {
        bool canGoBack = m_navigationManager->canGoBack();
        qDebug() << "BreadcrumbWidget: NavigationManager canGoBack:" << canGoBack;
        m_backButton->setEnabled(canGoBack);
    } else {
        // Fallback to breadcrumb-based logic
        bool enabled = m_currentIndex > 0;
        qDebug() << "BreadcrumbWidget: Fallback logic - currentIndex:" << m_currentIndex << "enabled:" << enabled;
        m_backButton->setEnabled(enabled);
    }
    
    qDebug() << "BreadcrumbWidget: Back button enabled:" << m_backButton->isEnabled();
    
    // Update breadcrumb button states
    for (BreadcrumbButton *button : m_breadcrumbButtons) {
        button->setActive(button->breadcrumbIndex() == m_currentIndex);
    }
}

void BreadcrumbWidget::applyTouchStyling()
{
    // Apply industrial touch-optimized styling
    QString touchButtonStyle = QString(
        "QPushButton {"
        "  background-color: rgba(0, 229, 255, 0.1);"
        "  border: 1px solid #00E5FF;"
        "  border-radius: %1px;"
        "  color: #00E5FF;"
        "  font-size: %2px;"
        "  font-weight: bold;"
        "  min-width: %3px;"
        "  min-height: %3px;"
        "}"
        "QPushButton:hover {"
        "  background-color: rgba(0, 229, 255, 0.2);"
        "  border: 2px solid #00E5FF;"
        "}"
        "QPushButton:pressed {"
        "  background-color: rgba(0, 229, 255, 0.3);"
        "  border: 2px solid #00E5FF;"
        "}"
        "QPushButton:disabled {"
        "  background-color: rgba(128, 128, 128, 0.1);"
        "  border: 1px solid #808080;"
        "  color: #808080;"
        "}")
        .arg(m_touchOptimized ? 8 : 4)
        .arg(m_touchOptimized ? 14 : 12)
        .arg(m_touchOptimized ? TOUCH_BUTTON_SIZE : STANDARD_BUTTON_SIZE);
    
    m_homeButton->setStyleSheet(touchButtonStyle);
    m_backButton->setStyleSheet(touchButtonStyle);
    m_overflowButton->setStyleSheet(touchButtonStyle);
}

void BreadcrumbWidget::applyIndustrialStyling()
{
    applyTouchStyling();
    
    // Apply theme-based styling for separators
    QString separatorStyle = QString(
        "QLabel {"
        "  color: %1;"
        "  font-size: %2px;"
        "  font-weight: bold;"
        "}")
        .arg(ThemeManager::instance()->color(ThemeManager::Primary).name())
        .arg(m_touchOptimized ? 16 : 14);
    
    for (QLabel *label : m_separatorLabels) {
        label->setStyleSheet(separatorStyle);
    }
}

void BreadcrumbWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    // TODO: Implement responsive breadcrumb hiding for narrow widths
}

void BreadcrumbWidget::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    
    // Draw industrial-style background
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    QColor bgColor = ThemeManager::instance()->color(ThemeManager::MainBackground);
    bgColor.setAlpha(240);
    painter.fillRect(rect(), bgColor);
    
    // Draw subtle border
    painter.setPen(QPen(ThemeManager::instance()->color(ThemeManager::Primary).lighter(150), 1));
    painter.drawLine(0, height() - 1, width(), height() - 1);
}

void BreadcrumbWidget::onBreadcrumbClicked()
{
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        // Find the index of this button
        for (int i = 0; i < m_breadcrumbButtons.size(); ++i) {
            if (m_breadcrumbButtons[i] == button) {
                navigateToIndex(static_cast<BreadcrumbButton*>(button)->breadcrumbIndex());
                break;
            }
        }
    }
}

void BreadcrumbWidget::onAnimationFinished()
{
    if (m_fadeAnimation) {
        m_fadeAnimation->deleteLater();
        m_fadeAnimation = nullptr;
    }
    if (m_opacityEffect) {
        m_opacityEffect->deleteLater();
        m_opacityEffect = nullptr;
    }
}

// BreadcrumbButton Implementation
BreadcrumbButton::BreadcrumbButton(const QString &text, int index, QWidget *parent)
    : QPushButton(text, parent)
    , m_index(index)
    , m_isActive(false)
    , m_isHovered(false)
    , m_touchOptimized(true)
{
    updateStyling();
}

void BreadcrumbButton::setActive(bool active)
{
    if (m_isActive != active) {
        m_isActive = active;
        updateStyling();
    }
}

void BreadcrumbButton::setTouchOptimized(bool enabled)
{
    if (m_touchOptimized != enabled) {
        m_touchOptimized = enabled;
        updateStyling();
    }
}

void BreadcrumbButton::updateStyling()
{
    int buttonHeight = m_touchOptimized ? BreadcrumbWidget::getTouchButtonSize() : BreadcrumbWidget::getStandardButtonSize();
    int fontSize = m_touchOptimized ? 14 : 12;
    
    setFixedHeight(buttonHeight);
    setMinimumWidth(buttonHeight);
    
    QString style;
    if (m_isActive) {
        style = QString(
            "BreadcrumbButton {"
            "  background-color: #00E5FF;"
            "  color: #000000;"
            "  border: 2px solid #00E5FF;"
            "  border-radius: 6px;"
            "  font-size: %1px;"
            "  font-weight: bold;"
            "  padding: 4px 12px;"
            "}"
            "BreadcrumbButton:hover {"
            "  background-color: #00C4E5;"
            "}")
            .arg(fontSize);
    } else {
        style = QString(
            "BreadcrumbButton {"
            "  background-color: rgba(0, 229, 255, 0.1);"
            "  color: #00E5FF;"
            "  border: 1px solid #00E5FF;"
            "  border-radius: 6px;"
            "  font-size: %1px;"
            "  font-weight: bold;"
            "  padding: 4px 12px;"
            "}"
            "BreadcrumbButton:hover {"
            "  background-color: rgba(0, 229, 255, 0.2);"
            "  border: 2px solid #00E5FF;"
            "}")
            .arg(fontSize);
    }
    
    setStyleSheet(style);
}

void BreadcrumbButton::paintEvent(QPaintEvent *event)
{
    QPushButton::paintEvent(event);
}

void BreadcrumbButton::enterEvent(QEvent *event)
{
    m_isHovered = true;
    QPushButton::enterEvent(event);
}

void BreadcrumbButton::leaveEvent(QEvent *event)
{
    m_isHovered = false;
    QPushButton::leaveEvent(event);
}