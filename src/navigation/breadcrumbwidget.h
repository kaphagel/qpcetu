#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QStringList>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>

// Forward declarations
class BreadcrumbButton;
class NavigationManager;

/**
 * @brief Touch-optimized breadcrumb navigation widget for Industrial HMI
 * 
 * Features:
 * - Touch-friendly button sizing (minimum 44x44px)
 * - High contrast industrial styling
 * - Smooth animations for state changes
 * - Support for long breadcrumb paths with scrolling
 * - Accessibility support for industrial environments
 * - Theme-aware styling
 */
class BreadcrumbWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BreadcrumbWidget(QWidget *parent = nullptr);
    ~BreadcrumbWidget();

    // Breadcrumb Management
    void setBreadcrumbs(const QStringList &breadcrumbs);
    void addBreadcrumb(const QString &title);
    void removeBreadcrumb(int index);
    void clearBreadcrumbs();
    
    // Configuration
    void setMaxVisibleItems(int maxItems) { m_maxVisibleItems = maxItems; updateLayout(); }
    void setAnimationsEnabled(bool enabled) { m_animationsEnabled = enabled; }
    void setTouchOptimized(bool enabled);
    void setSeparator(const QString &separator) { m_separator = separator; updateLayout(); }
    void setNavigationManager(NavigationManager *manager);
    
    // State
    QStringList breadcrumbs() const { return m_breadcrumbs; }
    int currentIndex() const { return m_currentIndex; }
    bool isEmpty() const { return m_breadcrumbs.isEmpty(); }

signals:
    void breadcrumbClicked(int index);
    void homeClicked();
    void backClicked();

public slots:
    void navigateToIndex(int index);
    void goHome();
    void goBack();

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onBreadcrumbClicked();
    void onAnimationFinished();

private:
    void setupUI();
    void updateLayout();
    void createBreadcrumbButton(const QString &title, int index);
    void createSeparatorLabel();
    void animateItemTransition(QWidget *item, bool fadeIn);
    void updateButtonStates();
    void applyTouchStyling();
    void applyIndustrialStyling();

    // Core Components
    QHBoxLayout *m_mainLayout;
    QHBoxLayout *m_breadcrumbLayout;
    
    // Navigation Buttons
    QPushButton *m_homeButton;
    QPushButton *m_backButton;
    QPushButton *m_overflowButton;
    
    // Breadcrumb Data
    QStringList m_breadcrumbs;
    QList<BreadcrumbButton*> m_breadcrumbButtons;
    QList<QLabel*> m_separatorLabels;
    
    // Configuration
    int m_maxVisibleItems;
    int m_currentIndex;
    QString m_separator;
    bool m_animationsEnabled;
    bool m_touchOptimized;
    
    // Animation
    QPropertyAnimation *m_fadeAnimation;
    QGraphicsOpacityEffect *m_opacityEffect;
    
    // Navigation
    NavigationManager *m_navigationManager;
    
    // Styling
    static const int TOUCH_BUTTON_SIZE = 44;
    static const int TOUCH_BUTTON_SPACING = 8;
    static const int STANDARD_BUTTON_SIZE = 32;
    static const int STANDARD_BUTTON_SPACING = 4;

public:
    static int getTouchButtonSize() { return TOUCH_BUTTON_SIZE; }
    static int getStandardButtonSize() { return STANDARD_BUTTON_SIZE; }
};

/**
 * @brief Custom breadcrumb button with industrial styling
 */
class BreadcrumbButton : public QPushButton
{
    Q_OBJECT

public:
    explicit BreadcrumbButton(const QString &text, int index, QWidget *parent = nullptr);
    
    int breadcrumbIndex() const { return m_index; }
    void setActive(bool active);
    void setTouchOptimized(bool enabled);

protected:
    void paintEvent(QPaintEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    void updateStyling();
    
    int m_index;
    bool m_isActive;
    bool m_isHovered;
    bool m_touchOptimized;
};
