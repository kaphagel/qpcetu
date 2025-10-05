#include "dashboardpage.h"
#include "../mainwindow.h"
#include "../datawidget.h"
#include "../animatedprogressbar.h"
#include "../graphwidget.h"
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QFrame>
#include <QHBoxLayout>
#include <QSizePolicy>
#include <QGroupBox>
#include <QDateTime>
// --- DashboardPage widget creation methods ---
void DashboardPage::createStatusPanel(QVBoxLayout *mainVLayout) {
    QFrame *statusFrame = new QFrame;
    statusFrame->setFrameStyle(QFrame::Box);
    statusFrame->setObjectName("statusFrame");
    statusFrame->setMaximumHeight(60);
    statusFrame->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    QHBoxLayout *statusLayout = new QHBoxLayout(statusFrame);

    m_statusLabel = new QLabel("SYSTEM ONLINE");
    m_statusLabel->setObjectName("statusLabel");
    m_statusLabel->setAlignment(Qt::AlignCenter);

    m_timeLabel = new QLabel;
    m_timeLabel->setObjectName("timeLabel");
    m_timeLabel->setAlignment(Qt::AlignCenter);

    m_connectionStatus = new QLabel("QUANTUM LINK: ACTIVE");
    m_connectionStatus->setObjectName("connectionStatus");
    m_connectionStatus->setAlignment(Qt::AlignCenter);

    statusLayout->addWidget(m_statusLabel);
    statusLayout->addWidget(m_timeLabel);
    statusLayout->addWidget(m_connectionStatus);

    mainVLayout->addWidget(statusFrame);
}

void DashboardPage::createDataPanels(QGridLayout *mainLayout) {
    m_energyWidget = new DataWidget("ENERGY CORE", "MW");
    mainLayout->addWidget(m_energyWidget, 1, 0);

    m_shieldWidget = new DataWidget("SHIELD MATRIX", "%");
    mainLayout->addWidget(m_shieldWidget, 1, 1);

    m_engineWidget = new DataWidget("ENGINE THRUST", "KN");
    mainLayout->addWidget(m_engineWidget, 2, 0);

    m_weaponWidget = new DataWidget("WEAPON ARRAY", "READY");
    mainLayout->addWidget(m_weaponWidget, 2, 1);
}

void DashboardPage::createSystemPanel(QGridLayout *mainLayout) {
    QGroupBox *systemGroup = new QGroupBox("SYSTEM PARAMETERS");
    systemGroup->setObjectName("systemGroup");
    QVBoxLayout *systemLayout = new QVBoxLayout(systemGroup);

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

    mainLayout->addWidget(systemGroup, 1, 2, 2, 1);
}

void DashboardPage::createControlPanel(QGridLayout *mainLayout) {
    QFrame *controlFrame = new QFrame;
    controlFrame->setFrameStyle(QFrame::Box);
    controlFrame->setObjectName("controlFrame");

    QVBoxLayout *controlLayout = new QVBoxLayout(controlFrame);

    m_engageBtn = new QPushButton("ENGAGE SYSTEMS");
    m_engageBtn->setObjectName("controlButton");

    m_alertBtn = new QPushButton("ALERT STATUS");
    m_alertBtn->setObjectName("alertButton");

    m_scanBtn = new QPushButton("DEEP SCAN");
    m_scanBtn->setObjectName("controlButton");

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

    mainLayout->addWidget(controlFrame, 1, 3, 2, 1);

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

void DashboardPage::createGraphPanels(QGridLayout *mainLayout) {
    m_energyGraph = new GraphWidget("ENERGY FLUX", GraphWidget::SineWave);
    m_energyGraph->setRange(0, 120);
    mainLayout->addWidget(m_energyGraph, 2, 2);

    m_shieldGraph = new GraphWidget("SHIELD HARMONICS", GraphWidget::RandomData);
    m_shieldGraph->setRange(20, 100);
    mainLayout->addWidget(m_shieldGraph, 2, 3);

    m_systemGraph = new GraphWidget("SYSTEM STATUS", GraphWidget::StepFunction);
    m_systemGraph->setRange(0, 100);
    mainLayout->addWidget(m_systemGraph, 3, 0);

    m_networkGraph = new GraphWidget("NETWORK TRAFFIC", GraphWidget::PulseWave);
    m_networkGraph->setRange(0, 100);
    mainLayout->addWidget(m_networkGraph, 3, 1);

    m_thrusterGraph = new GraphWidget("THRUSTER OUTPUT", GraphWidget::SineWave);
    m_thrusterGraph->setRange(0, 150);
    mainLayout->addWidget(m_thrusterGraph, 3, 2);

    m_sensorGraph = new GraphWidget("SENSOR ARRAY", GraphWidget::RandomData);
    m_sensorGraph->setRange(10, 90);
    mainLayout->addWidget(m_sensorGraph, 3, 3);
}
// ...existing code...
#include <QDateTime>
#include <QScrollBar>
#include <QRandomGenerator>

void DashboardPage::updateData() {
    QRandomGenerator *rng = QRandomGenerator::global();
    if (m_energyWidget) m_energyWidget->setValue(85 + rng->bounded(15));
    if (m_shieldWidget) m_shieldWidget->setValue(70 + rng->bounded(30));
    if (m_engineWidget) m_engineWidget->setValue(90 + rng->bounded(10));
    if (m_weaponWidget) m_weaponWidget->setValue(rng->bounded(2) ? 100 : 95 + rng->bounded(5));
    if (m_powerBar) m_powerBar->setValue(75 + rng->bounded(20));
    if (m_coolantBar) m_coolantBar->setValue(60 + rng->bounded(25));
    if (m_fuelBar) m_fuelBar->setValue(80 + rng->bounded(15));
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

void DashboardPage::updateSystemStatus() {
    if (m_timeLabel) {
        m_timeLabel->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    }
    QRandomGenerator *rng = QRandomGenerator::global();
    if (rng->bounded(100) < 2) {
        m_systemOnline = !m_systemOnline;
        if (m_statusLabel) {
            if (m_systemOnline) {
                m_statusLabel->setText("SYSTEM ONLINE");
                // Removed per-label stylesheet for global style
            } else {
                m_statusLabel->setText("SYSTEM WARNING");
                // Removed per-label stylesheet for global style
            }
        }
    }
}

void DashboardPage::simulateAlert() {
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
        QScrollBar *scrollBar = m_logDisplay->verticalScrollBar();
        scrollBar->setValue(scrollBar->maximum());
    }
}
// DashboardPage implementation
#include "dashboardpage.h"
#include "../datawidget.h"
#include "../animatedprogressbar.h"
#include "../graphwidget.h"
#include <QVBoxLayout>
#include <QLabel>

DashboardPage::DashboardPage(QWidget *parent) : QWidget(parent) {
    setupEEGLayout();
    // Apply EEG-inspired dark style
    QString styleSheet = R"(
        QWidget {
            background-color: #101020;
            color: #00ffcc;
        }
            // Removed custom QPushButton styles for global flat style
        QLabel {
            font-size: 22px;
            color: #00ffcc;
        }
        QFrame, QWidget#graphArea {
            background-color: #181830;
            border: 2px solid #00ffcc;
            border-radius: 12px;
        }
        QLineEdit, QTextEdit {
            background-color: #181830;
            color: #00ffcc;
            font-size: 20px;
            border: 2px solid #00ffcc;
            border-radius: 8px;
        }
    )";
    // Removed per-page stylesheet to allow global button style
}

void DashboardPage::setupEEGLayout() {
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(16);
    mainLayout->setContentsMargins(16, 16, 16, 16);

    // Top bar (info/status/navigation)
    // Top app bar with home button
    QWidget *topBar = new QWidget;
    QHBoxLayout *topLayout = new QHBoxLayout(topBar);
    topLayout->setContentsMargins(0, 0, 0, 0);
    topLayout->setSpacing(0);
    QPushButton *homeBtn = new QPushButton;
    homeBtn->setIcon(QIcon(":/icons/home.svg"));
    homeBtn->setIconSize(QSize(32, 32));
    homeBtn->setFlat(true);
    homeBtn->setStyleSheet("QPushButton { background: transparent; border: none; margin: 0 8px; } QPushButton:pressed { background: #e0e0e0; }");
    topLayout->addWidget(homeBtn, 0, Qt::AlignLeft);
    QLabel *titleLabel = new QLabel("Dashboard");
    titleLabel->setStyleSheet("font-size: 22px; font-weight: bold; color: #007AFF; background: transparent;");
    topLayout->addWidget(titleLabel, 1, Qt::AlignLeft);
    topLayout->addStretch();
    mainLayout->addWidget(topBar);
    connect(homeBtn, &QPushButton::clicked, this, [this]() {
        QWidget *mw = this->window();
        if (auto mainWin = qobject_cast<MainWindow*>(mw)) {
            mainWin->navigateToPage(0);
        }
    });

    // Main graph area (full-width)
    mainLayout->addWidget(createGraphArea(), 1);

    // Data widgets row (horizontal)
    mainLayout->addWidget(createDataWidgetRow());

    // Bottom control bar
    mainLayout->addWidget(createBottomBar());
    this->setLayout(mainLayout);
}

QWidget* DashboardPage::createTopBar() {
    QWidget *topBar = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout(topBar);
    layout->setSpacing(24);
    layout->setContentsMargins(0, 0, 0, 0);
    QLabel *infoLabel = new QLabel("Patient: John Doe | Device: QTC-ETU");
    // Removed per-label stylesheet for global style
    QLabel *statusLabel = new QLabel("Status: OK");
    // Removed per-label stylesheet for global style
    QPushButton *dashboardBtn = new QPushButton("Dashboard");
    QPushButton *graphsBtn = new QPushButton("Graphs");
    QPushButton *udpBtn = new QPushButton("UDP Response");
    dashboardBtn->setMinimumSize(80, 48);
    graphsBtn->setMinimumSize(80, 48);
    udpBtn->setMinimumSize(120, 48);
    layout->addWidget(infoLabel);
    layout->addWidget(statusLabel);
    layout->addStretch();
    layout->addWidget(dashboardBtn);
    layout->addWidget(graphsBtn);
    layout->addWidget(udpBtn);
    return topBar;
}

QWidget* DashboardPage::createGraphArea() {
    QWidget *graphArea = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout(graphArea);
    layout->setSpacing(8);
    layout->setContentsMargins(0, 0, 0, 0);
    GraphWidget *eegGraph = new GraphWidget("EEG Waveform", GraphWidget::SineWave);
    eegGraph->setMinimumHeight(220);
    eegGraph->setRange(0, 100);
    layout->addWidget(eegGraph);
    return graphArea;
}

QWidget* DashboardPage::createDataWidgetRow() {
    QWidget *row = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout(row);
    layout->setSpacing(24);
    layout->setContentsMargins(0, 0, 0, 0);
    DataWidget *w1 = new DataWidget("Alpha", "uV");
    DataWidget *w2 = new DataWidget("Beta", "uV");
    DataWidget *w3 = new DataWidget("Gamma", "uV");
    w1->setMinimumSize(180, 120);
    w2->setMinimumSize(180, 120);
    w3->setMinimumSize(180, 120);
    layout->addWidget(w1);
    layout->addWidget(w2);
    layout->addWidget(w3);
    return row;
}

QWidget* DashboardPage::createBottomBar() {
    QWidget *bottomBar = new QWidget;
    QHBoxLayout *layout = new QHBoxLayout(bottomBar);
    layout->setSpacing(32);
    layout->setContentsMargins(0, 0, 0, 0);
    QPushButton *startBtn = new QPushButton("Start");
    QPushButton *stopBtn = new QPushButton("Stop");
    QPushButton *settingsBtn = new QPushButton("Settings");
    QPushButton *alertBtn = new QPushButton("Alert");
    startBtn->setMinimumSize(120, 60);
    stopBtn->setMinimumSize(120, 60);
    settingsBtn->setMinimumSize(120, 60);
    alertBtn->setMinimumSize(120, 60);
    layout->addStretch();
    layout->addWidget(startBtn);
    layout->addWidget(stopBtn);
    layout->addWidget(settingsBtn);
    layout->addWidget(alertBtn);
    layout->addStretch();
    return bottomBar;
}
