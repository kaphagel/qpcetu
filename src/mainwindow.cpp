#include "mainwindow.h"
#include "datawidget.h"
#include "animatedprogressbar.h"
#include "graphwidget.h"
#include <QDateTime>
#include <QScrollBar>
#include <QApplication>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_centralWidget(nullptr)
    , m_mainLayout(nullptr)
    , m_statusLabel(nullptr)
    , m_timeLabel(nullptr)
    , m_connectionStatus(nullptr)
    , m_energyWidget(nullptr)
    , m_shieldWidget(nullptr)
    , m_engineWidget(nullptr)
    , m_weaponWidget(nullptr)
    , m_powerBar(nullptr)
    , m_coolantBar(nullptr)
    , m_fuelBar(nullptr)
    , m_logDisplay(nullptr)
    , m_coordinates(nullptr)
    , m_velocity(nullptr)
    , m_altitude(nullptr)
    , m_engageBtn(nullptr)
    , m_alertBtn(nullptr)
    , m_scanBtn(nullptr)
    , m_updateTimer(nullptr)
    , m_statusTimer(nullptr)
    , m_alertTimer(nullptr)
    , m_energyGraph(nullptr)
    , m_shieldGraph(nullptr)
    , m_systemGraph(nullptr)
    , m_networkGraph(nullptr)
    , m_thrusterGraph(nullptr)
    , m_sensorGraph(nullptr)
    , m_alertLevel(0)
    , m_systemOnline(true)
{
    setWindowTitle("QUANTUM TACTICAL PROCESSING CENTER - ETU");
    setMinimumSize(1200, 800);   // Reduced minimum size
    resize(1400, 1000);          // Reduced initial size
    
    setupUI();
    setupStyling();
    
    // Setup timers
    m_updateTimer = new QTimer(this);
    connect(m_updateTimer, &QTimer::timeout, this, &MainWindow::updateData);
    
    m_statusTimer = new QTimer(this);
    connect(m_statusTimer, &QTimer::timeout, this, &MainWindow::updateSystemStatus);
    
    m_alertTimer = new QTimer(this);
    connect(m_alertTimer, &QTimer::timeout, this, &MainWindow::simulateAlert);
    
    // Initial update
    updateData();
    updateSystemStatus();
    
    // Start timers
    m_updateTimer->start(2000); // Update every 2 seconds
    m_statusTimer->start(1000); // Update every second
    m_alertTimer->start(15000); // Alert every 15 seconds
}

MainWindow::~MainWindow()
{
    if (m_updateTimer) {
        m_updateTimer->stop();
        m_updateTimer->deleteLater();
        m_updateTimer = nullptr;
    }
    if (m_statusTimer) {
        m_statusTimer->stop();
        m_statusTimer->deleteLater();
        m_statusTimer = nullptr;
    }
    if (m_alertTimer) {
        m_alertTimer->stop();
        m_alertTimer->deleteLater();
        m_alertTimer = nullptr;
    }
}

void MainWindow::setupUI()
{
    m_centralWidget = new QWidget;
    setCentralWidget(m_centralWidget);

    QVBoxLayout *mainVLayout = new QVBoxLayout(m_centralWidget);
    mainVLayout->setSpacing(0);
    mainVLayout->setContentsMargins(0, 0, 0, 0);

    // Breadcrumb bar
    m_breadcrumbBar = new QWidget(m_centralWidget);
    m_breadcrumbLayout = new QHBoxLayout(m_breadcrumbBar);
    m_breadcrumbLayout->setContentsMargins(10, 10, 10, 10);
    m_breadcrumbLayout->setSpacing(8);
    mainVLayout->addWidget(m_breadcrumbBar);

    // Stacked widget for pages
    m_stackedWidget = new QStackedWidget(m_centralWidget);
    mainVLayout->addWidget(m_stackedWidget, 1);

    setupPages();
    setupBreadcrumbs({"Dashboard", "Graphs", "Settings"}, 0);
    m_stackedWidget->setCurrentIndex(0);
}

void MainWindow::createStatusPanel()
{
    QFrame *statusFrame = new QFrame;
    statusFrame->setFrameStyle(QFrame::Box);
    statusFrame->setObjectName("statusFrame");
    statusFrame->setMaximumHeight(60);  // Force maximum height
    statusFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    
    QHBoxLayout *statusLayout = new QHBoxLayout(statusFrame);
    
    // System status
    m_statusLabel = new QLabel("SYSTEM ONLINE");
    m_statusLabel->setObjectName("statusLabel");
    m_statusLabel->setAlignment(Qt::AlignCenter);
    
    // Time display
    m_timeLabel = new QLabel;
    m_timeLabel->setObjectName("timeLabel");
    m_timeLabel->setAlignment(Qt::AlignCenter);
    
    // Connection status
    m_connectionStatus = new QLabel("QUANTUM LINK: ACTIVE");
    m_connectionStatus->setObjectName("connectionStatus");
    m_connectionStatus->setAlignment(Qt::AlignCenter);
    
    statusLayout->addWidget(m_statusLabel);
    statusLayout->addWidget(m_timeLabel);
    statusLayout->addWidget(m_connectionStatus);
    
    m_mainLayout->addWidget(statusFrame, 0, 0, 1, 4);
}

void MainWindow::createDataPanels()
{
    // Energy systems
    m_energyWidget = new DataWidget("ENERGY CORE", "MW");
    m_mainLayout->addWidget(m_energyWidget, 1, 0);
    
    // Shield systems
    m_shieldWidget = new DataWidget("SHIELD MATRIX", "%");
    m_mainLayout->addWidget(m_shieldWidget, 1, 1);
    
    // Engine systems
    m_engineWidget = new DataWidget("ENGINE THRUST", "KN");
    m_mainLayout->addWidget(m_engineWidget, 2, 0);
    
    // Weapon systems
    m_weaponWidget = new DataWidget("WEAPON ARRAY", "READY");
    m_mainLayout->addWidget(m_weaponWidget, 2, 1);
}

void MainWindow::createGraphPanels()
{
    // Create real-time graphs with different data types and sci-fi colors
    m_energyGraph = new GraphWidget("ENERGY FLUX", GraphWidget::SineWave);
    m_energyGraph->setRange(0, 120);
    m_mainLayout->addWidget(m_energyGraph, 2, 2);  // Row 2, next to system panel
    
    m_shieldGraph = new GraphWidget("SHIELD HARMONICS", GraphWidget::RandomData);
    m_shieldGraph->setRange(20, 100);
    m_mainLayout->addWidget(m_shieldGraph, 2, 3);  // Row 2, next to control panel
    
    m_systemGraph = new GraphWidget("SYSTEM STATUS", GraphWidget::StepFunction);
    m_systemGraph->setRange(0, 100);
    m_mainLayout->addWidget(m_systemGraph, 3, 0);  // Row 3, column 0
    
    m_networkGraph = new GraphWidget("NETWORK TRAFFIC", GraphWidget::PulseWave);
    m_networkGraph->setRange(0, 100);
    m_mainLayout->addWidget(m_networkGraph, 3, 1);  // Row 3, column 1
    
    m_thrusterGraph = new GraphWidget("THRUSTER OUTPUT", GraphWidget::SineWave);
    m_thrusterGraph->setRange(0, 150);
    m_mainLayout->addWidget(m_thrusterGraph, 3, 2);  // Row 3, column 2
    
    m_sensorGraph = new GraphWidget("SENSOR ARRAY", GraphWidget::RandomData);
    m_sensorGraph->setRange(10, 90);
    m_mainLayout->addWidget(m_sensorGraph, 3, 3);  // Row 3, column 3
}

void MainWindow::createSystemPanel()
{
    QGroupBox *systemGroup = new QGroupBox("SYSTEM PARAMETERS");
    systemGroup->setObjectName("systemGroup");
    QVBoxLayout *systemLayout = new QVBoxLayout(systemGroup);
    
    // Progress bars
    QLabel *powerLabel = new QLabel("POWER DISTRIBUTION");
    powerLabel->setObjectName("parameterLabel");
    m_powerBar = new AnimatedProgressBar;
    m_powerBar->setObjectName("powerBar");
    
    QLabel *coolantLabel = new QLabel("COOLANT SYSTEM");
    coolantLabel->setObjectName("parameterLabel");
    m_coolantBar = new AnimatedProgressBar;
    m_coolantBar->setObjectName("coolantBar");
    
    QLabel *fuelLabel = new QLabel("FUEL RESERVES");
    fuelLabel->setObjectName("parameterLabel");
    m_fuelBar = new AnimatedProgressBar;
    m_fuelBar->setObjectName("fuelBar");
    
    // Navigation data
    m_coordinates = new QLabel("COORDINATES: X:00000 Y:00000 Z:00000");
    m_coordinates->setObjectName("navLabel");
    
    m_velocity = new QLabel("VELOCITY: 0.00 C");
    m_velocity->setObjectName("navLabel");
    
    m_altitude = new QLabel("ALTITUDE: 0 KM");
    m_altitude->setObjectName("navLabel");
    
    systemLayout->addWidget(powerLabel);
    systemLayout->addWidget(m_powerBar);
    systemLayout->addWidget(coolantLabel);
    systemLayout->addWidget(m_coolantBar);
    systemLayout->addWidget(fuelLabel);
    systemLayout->addWidget(m_fuelBar);
    systemLayout->addWidget(m_coordinates);
    systemLayout->addWidget(m_velocity);
    systemLayout->addWidget(m_altitude);
    
    m_mainLayout->addWidget(systemGroup, 1, 2, 2, 1);
}

void MainWindow::createControlPanel()
{
    QFrame *controlFrame = new QFrame;
    controlFrame->setFrameStyle(QFrame::Box);
    controlFrame->setObjectName("controlFrame");
    
    QVBoxLayout *controlLayout = new QVBoxLayout(controlFrame);
    
    // Control buttons
    m_engageBtn = new QPushButton("ENGAGE SYSTEMS");
    m_engageBtn->setObjectName("controlButton");
    
    m_alertBtn = new QPushButton("ALERT STATUS");
    m_alertBtn->setObjectName("alertButton");
    
    m_scanBtn = new QPushButton("DEEP SCAN");
    m_scanBtn->setObjectName("controlButton");
    
    // Log display
    QLabel *logLabel = new QLabel("SYSTEM LOG");
    logLabel->setObjectName("parameterLabel");
    
    m_logDisplay = new QTextEdit;
    m_logDisplay->setObjectName("logDisplay");
    m_logDisplay->setMaximumHeight(200);
    m_logDisplay->setReadOnly(true);
    
    controlLayout->addWidget(m_engageBtn);
    controlLayout->addWidget(m_alertBtn);
    controlLayout->addWidget(m_scanBtn);
    controlLayout->addWidget(logLabel);
    controlLayout->addWidget(m_logDisplay);
    
    m_mainLayout->addWidget(controlFrame, 1, 3, 2, 1);
    
    // Connect buttons
    connect(m_engageBtn, &QPushButton::clicked, [this]() {
        if (m_logDisplay) {
            m_logDisplay->append(QString("[%1] Systems engaged - All parameters nominal")
                                .arg(QDateTime::currentDateTime().toString("hh:mm:ss")));
        }
    });
    
    connect(m_alertBtn, &QPushButton::clicked, [this]() {
        simulateAlert();
    });
    
    connect(m_scanBtn, &QPushButton::clicked, [this]() {
        if (m_logDisplay) {
            m_logDisplay->append(QString("[%1] Deep scan initiated - Analyzing quantum signatures...")
                                .arg(QDateTime::currentDateTime().toString("hh:mm:ss")));
        }
    });
}

void MainWindow::setupStyling()
{
    QString styleSheet = R"(
        QMainWindow {
            background-color: #0a0a1a;
            color: #00aaff;
        }
        
        QFrame#statusFrame {
            background-color: #001133;
            border: 2px solid #0066cc;
            border-radius: 8px;
            padding: 10px;
        }
        
        QFrame#controlFrame {
            background-color: #001133;
            border: 2px solid #0066cc;
            border-radius: 8px;
            padding: 10px;
        }
        
        QLabel#statusLabel {
            font-size: 16px;
            font-weight: bold;
            color: #00ff88;
            background-color: #002211;
            border: 1px solid #00aa44;
            border-radius: 4px;
            padding: 8px;
        }
        
        QLabel#timeLabel {
            font-size: 14px;
            color: #00aaff;
            font-family: 'Courier New', monospace;
        }
        
        QLabel#connectionStatus {
            font-size: 12px;
            color: #ffaa00;
        }
        
        QGroupBox#systemGroup {
            font-size: 14px;
            font-weight: bold;
            color: #00aaff;
            border: 2px solid #0066cc;
            border-radius: 8px;
            margin-top: 10px;
            background-color: #001133;
        }
        
        QGroupBox#systemGroup::title {
            subcontrol-origin: margin;
            left: 10px;
            padding: 0 8px 0 8px;
            color: #00aaff;
        }
        
        QLabel#parameterLabel {
            font-size: 11px;
            color: #88aaff;
            font-weight: bold;
            margin-top: 5px;
        }
        
        QLabel#navLabel {
            font-size: 11px;
            color: #00aaff;
            font-family: 'Courier New', monospace;
            background-color: #000822;
            border: 1px solid #0044aa;
            border-radius: 3px;
            padding: 4px;
            margin: 2px;
        }
        
        QPushButton#controlButton {
            background-color: #0044aa;
            color: #ffffff;
            border: 2px solid #0066cc;
            border-radius: 6px;
            padding: 8px;
            font-weight: bold;
            font-size: 12px;
        }
        
        QPushButton#controlButton:hover {
            background-color: #0066cc;
            border-color: #0088ff;
        }
        
        QPushButton#controlButton:pressed {
            background-color: #002266;
        }
        
        QPushButton#alertButton {
            background-color: #aa4400;
            color: #ffffff;
            border: 2px solid #cc6600;
            border-radius: 6px;
            padding: 8px;
            font-weight: bold;
            font-size: 12px;
        }
        
        QPushButton#alertButton:hover {
            background-color: #cc6600;
            border-color: #ff8800;
        }
        
        QTextEdit#logDisplay {
            background-color: #000011;
            color: #00ff88;
            border: 1px solid #004422;
            border-radius: 4px;
            font-family: 'Courier New', monospace;
            font-size: 10px;
        }
        
        QScrollBar:vertical {
            background-color: #001122;
            width: 12px;
            border-radius: 6px;
        }
        
        QScrollBar::handle:vertical {
            background-color: #0066cc;
            border-radius: 6px;
            min-height: 20px;
        }
        
        QScrollBar::handle:vertical:hover {
            background-color: #0088ff;
        }
    )";
    
    setStyleSheet(styleSheet);
}

void MainWindow::setupPages() {
    // Page 0: Dashboard (uses member widgets)
    QWidget *dashboardPage = new QWidget;
    QGridLayout *dashboardLayout = new QGridLayout(dashboardPage);
    dashboardLayout->setSpacing(10);
    dashboardLayout->setContentsMargins(15, 15, 15, 15);
    
    // Status panel (member QFrame)
    QFrame *statusFrame = new QFrame(dashboardPage);
    statusFrame->setFrameStyle(QFrame::Box);
    statusFrame->setMaximumHeight(60);
    QHBoxLayout *statusLayout = new QHBoxLayout(statusFrame);
    m_statusLabel = new QLabel("SYSTEM ONLINE", statusFrame);
    m_statusLabel->setAlignment(Qt::AlignCenter);
    m_timeLabel = new QLabel(statusFrame);
    m_timeLabel->setAlignment(Qt::AlignCenter);
    m_connectionStatus = new QLabel("QUANTUM LINK: ACTIVE", statusFrame);
    m_connectionStatus->setAlignment(Qt::AlignCenter);
    statusLayout->addWidget(m_statusLabel);
    statusLayout->addWidget(m_timeLabel);
    statusLayout->addWidget(m_connectionStatus);
    dashboardLayout->addWidget(statusFrame, 0, 0, 1, 4);
    
    // Data panels (member widgets)
    m_energyWidget = new DataWidget("ENERGY CORE", "MW", dashboardPage);
    m_shieldWidget = new DataWidget("SHIELD MATRIX", "%", dashboardPage);
    m_engineWidget = new DataWidget("ENGINE THRUST", "KN", dashboardPage);
    m_weaponWidget = new DataWidget("WEAPON ARRAY", "READY", dashboardPage);
    dashboardLayout->addWidget(m_energyWidget, 1, 0);
    dashboardLayout->addWidget(m_shieldWidget, 1, 1);
    dashboardLayout->addWidget(m_engineWidget, 2, 0);
    dashboardLayout->addWidget(m_weaponWidget, 2, 1);
    
    // Graph panels (member widgets)
    m_energyGraph = new GraphWidget("ENERGY FLUX", GraphWidget::SineWave, dashboardPage);
    m_energyGraph->setRange(0, 120);
    m_shieldGraph = new GraphWidget("SHIELD HARMONICS", GraphWidget::RandomData, dashboardPage);
    m_shieldGraph->setRange(20, 100);
    m_systemGraph = new GraphWidget("SYSTEM STATUS", GraphWidget::StepFunction, dashboardPage);
    m_systemGraph->setRange(0, 100);
    m_networkGraph = new GraphWidget("NETWORK TRAFFIC", GraphWidget::PulseWave, dashboardPage);
    m_networkGraph->setRange(0, 100);
    m_thrusterGraph = new GraphWidget("THRUSTER OUTPUT", GraphWidget::SineWave, dashboardPage);
    m_thrusterGraph->setRange(0, 150);
    m_sensorGraph = new GraphWidget("SENSOR ARRAY", GraphWidget::RandomData, dashboardPage);
    m_sensorGraph->setRange(10, 90);
    dashboardLayout->addWidget(m_energyGraph, 2, 2);
    dashboardLayout->addWidget(m_shieldGraph, 2, 3);
    dashboardLayout->addWidget(m_systemGraph, 3, 0);
    dashboardLayout->addWidget(m_networkGraph, 3, 1);
    dashboardLayout->addWidget(m_thrusterGraph, 3, 2);
    dashboardLayout->addWidget(m_sensorGraph, 3, 3);
    
    m_stackedWidget->addWidget(dashboardPage);
    
    // Page 1: Graphs (local widgets only)
    QWidget *graphsPage = new QWidget;
    QGridLayout *graphsLayout = new QGridLayout(graphsPage);
    graphsLayout->setSpacing(10);
    graphsLayout->setContentsMargins(15, 15, 15, 15);
    graphsLayout->addWidget(new GraphWidget("ENERGY FLUX", GraphWidget::SineWave, graphsPage), 0, 0);
    graphsLayout->addWidget(new GraphWidget("SHIELD HARMONICS", GraphWidget::RandomData, graphsPage), 0, 1);
    graphsLayout->addWidget(new GraphWidget("SYSTEM STATUS", GraphWidget::StepFunction, graphsPage), 1, 0);
    graphsLayout->addWidget(new GraphWidget("NETWORK TRAFFIC", GraphWidget::PulseWave, graphsPage), 1, 1);
    m_stackedWidget->addWidget(graphsPage);
    
    // Page 2: Settings (local widgets only)
    QWidget *settingsPage = new QWidget;
    QVBoxLayout *settingsLayout = new QVBoxLayout(settingsPage);
    QLabel *settingsLabel = new QLabel("Settings Page (Demo)", settingsPage);
    settingsLabel->setAlignment(Qt::AlignCenter);
    settingsLayout->addWidget(settingsLabel);
    m_stackedWidget->addWidget(settingsPage);
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
    setupBreadcrumbs({"Dashboard", "Graphs", "Settings"}, index);
}

void MainWindow::updateData()
{
    QRandomGenerator *rng = QRandomGenerator::global();
    
    // Update data widgets with random values (with null checks)
    if (m_energyWidget) m_energyWidget->setValue(85 + rng->bounded(15));
    if (m_shieldWidget) m_shieldWidget->setValue(70 + rng->bounded(30));
    if (m_engineWidget) m_engineWidget->setValue(90 + rng->bounded(10));
    if (m_weaponWidget) m_weaponWidget->setValue(rng->bounded(2) ? 100 : 95 + rng->bounded(5));
    
    // Update progress bars (with null checks)
    if (m_powerBar) m_powerBar->setValue(75 + rng->bounded(20));
    if (m_coolantBar) m_coolantBar->setValue(60 + rng->bounded(25));
    if (m_fuelBar) m_fuelBar->setValue(80 + rng->bounded(15));
    
    // Update navigation data (with null checks)
    if (m_coordinates) {
        int x = 10000 + rng->bounded(90000);
        int y = 5000 + rng->bounded(45000);
        int z = 1000 + rng->bounded(9000);
        m_coordinates->setText(QString("COORDINATES: X:%1 Y:%2 Z:%3").arg(x).arg(y).arg(z));
    }
    
    if (m_velocity) {
        double velocity = 0.15 + (rng->bounded(100) / 1000.0);
        m_velocity->setText(QString("VELOCITY: %1 C").arg(velocity, 0, 'f', 3));
    }
    
    if (m_altitude) {
        int altitude = 15000 + rng->bounded(5000);
        m_altitude->setText(QString("ALTITUDE: %1 KM").arg(altitude));
    }
}

void MainWindow::updateSystemStatus()
{
    // Update time (with null check)
    if (m_timeLabel) {
        m_timeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    }
    
    // Simulate system status changes
    QRandomGenerator *rng = QRandomGenerator::global();
    if (rng->bounded(100) < 2) { // 2% chance
        m_systemOnline = !m_systemOnline;
        if (m_statusLabel) {
            if (m_systemOnline) {
                m_statusLabel->setText("SYSTEM ONLINE");
                m_statusLabel->setStyleSheet("color: #00ff88; background-color: #002211; border-color: #00aa44;");
            } else {
                m_statusLabel->setText("SYSTEM WARNING");
                m_statusLabel->setStyleSheet("color: #ffaa00; background-color: #221100; border-color: #aa4400;");
            }
        }
    }
}

void MainWindow::simulateAlert()
{
    QRandomGenerator *rng = QRandomGenerator::global();
    QStringList alerts = {
        "Quantum fluctuation detected in sector 7",
        "Energy spike in main reactor core",
        "Incoming transmission from deep space",
        "Shield harmonics approaching critical threshold",
        "Navigation array recalibration complete",
        "Weapon systems cycling - all parameters nominal",
        "Long-range sensors detecting anomalous readings",
        "Coolant flow rate optimization in progress"
    };
    
    QString alert = alerts[rng->bounded(alerts.size())];
    if (m_logDisplay) {
        m_logDisplay->append(QString("[%1] %2")
                            .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
                            .arg(alert));
        // Auto-scroll to bottom
        QScrollBar *scrollBar = m_logDisplay->verticalScrollBar();
        scrollBar->setValue(scrollBar->maximum());
    }
}
