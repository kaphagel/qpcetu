#ifndef NAVIGATIONMANAGER_H
#define NAVIGATIONMANAGER_H

#include <QObject>
#include <QStack>
#include <QStackedWidget>
#include <QWidget>
#include <QHash>
#include <QStringList>
#include <QVariantMap>

/**
 * @brief Professional Navigation Manager for Industrial HMI
 * 
 * Implements Command + Observer patterns for robust page navigation
 * with touch-optimized breadcrumbs, back/forward history, and 
 * industrial-grade navigation state management.
 * 
 * Features:
 * - Command pattern for navigation operations
 * - Observer pattern for navigation state changes
 * - Touch-optimized breadcrumb system
 * - Back/forward navigation history
 * - Page lifecycle management
 * - Industrial confirmation dialogs
 * - Animation support for page transitions
 */
class NavigationManager : public QObject
{
    Q_OBJECT

public:
    /**
     * @brief Navigation page identifiers for type safety
     */
    enum class PageId {
        Overview = 0,
        Dashboard = 1,
        Graphs = 2,
        Settings = 3,
        UdpResponse = 4,
        ControllerDetails = 5,
        Diagnostics = 6,
        Alarms = 7,
        Reports = 8
    };
    Q_ENUM(PageId)

    /**
     * @brief Navigation transition types for animations
     */
    enum class TransitionType {
        None,
        SlideLeft,
        SlideRight,
        SlideUp,
        SlideDown,
        Fade,
        Push,
        Pop
    };
    Q_ENUM(TransitionType)

    /**
     * @brief Navigation context for advanced routing
     */
    struct NavigationContext {
        PageId fromPage;
        PageId toPage;
        QVariantMap parameters;
        TransitionType transition;
        bool requiresConfirmation;
        QString confirmationMessage;
    };

public:
    explicit NavigationManager(QStackedWidget *stackedWidget, QWidget *parent = nullptr);
    ~NavigationManager();

    // Core Navigation API
    void registerPage(PageId pageId, QWidget *page, const QString &title, const QString &icon = QString());
    void navigateToPage(PageId pageId, const QVariantMap &parameters = QVariantMap(), 
                       TransitionType transition = TransitionType::SlideLeft);
    void goBack();
    void goForward();
    void goHome();
    void navigateToHistoryIndex(int index);

    // Navigation State
    PageId currentPage() const { return m_currentPage; }
    bool canGoBack() const { return !m_backStack.isEmpty(); }
    bool canGoForward() const { return !m_forwardStack.isEmpty(); }
    QStringList breadcrumbPath() const;
    QString currentPageTitle() const;

    // Page Lifecycle
    void setPageVisible(PageId pageId, bool visible);
    void setPageEnabled(PageId pageId, bool enabled);
    void refreshCurrentPage();

    // Navigation Guards
    void setNavigationGuard(PageId pageId, std::function<bool(const NavigationContext&)> guard);
    void setConfirmationRequired(PageId fromPage, PageId toPage, const QString &message);

    // Touch Optimization
    void setTouchOptimized(bool enabled) { m_touchOptimized = enabled; }
    void setBreadcrumbsVisible(bool visible);

signals:
    // Navigation Events
    void pageChanged(PageId fromPage, PageId toPage);
    void navigationStateChanged();
    void breadcrumbsChanged(const QStringList &breadcrumbs);
    
    // Page Lifecycle Events
    void pageAboutToShow(PageId pageId, const QVariantMap &parameters);
    void pageShown(PageId pageId);
    void pageAboutToHide(PageId pageId);
    void pageHidden(PageId pageId);

    // Error Events
    void navigationError(const QString &error);
    void confirmationRequired(const QString &message, std::function<void(bool)> callback);

public slots:
    void handlePageRequest(PageId pageId, const QVariantMap &parameters = QVariantMap());
    void handleBackRequest();
    void handleHomeRequest();

private slots:
    void onTransitionFinished();
    void onConfirmationResult(bool confirmed);

private:
    // Page Management
    struct PageInfo {
        QWidget *widget;
        QString title;
        QString icon;
        bool visible;
        bool enabled;
        std::function<bool(const NavigationContext&)> guard;
    };

    void executeNavigation(const NavigationContext &context);
    bool validateNavigation(const NavigationContext &context);
    void updateNavigationState();
    void performTransition(PageId fromPage, PageId toPage, TransitionType transition);
    void updateBreadcrumbs();

    // Core Components
    QStackedWidget *m_stackedWidget;
    QHash<PageId, PageInfo> m_pages;
    
    // Navigation State
    PageId m_currentPage;
    QStack<PageId> m_backStack;
    QStack<PageId> m_forwardStack;
    QHash<QPair<PageId, PageId>, QString> m_confirmationMessages;
    
    // Configuration
    bool m_touchOptimized;
    bool m_breadcrumbsVisible;
    bool m_animationsEnabled;
    
    // Current Navigation Context
    NavigationContext m_pendingNavigation;
    bool m_navigationInProgress;
};

/**
 * @brief Navigation Command for Command Pattern implementation
 */
class NavigationCommand : public QObject
{
    Q_OBJECT

public:
    explicit NavigationCommand(NavigationManager *manager, 
                              NavigationManager::PageId pageId,
                              const QVariantMap &parameters = QVariantMap(),
                              QObject *parent = nullptr);

    void execute();
    void undo();
    bool canExecute() const;

signals:
    void executed();
    void undone();
    void failed(const QString &error);

private:
    NavigationManager *m_manager;
    NavigationManager::PageId m_targetPage;
    NavigationManager::PageId m_previousPage;
    QVariantMap m_parameters;
    bool m_executed;
};

// Hash function for PageId enum to work with QHash
inline uint qHash(NavigationManager::PageId key, uint seed = 0) Q_DECL_NOTHROW
{
    return qHash(static_cast<uint>(key), seed);
}

#endif // NAVIGATIONMANAGER_H