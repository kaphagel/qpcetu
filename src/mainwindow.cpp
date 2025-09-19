#include <QCloseEvent>
#include "mainwindow.h"
#include <QCloseEvent>
MainWindow::~MainWindow() {}

void MainWindow::closeEvent(QCloseEvent *event) {
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_centralWidget(nullptr)
    , m_mainLayout(nullptr)
    , m_statusLabel(nullptr)
    , m_timeLabel(nullptr)
    , m_connectionStatus(nullptr)
    // ...existing code...
    , m_udpService(nullptr)
    , m_udpResponsePage(nullptr) // Will be constructed in setupUI
{
    qDebug() << "MainWindow constructor start";
    setWindowTitle("QUANTUM TACTICAL PROCESSING CENTER - ETU");
    setMinimumSize(1200, 800);   // Reduced minimum size
    resize(1400, 1000);          // Reduced initial size
    
    dashboardPage = new DashboardPage(this);
    graphsPage = new GraphsPage(this);
    settingsPage = new SettingsPage(this);
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
    m_stackedWidget->addWidget(dashboardPage);
    m_stackedWidget->addWidget(graphsPage);
    m_stackedWidget->addWidget(settingsPage);
    m_stackedWidget->addWidget(m_udpResponsePage);
    m_stackedWidget->setCurrentIndex(0);

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
        "QPushButton#controlButton { background-color: #0044aa; color: #ffffff; border: 2px solid #0066cc; border-radius: 6px; padding: 8px; font-weight: bold; font-size: 12px; } "
        "QPushButton#controlButton:hover { background-color: #0066cc; border-color: #0088ff; } "
        "QPushButton#controlButton:pressed { background-color: #002266; } "
        "QPushButton#alertButton { background-color: #aa4400; color: #ffffff; border: 2px solid #cc6600; border-radius: 6px; padding: 8px; font-weight: bold; font-size: 12px; } "
        "QPushButton#alertButton:hover { background-color: #cc6600; border-color: #ff8800; } "
        "QTextEdit#logDisplay { background-color: #000011; color: #00ff88; border: 1px solid #004422; border-radius: 4px; font-family: 'Courier New', monospace; font-size: 10px; } "
        "QScrollBar:vertical { background-color: #001122; width: 12px; border-radius: 6px; } "
        "QScrollBar::handle:vertical { background-color: #0066cc; border-radius: 6px; min-height: 20px; } "
        "QScrollBar::handle:vertical:hover { background-color: #0088ff; } ";
    setStyleSheet(styleSheet);
}

void MainWindow::setupPages() {
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

void MainWindow::setupBreadcrumbs(const QStringList &crumbs, int activeIndex) {
    // Clear previous breadcrumbs
    QLayoutItem *child;
    while ((child = m_breadcrumbLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
    for (int i = 0; i < crumbs.size(); ++i) {
        QPushButton *btn = new QPushButton(crumbs[i]);
        btn->setFlat(true);
        btn->setStyleSheet(i == activeIndex ? "font-weight: bold; color: #00aaff;" : "color: #cccccc;");
        m_breadcrumbLayout->addWidget(btn);
        connect(btn, &QPushButton::clicked, this, [this, i]() { navigateToPage(i); });
        if (i < crumbs.size() - 1) {
            QLabel *sep = new QLabel("/");
            sep->setStyleSheet("color: #888888; font-weight: bold;");
            m_breadcrumbLayout->addWidget(sep);
        }
    }
    m_breadcrumbLayout->addStretch();
}

void MainWindow::navigateToPage(int index) {
    m_stackedWidget->setCurrentIndex(index);
}

void MainWindow::updateData()
{
    if (dashboardPage) dashboardPage->updateData();
}

void MainWindow::updateSystemStatus()
{
    if (dashboardPage) dashboardPage->updateSystemStatus();
}

void MainWindow::simulateAlert()
{
    if (dashboardPage) dashboardPage->simulateAlert();
}
