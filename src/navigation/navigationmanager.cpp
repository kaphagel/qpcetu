#include "navigationmanager.h"
#include <QPropertyAnimation>
#include <QEasingCurve>
#include <QMessageBox>
#include <QApplication>
#include <QDebug>

NavigationManager::NavigationManager(QStackedWidget *stackedWidget, QWidget *parent)
    : QObject(parent)
    , m_stackedWidget(stackedWidget)
    , m_currentPage(PageId::Overview)
    , m_touchOptimized(true)
    , m_breadcrumbsVisible(true)
    , m_animationsEnabled(true)
    , m_navigationInProgress(false)
{
    Q_ASSERT(m_stackedWidget);
    
    // Connect stacked widget signals
    connect(m_stackedWidget, QOverload<int>::of(&QStackedWidget::currentChanged),
            this, [this](int index) {
                // Find PageId for the current widget
                for (auto it = m_pages.constBegin(); it != m_pages.constEnd(); ++it) {
                    if (m_stackedWidget->indexOf(it->widget) == index) {
                        PageId newPage = it.key();
                        if (newPage != m_currentPage) {
                            PageId oldPage = m_currentPage;
                            m_currentPage = newPage;
                            emit pageChanged(oldPage, newPage);
                            updateNavigationState();
                        }
                        break;
                    }
                }
            });

    qDebug() << "NavigationManager initialized with touch optimization enabled";
}

NavigationManager::~NavigationManager()
{
    qDebug() << "NavigationManager destroyed";
}

void NavigationManager::registerPage(PageId pageId, QWidget *page, const QString &title, const QString &icon)
{
    Q_ASSERT(page);
    
    PageInfo info;
    info.widget = page;
    info.title = title;
    info.icon = icon;
    info.visible = true;
    info.enabled = true;
    info.guard = nullptr;
    
    m_pages[pageId] = info;
    
    // Add to stacked widget if not already added
    if (m_stackedWidget->indexOf(page) == -1) {
        m_stackedWidget->addWidget(page);
    }
    
    qDebug() << "Registered page:" << title << "with ID:" << static_cast<int>(pageId);
}

void NavigationManager::navigateToPage(PageId pageId, const QVariantMap &parameters, TransitionType transition)
{
    if (m_navigationInProgress) {
        qWarning() << "Navigation already in progress, ignoring request";
        return;
    }
    
    if (!m_pages.contains(pageId)) {
        qWarning() << "Page not registered:" << static_cast<int>(pageId);
        emit navigationError(QString("Page not found: %1").arg(static_cast<int>(pageId)));
        return;
    }
    
    NavigationContext context;
    context.fromPage = m_currentPage;
    context.toPage = pageId;
    context.parameters = parameters;
    context.transition = transition;
    context.requiresConfirmation = m_confirmationMessages.contains({context.fromPage, context.toPage});
    context.confirmationMessage = m_confirmationMessages.value({context.fromPage, context.toPage});
    
    if (!validateNavigation(context)) {
        return;
    }
    
    executeNavigation(context);
}

void NavigationManager::goBack()
{
    qDebug() << "NavigationManager::goBack() called";
    qDebug() << "Back stack size:" << m_backStack.size();
    qDebug() << "Can go back:" << canGoBack();
    
    if (!canGoBack()) {
        qDebug() << "Cannot go back - empty back stack";
        return;
    }
    
    PageId previousPage = m_backStack.pop();
    m_forwardStack.push(m_currentPage);
    
    qDebug() << "Going back to page:" << static_cast<int>(previousPage);
    navigateToPage(previousPage, QVariantMap(), TransitionType::SlideRight);
}

void NavigationManager::goForward()
{
    if (!canGoForward()) {
        qDebug() << "Cannot go forward - empty forward stack";
        return;
    }
    
    PageId nextPage = m_forwardStack.pop();
    navigateToPage(nextPage, QVariantMap(), TransitionType::SlideLeft);
}

void NavigationManager::goHome()
{
    navigateToPage(PageId::Overview, QVariantMap(), TransitionType::Fade);
}

void NavigationManager::navigateToHistoryIndex(int index)
{
    QStringList breadcrumbs = breadcrumbPath();
    if (index < 0 || index >= breadcrumbs.size()) {
        qDebug() << "Invalid breadcrumb index:" << index;
        return;
    }
    
    // Calculate how many steps back we need to go
    int currentIndex = breadcrumbs.size() - 1;
    int stepsBack = currentIndex - index;
    
    qDebug() << "Navigating to breadcrumb index" << index << "- going back" << stepsBack << "steps";
    
    // Go back the required number of steps
    for (int i = 0; i < stepsBack && canGoBack(); ++i) {
        goBack();
    }
}

QStringList NavigationManager::breadcrumbPath() const
{
    QStringList path;
    
    // Build breadcrumb path from back stack
    for (int i = 0; i < m_backStack.size(); ++i) {
        PageId pageId = m_backStack.at(i);
        if (m_pages.contains(pageId)) {
            path.append(m_pages[pageId].title);
        }
    }
    
    // Add current page
    if (m_pages.contains(m_currentPage)) {
        path.append(m_pages[m_currentPage].title);
    }
    
    return path;
}

QString NavigationManager::currentPageTitle() const
{
    if (m_pages.contains(m_currentPage)) {
        return m_pages[m_currentPage].title;
    }
    return QString();
}

void NavigationManager::setPageVisible(PageId pageId, bool visible)
{
    if (m_pages.contains(pageId)) {
        m_pages[pageId].visible = visible;
        updateNavigationState();
    }
}

void NavigationManager::setPageEnabled(PageId pageId, bool enabled)
{
    if (m_pages.contains(pageId)) {
        m_pages[pageId].enabled = enabled;
        updateNavigationState();
    }
}

void NavigationManager::refreshCurrentPage()
{
    if (m_pages.contains(m_currentPage)) {
        QWidget *currentWidget = m_pages[m_currentPage].widget;
        if (currentWidget && currentWidget->metaObject()->indexOfMethod("refresh()") != -1) {
            QMetaObject::invokeMethod(currentWidget, "refresh");
        }
    }
}

void NavigationManager::setNavigationGuard(PageId pageId, std::function<bool(const NavigationContext&)> guard)
{
    if (m_pages.contains(pageId)) {
        m_pages[pageId].guard = guard;
    }
}

void NavigationManager::setConfirmationRequired(PageId fromPage, PageId toPage, const QString &message)
{
    m_confirmationMessages[{fromPage, toPage}] = message;
}

void NavigationManager::setBreadcrumbsVisible(bool visible)
{
    if (m_breadcrumbsVisible != visible) {
        m_breadcrumbsVisible = visible;
        updateBreadcrumbs();
    }
}

void NavigationManager::handlePageRequest(PageId pageId, const QVariantMap &parameters)
{
    navigateToPage(pageId, parameters);
}

void NavigationManager::handleBackRequest()
{
    goBack();
}

void NavigationManager::handleHomeRequest()
{
    goHome();
}

bool NavigationManager::validateNavigation(const NavigationContext &context)
{
    // Check if target page exists and is enabled
    const PageInfo &targetPage = m_pages[context.toPage];
    if (!targetPage.visible || !targetPage.enabled) {
        qWarning() << "Target page is not accessible:" << static_cast<int>(context.toPage);
        emit navigationError("Page is not accessible");
        return false;
    }
    
    // Check navigation guard
    if (targetPage.guard && !targetPage.guard(context)) {
        qDebug() << "Navigation guard rejected navigation to:" << static_cast<int>(context.toPage);
        return false;
    }
    
    return true;
}

void NavigationManager::executeNavigation(const NavigationContext &context)
{
    if (context.requiresConfirmation) {
        m_pendingNavigation = context;
        emit confirmationRequired(context.confirmationMessage, [this](bool confirmed) {
            onConfirmationResult(confirmed);
        });
        return;
    }
    
    m_navigationInProgress = true;
    
    // Update navigation history
    if (context.fromPage != context.toPage) {
        m_backStack.push(context.fromPage);
        m_forwardStack.clear(); // Clear forward stack on new navigation
    }
    
    // Emit page lifecycle events
    emit pageAboutToHide(context.fromPage);
    emit pageAboutToShow(context.toPage, context.parameters);
    
    // Perform transition
    performTransition(context.fromPage, context.toPage, context.transition);
    
    // Update current page
    PageId oldPage = m_currentPage;
    m_currentPage = context.toPage;
    
    // Update stacked widget
    if (m_pages.contains(context.toPage)) {
        QWidget *targetWidget = m_pages[context.toPage].widget;
        m_stackedWidget->setCurrentWidget(targetWidget);
        
        // Pass parameters to target page if it supports them
        if (targetWidget->metaObject()->indexOfMethod("setParameters(QVariantMap)") != -1) {
            QMetaObject::invokeMethod(targetWidget, "setParameters", Q_ARG(QVariantMap, context.parameters));
        }
    }
    
    // Emit completion events
    emit pageHidden(context.fromPage);
    emit pageShown(context.toPage);
    emit pageChanged(oldPage, context.toPage);
    
    updateNavigationState();
    updateBreadcrumbs();
    
    m_navigationInProgress = false;
    
    qDebug() << "Navigation completed:" << static_cast<int>(context.fromPage) 
             << "->" << static_cast<int>(context.toPage);
}

void NavigationManager::performTransition(PageId fromPage, PageId toPage, TransitionType transition)
{
    if (!m_animationsEnabled || transition == TransitionType::None) {
        return;
    }
    
    // TODO: Implement smooth transitions with QPropertyAnimation
    // For now, just use the default QStackedWidget transition
}

void NavigationManager::updateNavigationState()
{
    emit navigationStateChanged();
}

void NavigationManager::updateBreadcrumbs()
{
    if (m_breadcrumbsVisible) {
        emit breadcrumbsChanged(breadcrumbPath());
    }
}

void NavigationManager::onConfirmationResult(bool confirmed)
{
    if (confirmed) {
        executeNavigation(m_pendingNavigation);
    } else {
        qDebug() << "Navigation cancelled by user";
    }
}

void NavigationManager::onTransitionFinished()
{
    // Handle transition completion
    m_navigationInProgress = false;
}

// NavigationCommand Implementation
NavigationCommand::NavigationCommand(NavigationManager *manager, 
                                   NavigationManager::PageId pageId,
                                   const QVariantMap &parameters,
                                   QObject *parent)
    : QObject(parent)
    , m_manager(manager)
    , m_targetPage(pageId)
    , m_previousPage(manager->currentPage())
    , m_parameters(parameters)
    , m_executed(false)
{
}

void NavigationCommand::execute()
{
    if (!canExecute()) {
        emit failed("Cannot execute navigation command");
        return;
    }
    
    m_previousPage = m_manager->currentPage();
    m_manager->navigateToPage(m_targetPage, m_parameters);
    m_executed = true;
    emit executed();
}

void NavigationCommand::undo()
{
    if (!m_executed) {
        emit failed("Command not executed, cannot undo");
        return;
    }
    
    m_manager->navigateToPage(m_previousPage);
    m_executed = false;
    emit undone();
}

bool NavigationCommand::canExecute() const
{
    return m_manager != nullptr && !m_executed;
}