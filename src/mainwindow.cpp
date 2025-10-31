#include <QCloseEvent>
#include "mainwindow.h"
#include <QCloseEvent>
MainWindow::~MainWindow() {}

void MainWindow::closeEvent(QCloseEvent *event)
{
    QMainWindow::closeEvent(event);
}
#include "datawidget.h"
#include "animatedprogressbar.h"
#include "graphwidget.h"
#include <QDateTime>
#include <QScrollBar>
#include <QApplication>
#include <QDebug>
#include "udpservice.h"
#include "pages/dashboardpage.h"
#include "pages/graphspage.h"
#include "pages/settingspage.h"
#include "pages/udpresponsepage.h"
#include "pages/overviewpage.h" // Added include for OverviewPage
#include "pages/dragdroppage_simple.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      // ...existing code...
      ,
      m_udpService(nullptr), m_udpResponsePage(nullptr) // Will be constructed in setupUI
{
    qDebug() << "MainWindow constructor start";
    setWindowTitle("QUANTUM TACTICAL PROCESSING CENTER - ETU");
    setMinimumSize(1200, 800); // Reduced minimum size
    resize(1400, 1000);        // Reduced initial size

    overviewPage = new OverviewPage(this);
    dashboardPage = new DashboardPage(this);
    graphsPage = new GraphsPage(this);
    settingsPage = new SettingsPage(this);
    dragDropPage = new SimpleDragDropPage(this);
    m_udpResponsePage = new UdpResponsePage(this);
    setupUI();
    // Restore UDP service and broadcast
    m_udpService = new UdpService(this);
    connect(m_udpService, &UdpService::moduleDiscovered,
            m_udpResponsePage, &UdpResponsePage::addResponse);
    m_udpService->startBroadcast();
    qDebug() << "UDP service started broadcast";

    // ...existing code...
    // ...existing code...
}

void MainWindow::setupUI()
{
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);

    QVBoxLayout *mainVLayout = new QVBoxLayout(m_centralWidget);
    mainVLayout->setSpacing(0);
    mainVLayout->setContentsMargins(0, 0, 0, 0);

    // Navigation bar (breadcrumbs)
    m_breadcrumbBar = new QWidget(m_centralWidget);
    m_breadcrumbLayout = new QHBoxLayout(m_breadcrumbBar);
    m_breadcrumbLayout->setContentsMargins(10, 10, 10, 10);
    m_breadcrumbLayout->setSpacing(8);
    mainVLayout->addWidget(m_breadcrumbBar);

    // Stacked widget for pages
    m_stackedWidget = new QStackedWidget(m_centralWidget);
    mainVLayout->addWidget(m_stackedWidget, 1);

    // Add all pages to stacked widget
    m_stackedWidget->addWidget(overviewPage);      // index 0
    m_stackedWidget->addWidget(dashboardPage);     // index 1
    m_stackedWidget->addWidget(graphsPage);        // index 2
    m_stackedWidget->addWidget(settingsPage);      // index 3
    m_stackedWidget->addWidget(m_udpResponsePage); // index 4
    m_stackedWidget->addWidget(dragDropPage);      // index 5
    m_stackedWidget->setCurrentIndex(0);

    // Connect overview icons to navigation
    connect(overviewPage, &OverviewPage::iconClicked, this, [this](int pageIndex)
            {
        // pageIndex: 0=Dashboard, 1=Graphs, 2=Settings, 3=UDP, 4=DragDrop
        navigateToPage(pageIndex + 1); });

    // Connect drag drop page back button
    connect(dragDropPage, &SimpleDragDropPage::backRequested, this, [this]()
            {
                navigateToPage(0); // Go back to overview
            });

    setupBreadcrumbs({"Dashboard", "Graphs", "Settings", "UDP Response"}, 0);
}

void MainWindow::setupStyling()
{
    QString styleSheet = "QMainWindow { background-color: #0a0a1a; color: #00aaff; } "
                         "QFrame#statusFrame { background-color: #001133; border: 2px solid #0066cc; border-radius: 8px; padding: 10px; } "
                         "QFrame#controlFrame { color: #00aaff; } "
                         "QLabel#connectionStatus { font-size: 12px; color: #ffaa00; } "
                         "QGroupBox#systemGroup { font-size: 14px; font-weight: bold; color: #00aaff; border: 2px solid #0066cc; border-radius: 8px; margin-top: 10px; background-color: #001133; } "
                         "QGroupBox#systemGroup::title { subcontrol-origin: margin; left: 10px; padding: 0 8px 0 8px; color: #00aaff; } "
                         "QLabel#parameterLabel { font-size: 11px; color: #88aaff; font-weight: bold; margin-top: 5px; } "
                         "QLabel#navLabel { font-size: 11px; color: #00aaff; font-family: 'Courier New', monospace; background-color: #000822; border: 1px solid #0044aa; border-radius: 3px; padding: 4px; margin: 2px; } "
                         "QPushButton {"
                         "  background-color: #23272b;"
                         "  color: #e0e0e0;"
                         "  border: 1px solid #444;"
                         "  border-radius: 2px;"
                         "  font-family: 'Segoe UI', 'Arial', sans-serif;"
                         "  font-size: 14px;"
                         "  font-weight: 500;"
                         "  padding: 6px 18px;"
                         "  outline: none;"
                         "}"
                         "QPushButton:hover {"
                         "  background-color: #2c3136;"
                         "  border: 1px solid #666;"
                         "}"
                         "QPushButton:pressed {"
                         "  background-color: #1a1d20;"
                         "  border: 1px solid #888;"
                         "}"
                         "QPushButton:disabled {"
                         "  background-color: #181a1b;"
                         "  color: #888;"
                         "  border: 1px solid #222;"
                         "}"
                         "QTextEdit#logDisplay { background-color: #000011; color: #00ff88; border: 1px solid #004422; border-radius: 4px; font-family: 'Courier New', monospace; font-size: 10px; } "
                         "QScrollBar:vertical { background-color: #001122; width: 12px; border-radius: 6px; } "
                         "QScrollBar::handle:vertical { background-color: #0066cc; border-radius: 6px; min-height: 20px; } "
                         "QScrollBar::handle:vertical:hover { background-color: #0088ff; } ";
    setStyleSheet(styleSheet);
}

void MainWindow::setupPages()
{
    qDebug() << "Adding dashboardPage, ptr:" << dashboardPage << " stackedWidget:" << m_stackedWidget;
    m_stackedWidget->addWidget(dashboardPage);
    qDebug() << "Adding graphsPage, ptr:" << graphsPage << " stackedWidget:" << m_stackedWidget;
    m_stackedWidget->addWidget(graphsPage);
    qDebug() << "Adding settingsPage, ptr:" << settingsPage << " stackedWidget:" << m_stackedWidget;
    m_stackedWidget->addWidget(settingsPage);
    qDebug() << "Adding udpResponsePage, ptr:" << m_udpResponsePage << " stackedWidget:" << m_stackedWidget;
    m_stackedWidget->addWidget(m_udpResponsePage);
    qDebug() << "All pages added";
}

void MainWindow::setupBreadcrumbs(const QStringList &crumbs, int activeIndex)
{
}

void MainWindow::navigateToPage(int index)
{
    m_stackedWidget->setCurrentIndex(index);
}

void MainWindow::updateData()
{
    // No longer needed - DashboardPage ViewModel handles updates automatically
}

void MainWindow::updateSystemStatus()
{
    // No longer needed - DashboardPage ViewModel handles updates automatically
}

void MainWindow::simulateAlert()
{
    // No longer needed - DashboardPage ViewModel handles alerts automatically
}
