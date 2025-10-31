#include "dashboardviewmodel.h"
#include <QRandomGenerator>
#include <QDebug>

DashboardViewModel::DashboardViewModel(QObject* parent)
    : QObject(parent)
    , m_updateTimer(new QTimer(this))
    , m_isUpdating(false)
    , m_systemStatus(SystemStatus::Online)
    , m_navigationData()
    , m_systemParameters()
    , m_energyCore(85)
    , m_shieldMatrix(70)
    , m_engineThrust(90)
    , m_weaponArray(100)
    , m_connectionActive(true)
{
    connect(m_updateTimer, &QTimer::timeout, this, &DashboardViewModel::onUpdateTimer);
    qDebug() << "DashboardViewModel: Created";
}

DashboardViewModel::~DashboardViewModel() {
    stopUpdates();
    qDebug() << "DashboardViewModel: Destroyed";
}

void DashboardViewModel::startUpdates(int intervalMs) {
    if (!m_isUpdating) {
        m_updateTimer->start(intervalMs);
        m_isUpdating = true;
        qDebug() << "DashboardViewModel: Started updates with interval" << intervalMs << "ms";
    }
}

void DashboardViewModel::stopUpdates() {
    if (m_isUpdating) {
        m_updateTimer->stop();
        m_isUpdating = false;
        qDebug() << "DashboardViewModel: Stopped updates";
    }
}

void DashboardViewModel::updateData() {
    generateRandomData();
    generateRandomSystemParameters();
    generateRandomNavigationData();
}

void DashboardViewModel::updateSystemStatus() {
    // Update time
    QString timestamp = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    emit timeUpdated(timestamp);
    
    // Check system status (with random changes)
    checkSystemStatus();
}

void DashboardViewModel::generateAlert() {
    QString alert = generateRandomAlert();
    QString timestampedAlert = QString("[%1] %2")
        .arg(QDateTime::currentDateTime().toString("hh:mm:ss"))
        .arg(alert);
    
    emit alertGenerated(timestampedAlert);
}

void DashboardViewModel::onUpdateTimer() {
    updateData();
    updateSystemStatus();
    
    // Randomly generate alerts (5% chance per update)
    QRandomGenerator* rng = QRandomGenerator::global();
    if (rng->bounded(100) < 5) {
        generateAlert();
    }
}

void DashboardViewModel::generateRandomData() {
    QRandomGenerator* rng = QRandomGenerator::global();
    
    // Energy Core: 85-100 MW
    m_energyCore = 85 + rng->bounded(15);
    emit energyCoreUpdated(m_energyCore);
    
    // Shield Matrix: 70-100%
    m_shieldMatrix = 70 + rng->bounded(30);
    emit shieldMatrixUpdated(m_shieldMatrix);
    
    // Engine Thrust: 90-100 KN
    m_engineThrust = 90 + rng->bounded(10);
    emit engineThrustUpdated(m_engineThrust);
    
    // Weapon Array: 95-100% (occasionally 100)
    m_weaponArray = rng->bounded(2) ? 100 : 95 + rng->bounded(5);
    emit weaponArrayUpdated(m_weaponArray);
}

void DashboardViewModel::generateRandomSystemParameters() {
    QRandomGenerator* rng = QRandomGenerator::global();
    
    SystemParameters params;
    params.powerDistribution = 75 + rng->bounded(20);  // 75-95%
    params.coolantLevel = 60 + rng->bounded(25);       // 60-85%
    params.fuelReserves = 80 + rng->bounded(15);       // 80-95%
    
    m_systemParameters = params;
    emit systemParametersUpdated(params);
}

void DashboardViewModel::generateRandomNavigationData() {
    QRandomGenerator* rng = QRandomGenerator::global();
    
    NavigationData data;
    data.x = 10000 + rng->bounded(90000);           // 10,000 - 100,000
    data.y = 5000 + rng->bounded(45000);            // 5,000 - 50,000
    data.z = 1000 + rng->bounded(9000);             // 1,000 - 10,000
    data.velocity = 0.15 + (rng->bounded(100) / 1000.0);  // 0.15 - 0.25 C
    data.altitude = 15000 + rng->bounded(5000);     // 15,000 - 20,000 KM
    
    m_navigationData = data;
    emit navigationDataUpdated(data);
}

void DashboardViewModel::checkSystemStatus() {
    QRandomGenerator* rng = QRandomGenerator::global();
    
    // 2% chance to toggle system status
    if (rng->bounded(100) < 2) {
        SystemStatus oldStatus = m_systemStatus;
        
        // Toggle between Online and Warning
        if (m_systemStatus == SystemStatus::Online) {
            m_systemStatus = SystemStatus::Warning;
            emit systemStatusChanged(m_systemStatus, "SYSTEM WARNING");
            qDebug() << "DashboardViewModel: System status changed to WARNING";
        } else {
            m_systemStatus = SystemStatus::Online;
            emit systemStatusChanged(m_systemStatus, "SYSTEM ONLINE");
            qDebug() << "DashboardViewModel: System status changed to ONLINE";
        }
    }
    
    // Connection status (very rarely changes)
    if (rng->bounded(1000) < 1) {
        m_connectionActive = !m_connectionActive;
        QString message = m_connectionActive ? "QUANTUM LINK: ACTIVE" : "QUANTUM LINK: DEGRADED";
        emit connectionStatusChanged(m_connectionActive, message);
        qDebug() << "DashboardViewModel: Connection status changed -" << message;
    }
}

QString DashboardViewModel::generateRandomAlert() {
    QRandomGenerator* rng = QRandomGenerator::global();
    
    QStringList alerts = {
        "Quantum fluctuation detected in sector 7",
        "Energy spike in main reactor core",
        "Incoming transmission from deep space",
        "Shield harmonics approaching critical threshold",
        "Navigation array recalibration complete",
        "Weapon systems cycling - all parameters nominal",
        "Long-range sensors detecting anomalous readings",
        "Coolant flow rate optimization in progress",
        "Hyperdrive coils charging to full capacity",
        "Antimatter containment field stable",
        "Subspace communications array realignment initiated",
        "Warp field integrity at 98.7% - optimal range",
        "Deflector dish emitting standard tachyon pulse",
        "Bio-neural gel packs functioning within parameters",
        "Holographic systems online - all safeties engaged",
        "Transporter pattern buffer cleared and ready",
        "Auxiliary power routing to secondary systems",
        "Environmental controls maintaining life support",
        "Structural integrity field compensating for stress",
        "Inertial dampeners responding to course corrections"
    };
    
    return alerts[rng->bounded(alerts.size())];
}
