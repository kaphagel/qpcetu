#include "modernmainwindow.h"
#include "controllercardwidget.h"
#include "../pages/dashboardpage.h"
#include "../pages/graphspage.h"
#include "../pages/settingspage.h"
#include "../pages/udpresponsepage.h"

#include <QApplication>
#include <QDateTime>
#include <QDebug>
#include <QCloseEvent>
#include <QResizeEvent>
#include <QRandomGenerator>

ModernMainWindow::ModernMainWindow(QWidget *parent)
    : QMainWindow(parent), m_udpService(nullptr), m_dashboardPage(nullptr), m_graphsPage(nullptr), m_settingsPage(nullptr), m_udpResponsePage(nullptr), m_discoveredControllers(0)
{
    qDebug() << "ModernMainWindow constructor start";

    setWindowTitle("🛸 QUANTUM TACTICAL PROCESSING CENTER - ETU");
    setMinimumSize(1200, 800);
    resize(1600, 1000);

    setupUI();
    setupStyling();

    // Initialize UDP service for controller discovery
    m_udpService = new UdpService(this);
    connect(m_udpService, &UdpService::moduleDiscovered,
            this, &ModernMainWindow::onControllerDiscovered);
    connect(m_udpService, &UdpService::controllersChanged,
            this, [this]()
            { onControllerCountChanged(m_udpService->discoveredControllers()); });

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
    mainLayout->addWidget(m_mainContent, 1);
    mainLayout->addWidget(m_bottomStatusBar);
}

void ModernMainWindow::createHeaderBar()
{
    m_headerBar = new QWidget();
    m_headerBar->setFixedHeight(60);
    m_headerBar->setObjectName("headerBar");

    QHBoxLayout *headerLayout = new QHBoxLayout(m_headerBar);
    headerLayout->setContentsMargins(20, 10, 20, 10);
    headerLayout->setSpacing(20);

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

    headerLayout->addWidget(m_titleLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(m_connectionStatusLabel);
    headerLayout->addWidget(m_userLabel);
    headerLayout->addWidget(m_dateTimeLabel);
}

void ModernMainWindow::createSystemStatusStrip()
{
    m_statusStrip = new QWidget();
    m_statusStrip->setFixedHeight(40);
    m_statusStrip->setObjectName("statusStrip");

    QHBoxLayout *statusLayout = new QHBoxLayout(m_statusStrip);
    statusLayout->setContentsMargins(20, 8, 20, 8);
    statusLayout->setSpacing(30);

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
    contentLayout->setContentsMargins(20, 20, 20, 20);
    contentLayout->setSpacing(20);

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
    sectionLayout->setSpacing(15);

    // Section header
    QWidget *headerWidget = new QWidget();
    QHBoxLayout *headerLayout = new QHBoxLayout(headerWidget);
    headerLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *titleLabel = new QLabel("🎛️ ACTIVE CONTROLLERS");
    titleLabel->setObjectName("sectionTitle");

    QPushButton *refreshButton = new QPushButton("🔄 Refresh");
    refreshButton->setObjectName("actionButton");
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
    m_controllerGridLayout->setSpacing(15);
    m_controllerGridLayout->setContentsMargins(10, 10, 10, 10);

    // Add initial "Add Controller" card
    QPushButton *addControllerCard = new QPushButton("➕ ADD\nCONTROLLER\n\nAuto-Discover\nor Manual");
    addControllerCard->setFixedSize(280, 180);
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
    panelLayout->setContentsMargins(20, 0, 0, 0);
    panelLayout->setSpacing(20);

    // Alerts section
    QGroupBox *alertsGroup = new QGroupBox("🚨 ACTIVE ALERTS");
    alertsGroup->setObjectName("alertsGroup");

    QVBoxLayout *alertsLayout = new QVBoxLayout(alertsGroup);
    alertsLayout->setSpacing(10);

    // Sample alert items
    QLabel *alert1 = new QLabel("⚠️  Controller Discovery\n     New device found | 14:31\n     [VIEW] [CONFIGURE]");
    alert1->setObjectName("alertItem");

    QLabel *alert2 = new QLabel("ℹ️  System Status\n     All systems nominal | 14:28\n     [DETAILS] [ACKNOWLEDGE]");
    alert2->setObjectName("alertItem");

    alertsLayout->addWidget(alert1);
    alertsLayout->addWidget(alert2);
    alertsLayout->addStretch();

    // Quick actions section
    QGroupBox *actionsGroup = new QGroupBox("🔧 QUICK ACTIONS");
    actionsGroup->setObjectName("actionsGroup");

    QVBoxLayout *actionsLayout = new QVBoxLayout(actionsGroup);
    actionsLayout->setSpacing(8);

    QPushButton *controllersBtn = new QPushButton("🎛️  Controller Management");
    QPushButton *dashboardBtn = new QPushButton("📊  Data Visualization");
    QPushButton *settingsBtn = new QPushButton("⚙️  System Settings");
    QPushButton *networkBtn = new QPushButton("📡  Network Discovery");
    QPushButton *diagnosticsBtn = new QPushButton("🛠️  Diagnostic Tools");

    // Style all action buttons
    QList<QPushButton *> actionButtons = {controllersBtn, dashboardBtn, settingsBtn, networkBtn, diagnosticsBtn};
    for (QPushButton *btn : actionButtons)
    {
        btn->setObjectName("quickActionButton");
        btn->setFixedHeight(35);
        actionsLayout->addWidget(btn);
    }

    // Connect action buttons
    connect(dashboardBtn, &QPushButton::clicked, this, [this]()
            { navigateToPage(1); });
    connect(settingsBtn, &QPushButton::clicked, this, [this]()
            { navigateToPage(3); });
    connect(networkBtn, &QPushButton::clicked, this, &ModernMainWindow::refreshControllers);

    actionsLayout->addStretch();

    panelLayout->addWidget(alertsGroup);
    panelLayout->addWidget(actionsGroup);
    panelLayout->addStretch();
}

void ModernMainWindow::createStatusBar()
{
    m_bottomStatusBar = new QWidget();
    m_bottomStatusBar->setFixedHeight(32);
    m_bottomStatusBar->setObjectName("bottomStatusBar");

    QHBoxLayout *statusLayout = new QHBoxLayout(m_bottomStatusBar);
    statusLayout->setContentsMargins(20, 6, 20, 6);
    statusLayout->setSpacing(20);

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
    // Simple styling for now to avoid string literal issues
    setStyleSheet(
        "QMainWindow { background-color: #0F1419; color: #FFFFFF; }"
        "QWidget#headerBar { background-color: #1E2328; border-bottom: 2px solid #00E5FF; }"
        "QLabel#titleLabel { font-size: 18px; font-weight: bold; color: #00E5FF; }"
        "QLabel#connectionStatus { font-size: 12px; color: #4CAF50; font-weight: bold; }"
        "QLabel#userLabel, QLabel#dateTimeLabel { font-size: 12px; color: #B0BEC5; }"
        "QWidget#statusStrip { background-color: rgba(0, 229, 255, 0.05); }"
        "QLabel#statusLabel { font-size: 11px; color: #78909C; font-weight: 500; }"
        "QLabel#sectionTitle { font-size: 16px; font-weight: bold; color: #00E5FF; }"
        "QPushButton#addControllerCard { background-color: rgba(0, 229, 255, 0.1); border: 2px dashed rgba(0, 229, 255, 0.5); border-radius: 8px; color: #00E5FF; font-size: 14px; font-weight: bold; }"
        "QPushButton#addControllerCard:hover { background-color: rgba(0, 229, 255, 0.15); }"
        "QWidget#quickActionsPanel { background-color: rgba(45, 45, 45, 0.3); border-radius: 8px; }"
        "QGroupBox { font-size: 14px; font-weight: bold; color: #00E5FF; border: 1px solid rgba(0, 229, 255, 0.3); border-radius: 8px; }"
        "QLabel#alertItem { background-color: rgba(255, 152, 0, 0.1); border: 1px solid rgba(255, 152, 0, 0.3); border-radius: 6px; padding: 8px; font-size: 11px; color: #FFFFFF; }"
        "QPushButton#quickActionButton { background-color: rgba(55, 71, 79, 0.3); border: 1px solid rgba(176, 190, 197, 0.2); border-radius: 6px; color: #B0BEC5; font-size: 12px; padding: 8px 12px; }"
        "QPushButton#quickActionButton:hover { background-color: rgba(0, 229, 255, 0.1); border: 1px solid rgba(0, 229, 255, 0.3); color: #00E5FF; }"
        "QPushButton#actionButton { background-color: rgba(0, 229, 255, 0.1); border: 1px solid rgba(0, 229, 255, 0.3); border-radius: 6px; color: #00E5FF; font-size: 12px; padding: 6px 12px; }"
        "QPushButton#actionButton:hover { background-color: rgba(0, 229, 255, 0.2); }"
        "QWidget#bottomStatusBar { background-color: rgba(15, 20, 25, 0.8); }"
        "QLabel#statusBarLabel { font-size: 11px; color: #78909C; font-family: 'Courier New', monospace; }");
}

void ModernMainWindow::navigateToPage(int index)
{
    qDebug() << "Navigation to page" << index << "requested";
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
    qDebug() << "Show controller details for:" << ip;
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
}