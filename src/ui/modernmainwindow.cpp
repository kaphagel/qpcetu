#include "modernmainwindow.h"
#include "controllercardwidget.h"
#include "thememanager.h"
#include "applestyle.h"
#include "../pages/dashboardpage.h"
#include "../pages/graphspage.h"
#include "../pages/settingspage.h"
#include "../pages/udpresponsepage.h"
#include "../pages/industrialdatapage.h"
#include "../navigation/navigationmanager.h"
#include "../navigation/breadcrumbwidget.h"

#include <QApplication>
#include <QDateTime>
#include <QDebug>
#include <QCloseEvent>
#include <QResizeEvent>
#include <QRandomGenerator>
#include <QStyle>

ModernMainWindow::ModernMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_udpService(nullptr)
    , m_navigationManager(nullptr)
    , m_breadcrumbWidget(nullptr)
    , m_dashboardPage(nullptr)
    , m_graphsPage(nullptr)
    , m_settingsPage(nullptr)
    , m_udpResponsePage(nullptr)
    , m_industrialDataPage(nullptr)
    , m_hamburgerButton(nullptr)
    , m_backButton(nullptr)
    , m_homeButton(nullptr)
    , m_hamburgerMenu(nullptr)
    , m_discoveredControllers(0)
{
    qDebug() << "ModernMainWindow constructor start";

    setWindowTitle("🛸 QUANTUM TACTICAL PROCESSING CENTER - ETU");
    setMinimumSize(1200, 800);
    resize(1600, 1000);

    setupUI();
    setupNavigation();
    setupStyling();

    // Connect to theme system
    connect(ThemeManager::instance(), &ThemeManager::themeChanged,
            this, &ModernMainWindow::onThemeChanged);

    // Initialize UDP service for controller discovery
    m_udpService = new UdpService(this);
    connect(m_udpService, &UdpService::moduleDiscovered,
            this, &ModernMainWindow::onControllerDiscovered);
    connect(m_udpService, &UdpService::controllersChanged,
            this, [this]()
            { onControllerCountChanged(m_udpService->discoveredControllers()); });

    // Connect UDP service to UdpResponsePage for displaying responses
    if (m_udpService && m_udpResponsePage) {
        connect(m_udpService, &UdpService::moduleDiscovered,
                m_udpResponsePage, &UdpResponsePage::addResponse);
        qDebug() << "✅ Connected UDP service to UdpResponsePage for response display";
    } else {
        qDebug() << "❌ Failed to connect UDP service to UdpResponsePage:" 
                 << "UDP service:" << (m_udpService ? "OK" : "NULL")
                 << "UDP Response Page:" << (m_udpResponsePage ? "OK" : "NULL");
    }

    // Start discovery
    m_udpService->startBroadcast();
    qDebug() << "UDP service started for controller discovery";

    // Setup timers
    m_statusTimer = new QTimer(this);
    connect(m_statusTimer, &QTimer::timeout, this, &ModernMainWindow::updateSystemStatus);
    m_statusTimer->start(5000); // Update every 5 seconds

    m_dateTimeTimer = new QTimer(this);
    connect(m_dateTimeTimer, &QTimer::timeout, this, &ModernMainWindow::updateDateTime);
    m_dateTimeTimer->start(1000); // Update every second

    // Initial updates
    updateDateTime();
    updateSystemStatus();

    qDebug() << "ModernMainWindow initialization complete";
}

ModernMainWindow::~ModernMainWindow()
{
    if (m_udpService)
    {
        m_udpService->stopBroadcast();
    }
}

void ModernMainWindow::setupUI()
{
    m_centralWidget = new QWidget(this);
    setCentralWidget(m_centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout(m_centralWidget);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // Create main UI components
    createHeaderBar();
    createSystemStatusStrip();
    createMainContentArea();
    createStatusBar();

    // Add to main layout
    mainLayout->addWidget(m_headerBar);
    mainLayout->addWidget(m_statusStrip);
    
    // Create stacked widget here instead of in setupNavigation
    m_stackedWidget = new QStackedWidget(this);
    mainLayout->addWidget(m_stackedWidget, 1);
    mainLayout->addWidget(m_bottomStatusBar);
}

void ModernMainWindow::createHeaderBar()
{
    m_headerBar = new QWidget();
    m_headerBar->setFixedHeight(80); // Increased from 60px for touch
    m_headerBar->setObjectName("headerBar");

    QHBoxLayout *headerLayout = new QHBoxLayout(m_headerBar);
    headerLayout->setContentsMargins(24, 16, 24, 16); // Increased margins
    headerLayout->setSpacing(32);                     // Increased spacing for touch

    // Hamburger menu button
    m_hamburgerButton = new QPushButton("☰");
    m_hamburgerButton->setObjectName("hamburgerButton");
    m_hamburgerButton->setMinimumSize(60, 60); // Touch-friendly size
    m_hamburgerButton->setMaximumSize(60, 60);
    m_hamburgerButton->setToolTip("Open Navigation Menu");
    m_hamburgerButton->setStyleSheet(
        "QPushButton {"
        "    background: transparent;"
        "    border: none;"
        "    font-size: 24px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background: rgba(255, 255, 255, 0.1);"
        "}"
        "QPushButton:pressed {"
        "    background: rgba(255, 255, 255, 0.2);"
        "}"
    );
    connect(m_hamburgerButton, &QPushButton::clicked, this, [this]() {
        if (m_hamburgerMenu) {
            m_hamburgerMenu->toggleMenu();
        }
    });

    // Back button
    m_backButton = new QPushButton("←");
    m_backButton->setObjectName("backButton");
    m_backButton->setMinimumSize(50, 60); // Slightly smaller than hamburger
    m_backButton->setMaximumSize(50, 60);
    m_backButton->setToolTip("Go Back");
    m_backButton->setStyleSheet(
        "QPushButton {"
        "    background: transparent;"
        "    border: none;"
        "    font-size: 20px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background: rgba(255, 255, 255, 0.1);"
        "}"
        "QPushButton:pressed {"
        "    background: rgba(255, 255, 255, 0.2);"
        "}"
        "QPushButton:disabled {"
        "    color: rgba(255, 255, 255, 0.3);"
        "}"
    );
    connect(m_backButton, &QPushButton::clicked, this, [this]() {
        qDebug() << "Header back button clicked!";
        if (m_navigationManager) {
            m_navigationManager->goBack();
        }
    });

    // Home button
    m_homeButton = new QPushButton("🏠");
    m_homeButton->setObjectName("homeButton");
    m_homeButton->setMinimumSize(50, 60); // Slightly smaller than hamburger
    m_homeButton->setMaximumSize(50, 60);
    m_homeButton->setToolTip("Go Home");
    m_homeButton->setStyleSheet(
        "QPushButton {"
        "    background: transparent;"
        "    border: none;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    background: rgba(255, 255, 255, 0.1);"
        "}"
        "QPushButton:pressed {"
        "    background: rgba(255, 255, 255, 0.2);"
        "}"
    );
    connect(m_homeButton, &QPushButton::clicked, this, [this]() {
        qDebug() << "Header home button clicked!";
        if (m_navigationManager) {
            m_navigationManager->goHome();
        }
    });

    // Title with icon
    m_titleLabel = new QLabel("🛸 SciFi Data Screen");
    m_titleLabel->setObjectName("titleLabel");

    // Connection status
    m_connectionStatusLabel = new QLabel("🟢 ONLINE");
    m_connectionStatusLabel->setObjectName("connectionStatus");

    // User info
    m_userLabel = new QLabel("👤 Operator");
    m_userLabel->setObjectName("userLabel");

    // Date/time
    m_dateTimeLabel = new QLabel();
    m_dateTimeLabel->setObjectName("dateTimeLabel");

    // Create theme toggle button
    QPushButton *themeToggleBtn = new QPushButton("🎨");
    themeToggleBtn->setObjectName("themeToggleBtn");
    themeToggleBtn->setMinimumSize(60, 60); // Touch-friendly size
    themeToggleBtn->setMaximumSize(60, 60);
    themeToggleBtn->setToolTip("Tap to switch theme (Dark/Light/High Contrast/Apple Light/Apple Dark)");
    connect(themeToggleBtn, &QPushButton::clicked, this, &ModernMainWindow::toggleTheme);

    // Layout: Hamburger + Back + Home + Title on left, then status info on right
    headerLayout->addWidget(m_hamburgerButton);
    headerLayout->addWidget(m_backButton);
    headerLayout->addWidget(m_homeButton);
    headerLayout->addWidget(m_titleLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(themeToggleBtn);
    headerLayout->addWidget(m_connectionStatusLabel);
    headerLayout->addWidget(m_userLabel);
    headerLayout->addWidget(m_dateTimeLabel);
    
    // Create hamburger menu
    m_hamburgerMenu = new HamburgerMenu(this);
    m_hamburgerMenu->setTouchOptimized(true);
}

void ModernMainWindow::createSystemStatusStrip()
{
    m_statusStrip = new QWidget();
    m_statusStrip->setFixedHeight(56); // Increased from 40px for touch
    m_statusStrip->setObjectName("statusStrip");

    QHBoxLayout *statusLayout = new QHBoxLayout(m_statusStrip);
    statusLayout->setContentsMargins(24, 12, 24, 12); // Increased margins
    statusLayout->setSpacing(40);                     // Increased spacing for touch

    m_discoveryStatus = new QLabel("📡 Discovery: Active");
    m_discoveryStatus->setObjectName("statusLabel");

    m_modbusStatus = new QLabel("🔗 Modbus: Ready");
    m_modbusStatus->setObjectName("statusLabel");

    m_eventsStatus = new QLabel("⚡ Events: 0 New");
    m_eventsStatus->setObjectName("statusLabel");

    m_dataStatus = new QLabel("📊 Data: Live");
    m_dataStatus->setObjectName("statusLabel");

    statusLayout->addWidget(m_discoveryStatus);
    statusLayout->addWidget(m_modbusStatus);
    statusLayout->addWidget(m_eventsStatus);
    statusLayout->addWidget(m_dataStatus);
    statusLayout->addStretch();
}

void ModernMainWindow::createMainContentArea()
{
    m_mainContent = new QWidget();
    QHBoxLayout *contentLayout = new QHBoxLayout(m_mainContent);
    contentLayout->setContentsMargins(24, 24, 24, 24); // Increased margins for touch
    contentLayout->setSpacing(32);                     // Increased spacing for touch

    // Create controller grid section (60% of width)
    createControllerGrid();

    // Create quick actions panel (40% of width)
    createQuickActionsPanel();

    contentLayout->addWidget(m_controllerScrollArea, 6);
    contentLayout->addWidget(m_quickActionsPanel, 4);
}

void ModernMainWindow::createControllerGrid()
{
    // Controller section with title
    QWidget *controllerSection = new QWidget();
    QVBoxLayout *sectionLayout = new QVBoxLayout(controllerSection);
    sectionLayout->setContentsMargins(0, 0, 0, 0);
    sectionLayout->setSpacing(20); // Increased spacing for touch

    // Section header
    QWidget *headerWidget = new QWidget();
    QHBoxLayout *headerLayout = new QHBoxLayout(headerWidget);
    headerLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *titleLabel = new QLabel("🎛️ ACTIVE CONTROLLERS");
    titleLabel->setObjectName("sectionTitle");

    QPushButton *refreshButton = new QPushButton("🔄 Refresh");
    refreshButton->setObjectName("actionButton");
    refreshButton->setMinimumSize(120, 60); // Touch-optimized size
    connect(refreshButton, &QPushButton::clicked, this, &ModernMainWindow::refreshControllers);

    headerLayout->addWidget(titleLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(refreshButton);

    // Scroll area for controller grid
    m_controllerScrollArea = new QScrollArea();
    m_controllerScrollArea->setWidgetResizable(true);
    m_controllerScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_controllerScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_controllerScrollArea->setObjectName("controllerScrollArea");

    // Grid widget to hold controller cards
    m_controllerGridWidget = new QWidget();
    m_controllerGridLayout = new QGridLayout(m_controllerGridWidget);
    m_controllerGridLayout->setSpacing(20);                     // Increased spacing for touch
    m_controllerGridLayout->setContentsMargins(16, 16, 16, 16); // Increased margins

    // Add initial "Add Controller" card - made larger for touch
    QPushButton *addControllerCard = new QPushButton("➕ ADD\nCONTROLLER\n\nAuto-Discover\nor Manual");
    addControllerCard->setFixedSize(320, 220); // Larger touch target
    addControllerCard->setObjectName("addControllerCard");
    connect(addControllerCard, &QPushButton::clicked, this, &ModernMainWindow::refreshControllers);

    m_controllerGridLayout->addWidget(addControllerCard, 0, 0);

    m_controllerScrollArea->setWidget(m_controllerGridWidget);

    sectionLayout->addWidget(headerWidget);
    sectionLayout->addWidget(m_controllerScrollArea);

    // Replace the scroll area in the content layout
    m_controllerScrollArea = new QScrollArea();
    m_controllerScrollArea->setWidget(controllerSection);
    m_controllerScrollArea->setWidgetResizable(true);
    m_controllerScrollArea->setObjectName("controllerScrollArea");
}

void ModernMainWindow::createQuickActionsPanel()
{
    m_quickActionsPanel = new QWidget();
    m_quickActionsPanel->setObjectName("quickActionsPanel");

    QVBoxLayout *panelLayout = new QVBoxLayout(m_quickActionsPanel);
    panelLayout->setContentsMargins(24, 0, 0, 0); // Increased margins
    panelLayout->setSpacing(24);                  // Increased spacing for touch

    // Alerts section
    QGroupBox *alertsGroup = new QGroupBox("🚨 ACTIVE ALERTS");
    alertsGroup->setObjectName("alertsGroup");

    QVBoxLayout *alertsLayout = new QVBoxLayout(alertsGroup);
    alertsLayout->setSpacing(16); // Increased spacing

    // Sample alert items - larger for touch
    QLabel *alert1 = new QLabel("⚠️  Controller Discovery\n     New device found | 14:31\n     [VIEW] [CONFIGURE]");
    alert1->setObjectName("alertItem");
    alert1->setMinimumHeight(80); // Touch-friendly height

    QLabel *alert2 = new QLabel("ℹ️  System Status\n     All systems nominal | 14:28\n     [DETAILS] [ACKNOWLEDGE]");
    alert2->setObjectName("alertItem");
    alert2->setMinimumHeight(80); // Touch-friendly height

    alertsLayout->addWidget(alert1);
    alertsLayout->addWidget(alert2);
    alertsLayout->addStretch();

    // Quick actions section
    QGroupBox *actionsGroup = new QGroupBox("🔧 QUICK ACTIONS");
    actionsGroup->setObjectName("actionsGroup");

    QVBoxLayout *actionsLayout = new QVBoxLayout(actionsGroup);
    actionsLayout->setSpacing(12); // Increased spacing between buttons

    QPushButton *controllersBtn = new QPushButton("🎛️  Controller Management");
    QPushButton *dashboardBtn = new QPushButton("📊  Data Visualization");
    QPushButton *settingsBtn = new QPushButton("⚙️  System Settings");
    QPushButton *networkBtn = new QPushButton("📡  Network Discovery");
    QPushButton *diagnosticsBtn = new QPushButton("🛠️  Diagnostic Tools");

    // Style all action buttons - touch optimized
    QList<QPushButton *> actionButtons = {controllersBtn, dashboardBtn, settingsBtn, networkBtn, diagnosticsBtn};
    for (QPushButton *btn : actionButtons)
    {
        btn->setObjectName("quickActionButton");
        btn->setFixedHeight(60);   // Touch-optimized height (was 35px)
        btn->setMinimumWidth(200); // Ensure good touch width
        actionsLayout->addWidget(btn);
    }

    // Connect action buttons
    connect(dashboardBtn, &QPushButton::clicked, this, [this]() {
        navigateToPage(NavigationManager::PageId::Dashboard);
    });
    connect(settingsBtn, &QPushButton::clicked, this, [this]() {
        navigateToPage(NavigationManager::PageId::Settings);
    });
    connect(networkBtn, &QPushButton::clicked, this, &ModernMainWindow::refreshControllers);

    actionsLayout->addStretch();

    panelLayout->addWidget(alertsGroup);
    panelLayout->addWidget(actionsGroup);
    panelLayout->addStretch();
}

void ModernMainWindow::createStatusBar()
{
    m_bottomStatusBar = new QWidget();
    m_bottomStatusBar->setFixedHeight(48); // Increased from 32px for touch
    m_bottomStatusBar->setObjectName("bottomStatusBar");

    QHBoxLayout *statusLayout = new QHBoxLayout(m_bottomStatusBar);
    statusLayout->setContentsMargins(24, 8, 24, 8); // Increased margins
    statusLayout->setSpacing(32);                   // Increased spacing for touch

    m_cpuLabel = new QLabel("📊 CPU: --%");
    m_memoryLabel = new QLabel("💾 RAM: -- MB");
    m_networkLabel = new QLabel("🌐 Network: -- KB/s");
    m_lastUpdateLabel = new QLabel("🔄 Last Update: --");

    QList<QLabel *> statusLabels = {m_cpuLabel, m_memoryLabel, m_networkLabel, m_lastUpdateLabel};
    for (QLabel *label : statusLabels)
    {
        label->setObjectName("statusBarLabel");
        statusLayout->addWidget(label);
    }

    statusLayout->addStretch();
}

void ModernMainWindow::setupStyling()
{
    // Apply initial theme styling
    onThemeChanged();
}

void ModernMainWindow::toggleTheme()
{
    ThemeManager *tm = ThemeManager::instance();
    ThemeManager::Theme currentTheme = tm->currentTheme();

    // Simple toggle between Light and Dark themes
    switch (currentTheme)
    {
    case ThemeManager::Light:
        tm->setTheme(ThemeManager::Dark);
        break;
    case ThemeManager::Dark:
        tm->setTheme(ThemeManager::Light);
        break;
    default:
        tm->setTheme(ThemeManager::Light);
        break;
    }
}

void ModernMainWindow::onThemeChanged()
{
    ThemeManager *tm = ThemeManager::instance();

    // Get current theme colors for clean, borderless design
    QString mainBg = tm->colorString(ThemeManager::MainBackground);
    QString secondaryBg = tm->colorString(ThemeManager::SecondaryBackground);
    QString headerBg = tm->colorString(ThemeManager::HeaderBackground);
    QString cardBg = tm->colorString(ThemeManager::CardBackground);
    QString statusBg = tm->colorString(ThemeManager::StatusStripBackground);

    QString primaryText = tm->colorString(ThemeManager::PrimaryText);
    QString secondaryText = tm->colorString(ThemeManager::SecondaryText);
    QString accentText = tm->colorString(ThemeManager::AccentText);
    QString statusText = tm->colorString(ThemeManager::StatusText);

    QString buttonBg = tm->colorString(ThemeManager::ButtonBackground);
    QString buttonHover = tm->colorString(ThemeManager::ButtonHover);
    QString buttonPressed = tm->colorString(ThemeManager::ButtonPressed);

    // Clean, borderless base styles
    QString baseStyles = QString(
                             "QMainWindow { "
                             "  background-color: %1; "
                             "  color: %2; "
                             "} "
                             "QWidget { "
                             "  background-color: %1; "
                             "  color: %2; "
                             "  border: none; "
                             "} "
                             "QWidget#headerBar { "
                             "  background-color: %1; "
                             "  border: none; "
                             "} "
                             "QWidget#statusStrip { "
                             "  background-color: %4; "
                             "  border: none; "
                             "} "
                             "QWidget#mainContent { "
                             "  background-color: %1; "
                             "  border: none; "
                             "} "
                             "QScrollArea { "
                             "  background-color: %1; "
                             "  border: none; "
                             "} "
                             "QScrollBar:vertical { "
                             "  background-color: %3; "
                             "  border: none; "
                             "  width: 12px; "
                             "} "
                             "QScrollBar::handle:vertical { "
                             "  background-color: %4; "
                             "  border: none; "
                             "  border-radius: 6px; "
                             "} ")
                             .arg(mainBg)         // %1
                             .arg(primaryText)    // %2
                             .arg(statusBg)       // %3 (was headerBg, now statusBg since headerBg uses %1)
                             .arg(secondaryText); // %4 (was %5, now %4)

    // Clean theme-aware component styles (no borders)
    QString customStyles = QString(
                               "QPushButton#themeToggleBtn { "
                               "  background-color: %1; "
                               "  color: %2; "
                               "  border: none; "
                               "  border-radius: 8px; "
                               "  font-size: 20px; "
                               "  font-weight: bold; "
                               "  padding: 8px 16px; "
                               "}"
                               "QPushButton#themeToggleBtn:hover { "
                               "  background-color: %3; "
                               "}"
                               "QPushButton#themeToggleBtn:pressed { "
                               "  background-color: %4; "
                               "}"
                               "QPushButton#addControllerCard { "
                               "  background-color: %5; "
                               "  color: %6; "
                               "  border: none; "
                               "  border-radius: 12px; "
                               "  font-size: 18px; "
                               "  font-weight: bold; "
                               "  padding: 16px; "
                               "}"
                               "QPushButton#addControllerCard:hover { "
                               "  background-color: %3; "
                               "}"
                               "QPushButton#addControllerCard:pressed { "
                               "  background-color: %4; "
                               "}"
                               "QWidget#quickActionsPanel { "
                               "  background-color: %6; "
                               "  border: none; "
                               "  border-radius: 12px; "
                               "  padding: 16px; "
                               "} "
                               "QGroupBox { "
                               "  font-size: 18px; "
                               "  font-weight: bold; "
                               "  color: %2; "
                               "  border: none; "
                               "  border-radius: 12px; "
                               "  padding-top: 16px; "
                               "} "
                               "QLabel#sectionTitle { "
                               "  font-size: 22px; "
                               "  font-weight: 700; "
                               "  color: %2; "
                               "} "
                               "QLabel#alertLabel { "
                               "  font-size: 17px; "
                               "  font-weight: 400; "
                               "  color: %7; "
                               "  padding: 8px; "
                               "} "
                               "QPushButton#quickActionButton { "
                               "  background-color: %5; "
                               "  color: %2; "
                               "  border: none; "
                               "  border-radius: 8px; "
                               "  font-size: 16px; "
                               "  padding: 12px 16px; "
                               "}"
                               "QPushButton#quickActionButton:hover { "
                               "  background-color: %3; "
                               "}"
                               "QPushButton#quickActionButton:pressed { "
                               "  background-color: %4; "
                               "}"
                               "QPushButton#actionButton { "
                               "  background-color: %8; "
                               "  color: %9; "
                               "  border: none; "
                               "  border-radius: 8px; "
                               "  font-size: 16px; "
                               "  font-weight: 600; "
                               "  padding: 12px 24px; "
                               "}"
                               "QPushButton#actionButton:hover { "
                               "  background-color: %10; "
                               "}"
                               "QPushButton#actionButton:pressed { "
                               "  background-color: %11; "
                               "}"
                               "QWidget#bottomStatusBar { "
                               "  background-color: %6; "
                               "  border: none; "
                               "  border-radius: 8px; "
                               "} "
                               "QLabel#statusBarLabel { "
                               "  font-size: 15px; "
                               "  color: %7; "
                               "  font-weight: 400; "
                               "}")
                               .arg(buttonBg)                               // %1 - theme toggle background
                               .arg(primaryText)                            // %2 - primary text
                               .arg(buttonHover)                            // %3 - hover state
                               .arg(buttonPressed)                          // %4 - pressed state
                               .arg(cardBg)                                 // %5 - card background
                               .arg(secondaryBg)                            // %6 - secondary background
                               .arg(secondaryText)                          // %7 - secondary text
                               .arg(tm->colorString(ThemeManager::Primary)) // %8 - primary button bg
                               .arg(primaryText)                            // %9 - primary button text
                               .arg(buttonHover)                            // %10 - primary button hover
                               .arg(buttonPressed);                         // %11 - primary button pressed

    // Apply the complete stylesheet
    setStyleSheet(baseStyles + customStyles);

    // Update any existing controller cards
    for (ControllerCardWidget *card : m_controllerCards)
    {
        // Update controller card styling
        card->style()->unpolish(card);
        card->style()->polish(card);
    }

    // Debug output
    qDebug() << "Clean borderless theme applied:" << tm->themeName();
}

void ModernMainWindow::navigateToPage(int index)
{
    qDebug() << "Legacy navigation to page" << index << "requested";
    // Convert legacy index to PageId
    NavigationManager::PageId pageId = static_cast<NavigationManager::PageId>(index);
    navigateToPage(pageId);
}

void ModernMainWindow::navigateToPage(NavigationManager::PageId pageId, const QVariantMap &parameters)
{
    if (m_navigationManager) {
        m_navigationManager->navigateToPage(pageId, parameters);
    } else {
        qWarning() << "Navigation manager not initialized";
    }
}

void ModernMainWindow::onControllerDiscovered(const QString &ip, const QByteArray &data)
{
    qDebug() << "Controller discovered:" << ip << "Data:" << data;

    // Parse controller type from UDP response
    QString response = QString::fromUtf8(data);
    QString controllerType = "Unknown";

    if (response.contains("FB type = EPIC4", Qt::CaseInsensitive))
    {
        controllerType = "EPIC4";
    }
    else if (response.contains("FB type = EPIC5", Qt::CaseInsensitive))
    {
        controllerType = "EPIC5";
    }
    else if (response.contains("SNAP_PAC", Qt::CaseInsensitive))
    {
        controllerType = "SNAP_PAC";
    }

    // Check if controller already exists
    bool exists = false;
    for (ControllerCardWidget *card : m_controllerCards)
    {
        if (card->ipAddress() == ip)
        {
            // Update existing card
            card->setStatus(ControllerCardWidget::Connected);
            card->updateLastSeen();
            exists = true;
            break;
        }
    }

    if (!exists)
    {
        addControllerCard(ip, controllerType, "Connected");
    }

    // Update system status
    m_discoveryStatus->setText(QString("📡 Discovery: %1 Found").arg(m_controllerCards.count()));
}

void ModernMainWindow::onControllerCountChanged(int count)
{
    m_discoveredControllers = count;
    m_discoveryStatus->setText(QString("📡 Discovery: %1 Controllers").arg(count));
    qDebug() << "Controller count changed to:" << count;
}

void ModernMainWindow::updateSystemStatus()
{
    // Update system metrics (simplified for demo)
    m_cpuLabel->setText("📊 CPU: 12%");
    m_memoryLabel->setText("💾 RAM: 245MB");
    m_networkLabel->setText("🌐 Network: 1.2MB/s");
    m_lastUpdateLabel->setText(QString("🔄 Last Update: %1").arg(QDateTime::currentDateTime().toString("hh:mm:ss")));

    // Update connection status based on discovered controllers
    if (m_discoveredControllers > 0)
    {
        m_connectionStatusLabel->setText(QString("🟢 ONLINE - %1 Controllers").arg(m_discoveredControllers));
        m_modbusStatus->setText("🔗 Modbus: Connected");
    }
    else
    {
        m_connectionStatusLabel->setText("🟡 SCANNING");
        m_modbusStatus->setText("🔗 Modbus: Searching");
    }
}

void ModernMainWindow::updateDateTime()
{
    QDateTime now = QDateTime::currentDateTime();
    m_dateTimeLabel->setText(QString("🕐 %1\n%2")
                                 .arg(now.toString("hh:mm:ss"))
                                 .arg(now.toString("MMM d, yyyy")));
}

void ModernMainWindow::showControllerDetails(const QString &ip)
{
    qDebug() << "=== CONTROLLER DETAILS DEBUG ===";
    qDebug() << "Show controller details for IP:" << ip;
    qDebug() << "IP length:" << ip.length();
    qDebug() << "IP contains IPv6 prefix:" << ip.contains("::ffff:");
    
    // Clean up IPv6-mapped IPv4 addresses if needed
    QString cleanedIp = ip;
    if (ip.startsWith("::ffff:")) {
        cleanedIp = ip.mid(7); // Remove "::ffff:" prefix
        qDebug() << "Cleaned IPv6-mapped address to:" << cleanedIp;
    }
    
    // Ensure the Industrial Data Page is initialized
    if (!m_industrialDataPage) {
        m_industrialDataPage = new IndustrialDataPage(this);
    }
    
    // Set the controller URL and load the XML
    QString controllerUrl = QString("http://%1").arg(cleanedIp);
    qDebug() << "Setting controller URL to:" << controllerUrl;
    m_industrialDataPage->setControllerUrl(controllerUrl);
    m_industrialDataPage->loadXmlFile("unit/p_operation.xml");
    
    // Navigate to the page
    QVariantMap parameters;
    parameters["controllerIp"] = cleanedIp;
    navigateToPage(NavigationManager::PageId::ControllerDetails, parameters);
    qDebug() << "=== END CONTROLLER DETAILS DEBUG ===";
}

void ModernMainWindow::refreshControllers()
{
    qDebug() << "Refreshing controller discovery";

    if (m_udpService)
    {
        m_udpService->stopBroadcast();
        m_udpService->startBroadcast();
    }

    m_discoveryStatus->setText("📡 Discovery: Refreshing...");
}

void ModernMainWindow::addControllerCard(const QString &ip, const QString &type, const QString &status)
{
    ControllerCardWidget *card = new ControllerCardWidget(type, ip, this);

    // Set initial status
    if (status == "Connected")
    {
        card->setStatus(ControllerCardWidget::Connected);
    }
    else if (status == "Running")
    {
        card->setStatus(ControllerCardWidget::Running);
    }

    // Set some demo metrics
    card->setTemperature(65.0 + (QRandomGenerator::global()->bounded(20)));
    card->setPowerConsumption(12.5 + (QRandomGenerator::global()->bounded(8)));
    card->setConnectionQuality(80 + (QRandomGenerator::global()->bounded(20)));

    // Connect signals
    connect(card, &ControllerCardWidget::cardClicked,
            this, &ModernMainWindow::showControllerDetails);
    connect(card, &ControllerCardWidget::configureRequested,
            this, &ModernMainWindow::showControllerDetails);
    connect(card, &ControllerCardWidget::diagnosticsRequested,
            this, &ModernMainWindow::showControllerDetails);

    m_controllerCards.append(card);

    // Add to grid layout
    int row = m_controllerCards.count() / 3;
    int col = (m_controllerCards.count() - 1) % 3;
    m_controllerGridLayout->addWidget(card, row, col);

    // Animate card entry
    animateCardEntry(card);

    qDebug() << "Added controller card:" << type << ip;
}

void ModernMainWindow::animateCardEntry(QWidget *card)
{
    // Simple fade-in animation
    card->setVisible(true);
    card->show();
    qDebug() << "Animated card entry";
}

void ModernMainWindow::updateControllerGrid()
{
    // Update all controller cards with fresh data
    for (ControllerCardWidget *card : m_controllerCards)
    {
        // Simulate data updates
        if (QRandomGenerator::global()->bounded(10) == 0)
        { // 10% chance to update metrics
            card->setTemperature(65.0 + (QRandomGenerator::global()->bounded(20)));
            card->setPowerConsumption(12.5 + (QRandomGenerator::global()->bounded(8)));
            card->setConnectionQuality(80 + (QRandomGenerator::global()->bounded(20)));
        }
    }
}

void ModernMainWindow::closeEvent(QCloseEvent *event)
{
    if (m_udpService)
    {
        m_udpService->stopBroadcast();
    }
    QMainWindow::closeEvent(event);
}

void ModernMainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    updateControllerGrid();
    
    // Update hamburger menu size to fill the entire window
    if (m_hamburgerMenu) {
        m_hamburgerMenu->setGeometry(0, 0, width(), height());
    }
}

void ModernMainWindow::setupNavigation()
{
    // Stacked widget is already created in setupUI
    // Initialize navigation manager
    m_navigationManager = new NavigationManager(m_stackedWidget, this);
    
    // Create pages if they don't exist
    if (!m_dashboardPage) {
        m_dashboardPage = new DashboardPage(this);
    }
    if (!m_graphsPage) {
        m_graphsPage = new GraphsPage(this);
    }
    if (!m_settingsPage) {
        m_settingsPage = new SettingsPage(this);
    }
    if (!m_udpResponsePage) {
        m_udpResponsePage = new UdpResponsePage(this);
    }
    if (!m_industrialDataPage) {
        m_industrialDataPage = new IndustrialDataPage(this);
        // Set up controller connection
        m_industrialDataPage->setControllerUrl("http://192.168.10.243");
        m_industrialDataPage->loadXmlFile("unit/p_operation.xml");
    }
    
    // Register pages with navigation manager
    m_navigationManager->registerPage(NavigationManager::PageId::Overview, 
                                      m_mainContent, "Overview", "🏠");
    m_navigationManager->registerPage(NavigationManager::PageId::Dashboard, 
                                      m_dashboardPage, "Dashboard", "📊");
    m_navigationManager->registerPage(NavigationManager::PageId::Graphs, 
                                      m_graphsPage, "Graphs", "📈");
    m_navigationManager->registerPage(NavigationManager::PageId::Settings, 
                                      m_settingsPage, "Settings", "⚙️");
    m_navigationManager->registerPage(NavigationManager::PageId::UdpResponse, 
                                      m_udpResponsePage, "Network", "🌐");
    m_navigationManager->registerPage(NavigationManager::PageId::ControllerDetails, 
                                      m_industrialDataPage, "Industrial", "🏭");
    
    // Connect navigation signals
    connect(m_navigationManager, &NavigationManager::pageChanged,
            this, [this](NavigationManager::PageId fromPage, NavigationManager::PageId toPage) {
                qDebug() << "Page changed from" << static_cast<int>(fromPage) 
                         << "to" << static_cast<int>(toPage);
            });
    
    connect(m_navigationManager, &NavigationManager::navigationStateChanged,
            this, &ModernMainWindow::onNavigationStateChanged);
    
    // Connect hamburger menu to navigation manager
    if (m_hamburgerMenu) {
        qDebug() << "Connecting HamburgerMenu to NavigationManager";
        m_hamburgerMenu->setNavigationManager(m_navigationManager);
    }
    
    // Connect navigation state changes to update header buttons
    connect(m_navigationManager, &NavigationManager::navigationStateChanged,
            this, &ModernMainWindow::updateHeaderButtons);
    
    // Initial button state update
    updateHeaderButtons();
    
    qDebug() << "Professional navigation system initialized";
}

void ModernMainWindow::createBreadcrumbNavigation()
{
    m_breadcrumbWidget = new BreadcrumbWidget(this);
    m_breadcrumbWidget->setTouchOptimized(true);
    m_breadcrumbWidget->setMaxVisibleItems(5);
    
    // Connect breadcrumb widget to navigation manager
    if (m_navigationManager) {
        qDebug() << "Setting NavigationManager on BreadcrumbWidget";
        m_breadcrumbWidget->setNavigationManager(m_navigationManager);
    } else {
        qDebug() << "WARNING: NavigationManager is null when creating breadcrumb widget!";
    }
    
    // Connect breadcrumb signals
    connect(m_breadcrumbWidget, &BreadcrumbWidget::breadcrumbClicked,
            this, &ModernMainWindow::onBreadcrumbClicked);
    connect(m_breadcrumbWidget, &BreadcrumbWidget::homeClicked,
            this, [this]() {
                if (m_navigationManager) {
                    m_navigationManager->goHome();
                }
            });
    connect(m_breadcrumbWidget, &BreadcrumbWidget::backClicked,
            this, [this]() {
                qDebug() << "Back button clicked in ModernMainWindow!";
                if (m_navigationManager) {
                    qDebug() << "Calling NavigationManager::goBack()";
                    m_navigationManager->goBack();
                } else {
                    qDebug() << "NavigationManager is null!";
                }
            });
    
    qDebug() << "Breadcrumb navigation created";
}

void ModernMainWindow::updateHeaderButtons()
{
    if (!m_navigationManager) return;
    
    // Update back button state
    bool canGoBack = m_navigationManager->canGoBack();
    if (m_backButton) {
        m_backButton->setEnabled(canGoBack);
        qDebug() << "Header back button enabled:" << canGoBack;
    }
    
    // Home button is always enabled (could be disabled if already at home)
    if (m_homeButton) {
        bool isAtHome = (m_navigationManager->currentPage() == NavigationManager::PageId::Overview);
        m_homeButton->setEnabled(!isAtHome);
    }
}

void ModernMainWindow::onBreadcrumbClicked(int index)
{
    qDebug() << "Breadcrumb clicked at index:" << index;
    
    if (m_navigationManager) {
        // Get the navigation history to determine which page the breadcrumb represents
        QStringList breadcrumbs = m_navigationManager->breadcrumbPath();
        if (index >= 0 && index < breadcrumbs.size()) {
            // Navigate back to the clicked breadcrumb level
            m_navigationManager->navigateToHistoryIndex(index);
        }
    }
}

void ModernMainWindow::onNavigationStateChanged()
{
    // Update header buttons based on navigation state
    updateHeaderButtons();
}