#ifndef HAMBURGERMENU_H
#define HAMBURGERMENU_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QPropertyAnimation>
#include <QGraphicsOpacityEffect>
#include <QFrame>
#include <QScrollArea>

// Forward declarations
class NavigationManager;
class ThemeManager;

/**
 * @brief Touch-optimized hamburger menu for Industrial HMI navigation
 * 
 * Features:
 * - Slide-out animation from left side
 * - Touch-friendly button sizing (minimum 60x60px)
 * - High contrast industrial styling
 * - Theme-aware appearance
 * - Smooth animations with industrial feel
 * - Support for large button sets with scrolling
 */
class HamburgerMenu : public QWidget
{
    Q_OBJECT

public:
    explicit HamburgerMenu(QWidget *parent = nullptr);
    ~HamburgerMenu();

    // Navigation Integration
    void setNavigationManager(NavigationManager *manager);
    
    // Menu State
    void showMenu();
    void hideMenu();
    void toggleMenu();
    bool isVisible() const;
    
    // Configuration
    void setTouchOptimized(bool enabled);
    void setAnimationDuration(int milliseconds);
    void setMenuWidth(int width);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    bool eventFilter(QObject *obj, QEvent *event) override;

signals:
    void menuShown();
    void menuHidden();
    void navigationRequested(int pageId);

private slots:
    void onNavigationButtonClicked();
    void onAnimationFinished();
    void onThemeChanged();

private:
    void setupUI();
    void createNavigationButtons();
    void createOverlay();
    void startShowAnimation();
    void startHideAnimation();
    void applyIndustrialStyling();
    void updateButtonStates();

    // Core Components
    QWidget *m_overlay;
    QWidget *m_menuPanel;
    QScrollArea *m_scrollArea;
    QVBoxLayout *m_mainLayout;
    QVBoxLayout *m_buttonLayout;
    
    // Header
    QWidget *m_headerWidget;
    QHBoxLayout *m_headerLayout;
    QLabel *m_titleLabel;
    QPushButton *m_closeButton;
    
    // Navigation Buttons
    QPushButton *m_overviewButton;
    QPushButton *m_dashboardButton;
    QPushButton *m_graphsButton;
    QPushButton *m_settingsButton;
    QPushButton *m_networkButton;
    QPushButton *m_industrialButton;
    QPushButton *m_webBrowserButton;
    
    // Animation
    QPropertyAnimation *m_slideAnimation;
    QPropertyAnimation *m_fadeAnimation;
    QGraphicsOpacityEffect *m_overlayEffect;
    
    // Navigation
    NavigationManager *m_navigationManager;
    
    // Configuration
    bool m_touchOptimized;
    bool m_isMenuVisible;
    int m_animationDuration;
    int m_menuWidth;
    
    // Styling Constants
    static const int TOUCH_BUTTON_HEIGHT = 60;
    static const int TOUCH_BUTTON_SPACING = 12;
    static const int STANDARD_BUTTON_HEIGHT = 44;
    static const int STANDARD_BUTTON_SPACING = 8;
    static const int DEFAULT_MENU_WIDTH = 280;
    static const int DEFAULT_ANIMATION_DURATION = 300;
};

#endif // HAMBURGERMENU_H